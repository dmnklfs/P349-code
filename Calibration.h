#ifndef CALIBRATION_H
#define CALIBRATION_H

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
#include "CalibrationLayer.h"

class Calibration
{
public:

	Calibration();
	Calibration(const Config &_config);
	~Calibration();

	void get_data(data_for_D1_calibration _single_event_data);
	void tell_no_of_events();
	void solve_lr_ambiguity(const CalibrationLayer &layer1, const CalibrationLayer &layer2);
	void calculate_hit_position();
	void fill_histograms(double _chi2_cut);
	void fit_events_in_straight_layers();
	void set_values_of_track_projections_params();
	void deletations();

private:
	CalibrationLayer *Layer[8];
	int no_of_iterations;
	int no_of_calib_bins;
	int no_of_corr_bins;
	double max_time_range;
	double calib_bin_width;
	double corr_bin_width;

	// a, b track parameters in the frames of each set of layers (straight, Pl - +31, M - -31)
	std::vector<double> StraightLayersTracks_apar;
	std::vector<double> StraightLayersTracks_bpar;
	std::vector<double> InclinedLayersPlTracks_apar;
	std::vector<double> InclinedLayersPlTracks_bpar;
	std::vector<double> InclinedLayersMTracks_apar;
	std::vector<double> InclinedLayersMTracks_bpar;

	
};

#endif

// ;>