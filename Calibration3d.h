#ifndef CALIBRATION3D_H
#define CALIBRATION3D_H

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
#include "Fit3d.h"
#include "CalibrationLayer3d.h"
#include <TMath.h>

class Calibration3d
{
public:

	Calibration3d();
	Calibration3d(const Config &_config);
	~Calibration3d();

	void get_data(data_for_D1_calibration _single_event_data);
	void tell_no_of_events();
	void solve_lr_ambiguity(const CalibrationLayer3d &layer1, const CalibrationLayer3d &layer2);
	void calculate_hit_position();
	void save_histograms();
	void fit_events_in_straight_layers_biased(double _chi2_cut);
	void fit_events_in_straight_layers_unbiased(double _chi2_cut);
	void calculate_deltas();
	void set_values_of_track_projections_params();
	void deletations();
	void fill_chi2(double _chi2_cut);
	TCanvas* plot_chi2();		// w kazdej iteracji mozna dodawac histogramy do wektora, pozniej zwracac wektor do main
	TCanvas* plot_chi2_cut();
	TCanvas* plot_delta();
	void fit_delta_projections();
	void apply_corrections();
	void plot_current_calibration();
	void set_no_of_iteration(double _no_of_iteration);
	void set_no_of_bin_in_event();
	void fill_angle_distribution();
	TCanvas* plot_angle_distribution();
	bool was_correct_angle(double track_angle);
	void set_pos_Xerr();
	void fit_in_3d();
	void fit_events();

private:
	bool fit_with_inclined;
	CalibrationLayer3d *Layer[8];
	int no_of_iteration;
	int no_of_calib_bins;
	int no_of_corr_bins;
	double max_time_range;
	double calib_bin_width;
	double corr_bin_width;
	TH1F *chi2;
	TH1F *chi2_cut;
	TH1F *angle_distribution[4];
	TH1F *angle_distribution_no_cut[4];
	double track_angle_min;
	double track_angle_max;

	TVector3 track3d_fit_point, track3d_fit_vector;

	// a, b track parameters in the frames of each set of layers (straight, Pl - +31, M - -31)
	std::vector<double> StraightLayersTracks_apar;
	std::vector<double> StraightLayersTracks_bpar;
	std::vector<double> InclinedLayersPlTracks_apar;
	std::vector<double> InclinedLayersPlTracks_bpar;
	std::vector<double> InclinedLayersMTracks_apar;
	std::vector<double> InclinedLayersMTracks_bpar;

	std::vector<double> Chi2;

	// for plotting
	double half_x_dim;
	double half_z_dim;
	double x_lab_position;
	double z_lab_position;
	double distance_to_1st_layer;




};

#endif

// ;>