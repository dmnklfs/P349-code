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
#include <TMath.h>
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
#include "TrackCalc.h"
#include "FitToLines.h"

struct d1d2_3d_data
{
	double x_hit_pos[14];
	double x_err_hit_pos[14];
	double z_hit_pos[14];
	double chi2, phi_xz, theta_yz;
	bool errflag;
	int take_to_mean;

	//delme
//	double wire_posX[7];
//	double wire_posZ[7];
//	double drift_time[7];
//	double wire_number[7];

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

	TVector3 HitPoints[14], HitVectors[14];
	TVector3 ApproxTrackPoint, ApproxTrackVector;
	TVector3 TrackPoint, TrackVector;

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
		take_to_mean = -1;
		errflag = 1;
		take_to_mean = -1;
	}
};

/*struct wire
{
	std::vector<double> DriftTime;
	std::vector<double> Distance;
};*/

class D1D23d
{
public:

	D1D23d();
	D1D23d(const Config &_config);
	~D1D23d();

	void get_data(data_for_track_reconstruction _single_event_data);
	void tell_no_of_events();
	void calculate_init_params();
	void set_config_positions();
	void rotateD1(double _ax, double _ay, double _az);
	void rotateD2(double _ax, double _ay, double _az);
	void shiftD1(double _sx, double _sy, double _sz, bool change_lab);
	void shiftD2(double _sx, double _sy, double _sz, bool change_lab);
	void fit_in_3d();
	void fill_histos();
	double calculate_phi_xz(double vx, double vz);
	double calculate_theta_yz(double vy, double vz);
	void calibrate_wires_HEX();


	void deletations();

	double get_mean_chisq();
	void save_histos();

	double draw_chambers(int event_no);

private:
	TH1F *chi2, *chi2_resc, *phi, *theta;
	TH1F *calc_px, *calc_py, *calc_pz, *calc_vx, *calc_vy, *calc_vz;
	TH1F *track_px, *track_py, *track_pz, *track_vx, *track_vy, *track_vz;

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

	double x_lab_position_HEX;
	double z_lab_position_HEX;  

	TVector3 D1point, D2point;
	TVector3 D1vectorX, D1vectorY, D1vectorZ, D2vectorX, D2vectorY, D2vectorZ;
	// obroty wzgledem osi komory
	double D1_x_rot, D1_y_rot, D1_z_rot;
	double D2_x_rot, D2_y_rot, D2_z_rot;

	//wire hex_data[7];
	


};

#endif

// ;>