#ifndef D1D23D_H
#define D1D23D_H

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
#include "FitToLines.h"
#include <TMath.h>

struct d1d2_3d_data
{
	double x_hit_pos[14];
	double x_err_hit_pos[14];
	double z_hit_pos[14];
	double chi2, phi_xz, theta_yz;
	bool errflag;

//	double x_hit_pos_D1[8];
//	double x_err_hit_pos_D1[8];
//	double z_hit_pos_D1[8];
//	double chi2_D1, phi_xz_D1, theta_yz_D1;
//	bool errflag_D1;
//
//	double x_hit_pos_D2[6];
//	double x_err_hit_pos_D2[6];
//	double z_hit_pos_D2[6];
//	double chi2_D2, phi_xz_D2, theta_yz_D2;
//	bool errflag_D2;

	TVector3 track3d_fit_point, track3d_fit_vector;
//	TVector3 track3d_fit_point_D1, track3d_fit_vector_D1;
//	TVector3 track3d_fit_point_D2, track3d_fit_vector_D2;

	d1d2_3d_data() // make correct init for errflags
	{
//		chi2_D1 = -1;
//		chi2_D2 = -1;
		chi2 = -1;
//		phi_xz_D1 = -1;
//		theta_yz_D1 = -1;
//		phi_xz_D2 = -1;
//		theta_yz_D2 = -1;
		phi_xz = -1;
		theta_yz = -1;
	}
};

class D1D23d
{
public:

	D1D23d();
	D1D23d(const Config &_config);
	~D1D23d();

	void get_data(data_for_track_reconstruction _single_event_data);
	void tell_no_of_events();
//	void fit_in_3d_D1();
//	void fit_in_3d_D2();
	void fit();
	void deletations();

	double get_mean_chisq();

	double calculate_phi_xz(double vx, double vz);
	double calculate_theta_yz(double vy, double vz);

//	void plot_D1_d2_phi_corr();
	void save_histos();

	void set_x_offset(double xoffset);
	void set_y_offset(double yoffset);
	void set_z_offset(double zoffset);

	void Save_histos();

private:
	TH1F *chi2, *chi2_resc, *phi, *theta;
	TH1F *calc_px, *calc_py, *calc_pz, *calc_vx, *calc_vy, *calc_vz;

	std::vector<d1d2_3d_data> TrackRecoData;

	double half_x_dim_D1;
	double half_x_dim_D2;
	double half_z_dim_D1;
	double half_z_dim_D2;

	double x_lab_position_D1;
	double x_lab_position_D2;
	double y_lab_position_D1;
	double y_lab_position_D2;
	double z_lab_position_D1;
	double z_lab_position_D2;

	// obroty wzgledem osi komory
	double D1_x_rot, D1_y_rot, D1_z_rot;
	double D2_x_rot, D2_y_rot, D2_z_rot;

	TVector3 ApproxTrackPoint, ApproxTrackVector;
};

#endif

// ;>