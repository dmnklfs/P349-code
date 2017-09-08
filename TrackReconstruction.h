#ifndef TRACKRECONSTRUCTION_H
#define TRACKRECONSTRUCTION_H

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
#include "Fit3d_HEX.h"
#include "Fit3d_D2.h"
#include "Fit3d.h"
//#include "TrackReconstructionLayer.h"
#include <TMath.h>

struct track_reco_data
{
	double x_hit_pos_D1[8];
	double x_err_hit_pos_D1[8];
	double z_hit_pos_D1[8];
	double chi2_D1, phi_xz_D1, theta_yz_D1;
	bool errflag_D1;

	double x_hit_pos_D2[6];
	double x_err_hit_pos_D2[6];
	double z_hit_pos_D2[6];
	double chi2_D2, phi_xz_D2, theta_yz_D2;
	bool errflag_D2;

	double x_hit_pos_HEX[7];
	double x_err_hit_pos_HEX[7];
	double z_hit_pos_HEX[7];
	double chi2_HEX, phi_xz_HEX, theta_yz_HEX;
	bool errflag_HEX;

	TVector3 track3d_fit_point_D1, track3d_fit_vector_D1;
	TVector3 track3d_fit_point_D2, track3d_fit_vector_D2;
	TVector3 track3d_fit_point_HEX, track3d_fit_vector_HEX;

	track_reco_data() // make correct init for errflags
	{
		chi2_D1 = -1;
		chi2_D2 = -1;
		chi2_HEX = -1;
		phi_xz_D1 = -1;
		theta_yz_D1 = -1;
		phi_xz_D2 = -1;
		theta_yz_D2 = -1;
		phi_xz_HEX = -1;
		theta_yz_HEX = -1;
	}
};

class TrackReconstruction
{
public:

	TrackReconstruction();
	TrackReconstruction(const Config &_config);
	~TrackReconstruction();

	void get_data(data_for_track_reconstruction _single_event_data);
	void tell_no_of_events();
	void fit_events_in_D1();
	void fit_in_3d_D1();
	void fit_events_in_D2();
	void fit_in_3d_D2();
	void fit_events_in_HEX();
	void fit_in_3d_HEX();
	void deletations();

	double calculate_phi_xz(double vx, double vz);
	double calculate_theta_yz(double vy, double vz);

	void plot_D1_d2_phi_corr();
	void save_histos();

	void set_detectors_positions_on_vectors();
	void set_detectors_positions_on_points();
	void reconstructed_D2_vs_expected_D1(); // expected in D2 from reconstruction in D1

private:
	TH1F *D1_phi, *D1_theta, *D2_phi, *D2_theta;
	TH2F *D1D2_phi_corr;
	TH2F *D1D2_theta_corr;
	TH1F *D1_chisq, *D2_chisq;
	TH2F *D1HEX_phi_corr;
	TH2F *x_reco_D2_exp_D1;
	TH2F *y_reco_D2_exp_D1;
	TH1F *x_reco_D2_minus_exp_D1;
	TH1F *y_reco_D2_minus_exp_D1;


	std::vector<track_reco_data> TrackRecoData;

	double half_x_dim_D1;
	double half_x_dim_D2;
	double half_x_dim_HEX;
	double half_z_dim_D1;
	double half_z_dim_D2;
	double half_z_dim_HEX;
	double x_lab_position_D1;
	double x_lab_position_D2;
	double x_lab_position_HEX;
	double z_lab_position_D1;
	double z_lab_position_D2;
	double z_lab_position_HEX;
};

#endif

// ;>