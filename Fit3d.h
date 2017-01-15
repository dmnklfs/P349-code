#ifndef FIT3D_H
#define FIT3D_H 

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
#include "MinuitFit.h"

class Fit3d
{
public:
	Fit3d();
	~Fit3d();
	void set_values(double *_x, double *_y, double *_errors);
	void fit_straight_layer();
	void fit_inclined_layers();

private:
	double x_straight[4],  z_straight[4],  errors_straight[4];
	double x_inclined1[2], z_inclined1[2], errors_inclined1[2];
	double x_inclined2[2], z_inclined2[2], errors_inclined2[2];
	
	double z_x_a[3], z_x_b[3]; // 0 - straight, 1 - inclined \, 2 - inclined /
	
};


#endif