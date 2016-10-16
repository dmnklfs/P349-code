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
#include <fstream>
#include <string>
#include <sstream>



class MinuitFit
{
public:
	MinuitFit();
	//MinuitFit(double *_x, double *_y, double *_errors);
	static MinuitFit * GetInstance();
	~MinuitFit(){ _this = NULL; }
	double GlobalFCN(const double * par);
	std::vector<double> fit_with_minuit();
	void set_values(double *_x, double *_y, double *_errors);

private:
	static MinuitFit * _this;
	double x[4], y[4], errors[4];
	

	
};

#endif