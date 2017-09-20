#ifndef LINEFITD1D2_H
#define LINEFITD1D2_H 

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
#include "P349_data.h"
#include <numeric>
#include <boost/filesystem.hpp>
#include <cmath>
#include <math.h> 
#include <fstream>
#include <string>
#include <sstream>
#include <TMath.h>
#include "TVector3.h"
//#include "GSLError.h"

class LineFitD1D2
{
public:
	LineFitD1D2();
	static LineFitD1D2 * GetInstance();
	~LineFitD1D2(){ _this = NULL; }
	double GlobalFCN(const double * par);
	void fit_with_minuit();
	void set_z_values(double *_z);
	void set_x_straight_values(double *_x);
	void set_x_errors(double *_xerrors);
	void set_incl_hit_lines_params(double *_a, double *_b);
	void set_track_point(double _track_x, double _track_y, double _track_z);
	void set_track_vector(double _track_ux, double _track_uy, double _track_uz);
	void set_excluded_layer(int _excluded_layer);
	void set_z_reference(double z);
	void calculate_start_params();
	TVector3 return_track_point();
	TVector3 return_track_vector();
	double get_chisq();

	bool err_flag();

private:
	int no_of_points;
	static LineFitD1D2 * _this;
	int excluded_layer;
	// z positions of all layers - common
	double z[14];
	// points - for straight layers
	double x[6], errors[14];
	// hit equations - fo inclined layers
	double a[8], b[8];

	bool errflag;

	// coordinates of the point which belongs to the track - from the previous method
	double track_x, track_y, track_z;
	// 3d track vector - from the previous method
	double track_ux, track_uy, track_uz;

	// starting params
	double start_xp, start_yp;
	double start_ux, start_uy;

	// results of the fit
	// coordinates of the point which belongs to the track - results of the fit
	double xp, yp, zp;
	double ux, uy, uz;
};

#endif