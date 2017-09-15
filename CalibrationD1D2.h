 #ifndef CALIBRATIOND1D2_H
#define CALIBRATIOND1D2_H

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
#include "FitD1D2.h"
#include "CalibrationLayerD1D2.h"
#include <TMath.h>

class CalibrationD1D2
{
public:

	CalibrationD1D2();
	CalibrationD1D2(const Config &_config);
	~CalibrationD1D2();

	void get_data(data_for_D1D2_calibration _single_event_data);
	void tell_no_of_events();
	void solve_lr_ambiguity(const CalibrationLayerD1D2 &layer1, const CalibrationLayerD1D2 &layer2);
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
	TCanvas* plot_chi2_pdf();
	TCanvas* plot_chi2(int _layer_no);
	TCanvas* plot_chi2_cut(int _layer_no);
	TCanvas* plot_chi2_pdf(int _layer_no);
	TCanvas* plot_delta();
	void fit_delta_projections();
	void apply_corrections();
	void plot_current_calibration();
	void set_no_of_iteration(double _no_of_iteration);
	void set_no_of_bin_in_event();
	void fill_angle_distribution();
	TCanvas* plot_angle_distribution();
	TCanvas* plot_angle_distribution(int _layer_no);
	bool was_correct_angle(double track_angle);
	void set_pos_Xerr();
	void fit_in_3d();
	void fit_events();
	double calculate_phi_xz();
	double calculate_theta_y();

private:
	bool fit_with_inclined;
	bool unbiased_fit;
	CalibrationLayerD1D2 *Layer[14];
	int no_of_iteration;
	int no_of_calib_bins;
	int no_of_corr_bins;
	double max_time_range;
	double calib_bin_width;
	double corr_bin_width;
	TH1F *phi_xz;
	TH1F *theta_y;
	TH1F *chi2;
	TH1F *chi2_no_cut;
	TH1F *chi2_pdf;
	TH1F *chi2_pdf_no_cut;
	TH1F *angle_distribution;
	TH1F *angle_distribution_no_cut;
	TH1F *layer_phi_xz[14];
	TH1F *layer_theta_y[14];
	TH1F *layer_chi2[14];
	TH1F *layer_chi2_no_cut[14];
	TH1F *layer_chi2_pdf[14];
	TH1F *layer_chi2_pdf_no_cut[14];
	TH1F *layer_angle_distribution[14];
	TH1F *layer_angle_distribution_no_cut[14];
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
	double D1_x_lab_position;
	double D1_z_lab_position;
	double D2_x_lab_position;
	double D2_z_lab_position;
	double distance_to_1st_layer;
};

#endif

// ;>