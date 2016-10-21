#ifndef SIMPLECALIBRATION_H
#define SIMPLECALIBRATION_H

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
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
#include <ctime>
#include "struct.h"
#include "Config.h"
#include "MinuitFit.h"

struct single_event_data
{
	double wires_positionsX[4];
	double wires_positionsZ[4];
	double hits_positionsX[4];
	double hits_positionsZ[4];
	int left_right[4]; // left - right information
	double drift_times[4];
	double errors[4];
	double delta[4];
	double track_a;
	double track_b;
	double chi2;
	bool errflag;
	double bin;

	single_event_data()
	{
		bin = 1;
		chi2 = 1;
	}
	
};

class SimpleCalibration
{
public:

	SimpleCalibration();
	SimpleCalibration(const Config &_config);
	~SimpleCalibration();

	void get_data(data_for_D1_simple_calibration _single_event_data);
	void tell_no_of_events();
	double drift_time_to_distance(double drift_time);

	TCanvas* plot_chi2();
	TCanvas* plot_delta();
	TCanvas* plot_delta_cut();
	TCanvas* plot_current_calibration();

	void fit_events(double _chi2_cut);
	void fit_delta_projections(const char* folder_name);

	void apply_corrections();
	void deletations();
	void recalculate_positions();

private:
	void fill_chi2(double _chi2_cut);
	void fill_delta(double _chi2_cut);

	std::vector<single_event_data> CalibrationData; // all data in one vector

	// calibration data: starting calibration
	std::vector<double> InitialDriftTimes;
	std::vector<double> InitialDistances;

	// calibration after non-zero no of iterations
	std::vector<double> DriftTimes;
	std::vector<double> Distances;

	int no_of_iterations;	// should be defined in the config file
	int no_of_calib_bins;			// connected with the size of the calibration vector
	int no_of_corr_bins;	// should be (???) SMALLER than the no_of_bins
	double calib_bin_width;
	double corr_bin_width;
	double max_time_range;

	TH1F *chi2;
	TH2F *delta;

	TH1F *chi2_cut;
	TH2F *delta_cut;

	std::vector<double> ProjectionConstant;
	std::vector<double> ProjectionSigma;
	std::vector<double> ProjectionMean;

};

#endif

// ;>