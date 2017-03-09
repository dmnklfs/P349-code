#ifndef LINEFITUNBIASED_H
#define LINEFITUNBIASED_H 

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

class LineFitUnbiased
{
public:
	LineFitUnbiased();
	static LineFitUnbiased * GetInstance();
	~LineFitUnbiased(){ _this = NULL; }
	double GlobalFCN(const double * par);
	void fit_with_minuit();
	void set_z_values(double *_z);
	void set_x_straight_values(double *_x);
	void set_x_errors(double *_xerrors);
	void set_incl_hit_lines_params(double *_a, double *_b);
	void set_track_point(double _track_x, double _track_y, double _track_z);
	void set_track_vector(double _track_ux, double _track_uy, double _track_uz);
	void calculate_start_params();
	void set_excluded_layer(int _excluded_layer);

	TVector3 return_track_point(int _layer);
	TVector3 return_track_vector(int _layer);
	double get_chisq();

	bool err_flag();

private:
	int no_of_points;
	static LineFitUnbiased * _this;
	int excluded_layer;
	// z positions of all layers - common
	double z[8];
	// points - for straight layers
	double x[4], errors[8];
	// hit equations - fo inclined layers
	double a[4], b[4];

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
	double xp[8], yp[8], zp[8];
	double ux[8], uy[8], uz[8];

	double chisq[8];
};

#endif