#ifndef UNCORRELATEDOPT_H
#define UNCORRELATEDOPT_H 

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

class UncorrelatedOpt
{
public:
	UncorrelatedOpt();
	static UncorrelatedOpt * GetInstance();
	~UncorrelatedOpt(){ _this = NULL; }
	double GlobalFCN(const double * par);
	void fit_with_minuit();
	void set_z_values(double *_z);
	void set_x_straight_values(double *_x);
	void set_incl_hit_lines_params(double *_a, double *_b);
	void set_track_point(double _track_x, double _track_y, double _track_z);
	void set_track_vector(double _track_ux, double _track_uy, double _track_uz);
	void calculate_start_params();
	TVector3 return_track_point();
	TVector3 return_track_vector();
	double get_chisq();

	bool err_flag();

private:
	int no_of_points;
	static UncorrelatedOpt * _this;
	// z positions of all layers - common
	double z[8];
	// points - for straight layers
	double x[4], errors[4];
	// hit equations - fo inclined layers
	double a[4], b[4];

	bool errflag;

	// coordinates of the point which belongs to the track - from the previous method
	TVector3 initTrackPoint;
	// 3d track vector - from the previous method
	TVector3 initTrackVector;

	// correction axes
	TVector3 ac_1, ac_2;

	TVector3 fTrackPoint, fTrackVector;

	// starting params
	double start_xp, start_yp;
	double start_ux, start_uy;

	// results of the fit
	// coordinates of the point which belongs to the track - results of the fit
	double xp, yp, zp;
	double ux, uy, uz;
};

#endif