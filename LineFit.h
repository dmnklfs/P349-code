#ifndef MINUITFIT_H
#define MINUITFIT_H 

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

class LineFit
{
public:
	MinuitFit();
	static MinuitFit * GetInstance();
	~MinuitFit(){ _this = NULL; }
	double GlobalFCN(const double * par);
	std::vector<double> fit_with_minuit();
	void set_values(double *_x, double *_y, double *_errors);
	void set_no_of_hits(int nhits);
	void set_point_start_params(double _zp, double y_p, double zp_);
	void set_point_start_params(double _ux, double _uy, double _uz);

	bool err_flag();

private:
	int no_of_points;
	static MinuitFit * _this;
	double x[8], z[8], errors[8];
	bool errflag;

	// coordinates of the point which belongs to the track
	double start_zp, start_yp, start_zp;
	double start_ux, start_uy, start_uz;

	// coordinates of the point which belongs to the track
	double zp, yp, zp;
	double ux, uy, uz;

	// vector parallel to the track
	TVector3 track_vector;
};

#endif