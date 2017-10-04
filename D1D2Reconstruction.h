#ifndef D1D2RECONSTRUCTION_H
#define D1D2RECONSTRUCTION_H

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
#include <string>
#include "struct.h"
#include "Config.h"
#include "MinuitFit.h"
#include "FitD1D2.h"
#include "Fit3d_D2.h"
#include "Fit3d.h"
#include <TMath.h>

struct d1d2_reco_data
{
	double x_hit_pos[14];
	double x_err_hit_pos[14];
	double z_hit_pos[14];
	double chi2, phi_xz, theta_yz;
	bool errflag;

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

	TVector3 track3d_fit_point, track3d_fit_vector;
	TVector3 track3d_fit_point_D1, track3d_fit_vector_D1;
	TVector3 track3d_fit_point_D2, track3d_fit_vector_D2;

	d1d2_reco_data() // make correct init for errflags
	{
		chi2_D1 = -1;
		chi2_D2 = -1;
		chi2 = -1;
		phi_xz_D1 = -1;
		theta_yz_D1 = -1;
		phi_xz_D2 = -1;
		theta_yz_D2 = -1;
		phi_xz = -1;
		theta_yz = -1;
		errflag = 1;
	}
};

class D1D2Reconstruction
{
public:

	D1D2Reconstruction();
	D1D2Reconstruction(const Config &_config);
	~D1D2Reconstruction();

	void get_data(data_for_track_reconstruction _single_event_data);
	void tell_no_of_events();
	void fit_in_3d_D1();
	void fit_in_3d_D2();
	void fit();
	void deletations();

	double get_mean_chisq();

	double calculate_phi_xz(double vx, double vz);
	double calculate_theta_yz(double vy, double vz);

	void plot_D1_d2_phi_corr();
	void save_histos();

	void set_x_offset(double xoffset);
	void set_z_offset(double zoffset);
	void set_y_offset(double yoffset);
	//void set_detectors_shift_on_D2_vectors(double xshift, double zshift); remove? 20.09.2017
	void reconstructed_D2_vs_expected_D1(); // expected in D2 from reconstruction in D1

private:
	TH1F *D1_chisq, *D2_chisq, *chisq, *chisq_ndf, *probability, *chi2_resc, *chi2_resc_cut, *probability_cut;
	TH1F *D1_phi, *D1_theta, *D2_phi, *D2_theta, *phi, *theta;
	TH2F *D1D2_phi_corr, *D1D2_theta_corr;
	TH2F *x_reco_D2_exp_D1, *y_reco_D2_exp_D1;
	TH1F *x_reco_D2_minus_exp_D1, *y_reco_D2_minus_exp_D1;

	std::vector<d1d2_reco_data> TrackRecoData;

	double half_x_dim_D1;
	double half_x_dim_D2;
	double half_z_dim_D1;
	double half_z_dim_D2;

	double x_lab_position_D1;
	double x_lab_position_D2;
	double z_lab_position_D1;
	double z_lab_position_D2;

	double D2_x_offset, D2_z_offset, D2_y_offset;
};

#endif

// ;>