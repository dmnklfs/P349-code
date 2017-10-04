#ifndef FITTOLINES_H
#define FITTOLINES_H 

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TMinuit.h"
#include <TGraph.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <TGaxis.h>
#include <TF1.h>
#include "TVector3.h"
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
#include <TMarker3DBox.h>
#include <TPolyLine3D.h>
#include "MinuitFit.h"
#include "LineFitD1D2.h"
#include "UncorrelatedOpt.h"
#include "TView3D.h"
#include "TView.h"
#include "TAxis3D.h"
#include <TPolyMarker3D.h>
//#include "GSLError.h"

struct line3d
{
	TVector3 point;
	TVector3 direction;
};

class FitToLines
{
public:
	FitToLines();
	static FitToLines * GetInstance();
	~FitToLines(){ _this = NULL; }
	double GlobalFCN(const double * par);
	void set_line(TVector3 _point, TVector3 _direction);
	void set_init_params(TVector3 _point, TVector3 _direction);
	void calculate_distances_to_lines();
	void set_z_reference(double _z_reference);
	void fit_with_minuit();
	double calculate_chisq();
	TVector3 get_track_vector();
	TVector3 get_track_point();
	bool err_flag();
	bool errflag;
private:
	
	static FitToLines * _this;
	int event_no;
	double z_reference;
	std::vector<line3d> LinesToFit;
	TVector3 InitTrackPoint, InitTrackVector;
	TVector3 TrackPoint, TrackVector;

};


#endif