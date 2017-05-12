#ifndef CALIBRATIONLAYER3D_H
#define CALIBRATIONLAYER3D_H

#include <TStyle.h>
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TMinuit.h"
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TGaxis.h>
#include <TF1.h>
#include <Math/Factory.h>
#include <Math/Functor.h>
#include <numeric>
#include <boost/filesystem.hpp>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <TGraphErrors.h>
#include "TMath.h"
//#include "GSLError.h"

struct D1_single_event_data3d
{
	double wire_pos_X;
	double wire_pos_Z;
	double hit_pos_X;
	double hit_pos_Xerr;
	double hit_pos_Z;
	int left_right; // left - right information
	double drift_time;
	double distance_wire_hit; // from drift time, seems 2b unused, 24.02.17
	double distance_wire_track; // from 
	double error;
	double delta;
	double track_A; // track params: Ax + By + Cz = 0, needs to be changed when 3d unbiased fitting is prepared
	double track_B; // 
	double track_C; // 
	double track_angle;
	double chi2;
	bool errflag;
	int calib_bin;
	int corr_bin;

	D1_single_event_data3d()
	{
		calib_bin= -1;
		corr_bin = -1;
		chi2 = -1;
		hit_pos_Xerr = 1;
		track_A = -1;
		track_B = -1;
		track_C = -1;
		track_angle = -1;
	}
};

class CalibrationLayer3d
{
public:

	CalibrationLayer3d();
	CalibrationLayer3d(int _layer_no, const std::vector<double> &_CalibTimes, const std::vector<double> &_CalibDistances);
	~CalibrationLayer3d();

	// in general - for constructor
	void set_max_time_range(double _max_time_range);
	void set_no_of_corr_bins(double _no_of_corr_bins);
	void set_no_of_bin_in_event();
	void set_no_of_bin_in_calib();

	// in each event
	void get_data(double _wire_pos_X, double _wire_pos_Z, double _drift_time, int _lr);

	// in loop over all events
	double drift_time_to_distance(int i, double drift_time);
	double set_pos_Xerr();
	void calculate_hit_position();
	void calculate_deltas(int i);
	void fill_delta(double _chi2_cut);
	
	// in each iteration
	// for all corr bins
	void fit_delta_projections(const char* folder_name);
	void set_fit_errors();

	// plotting
	TCanvas* plot_delta();
	TCanvas* plot_delta_cut();
	TCanvas* plot_current_calibration();
	TCanvas* plot_corrections();

	// applying results and deletations
	void apply_corrections();
	void deletations();
	void recalculate_positions();

	void set_no_of_iteration(double _no_of_iteration);
	void save_in_root_file(TH2F *_c);
	void save_in_root_file(TGraph *_c);
	void save_in_root_file(TH1F *_c);

	// this should not be like that...
	std::vector<D1_single_event_data3d> CalibrationData;

private:
	int no_of_iteration;

	// calibration data: starting calibration
	std::vector<double> InitialDriftTimes;
	std::vector<double> InitialDistances;

	// calibration after non-zero no of iterations
	std::vector<double> DriftTimes;
	std::vector<double> Distances;
	std::vector<double> Bins;
	std::vector<double> SigmaForCalibration; // if bin widths are not equal

	int layer_no;
	int no_of_calib_bins;	// connected with the size of the calibration vector
	int no_of_corr_bins;	// should be (???) SMALLER than the no_of_bins
	double calib_bin_width;
	double corr_bin_width;
	double max_time_range;

	TH2F *delta;
	TH2F *delta_cut;
	TH1F *wire_hit_test;
	TH1F *wire_track_test;

	std::vector<double> ProjectionConstant;
	std::vector<double> ProjectionSigma;
	std::vector<double> ProjectionMean;
	std::vector<double> XErrors;
};

#endif

// ;>