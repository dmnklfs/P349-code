#include "MinuitFit.h"

MinuitFit * MinuitFit::_this = NULL;

MinuitFit * MinuitFit::GetInstance(){ 
  if( _this == NULL ){
    _this = new MinuitFit();
  }
  return _this; 
}

MinuitFit::MinuitFit()
{
	no_of_points = 8;
	for (int i = 0; i < 8; i++)
	{
		x[i] = 0;
		z[i] = 0;
		errors[i] = 10000;
	}
}

void MinuitFit::set_no_of_points(int npoints)
{
	no_of_points = npoints;
}


void MinuitFit::set_values(double *_x, double *_y, double *_errors)
{
	for (int i = 0; i < no_of_points; i++)
	{
		x[i] = _x[i];
		z[i] = _z[i];
		errors[i] = _errors[i];
	}
	zp = -z[0] - 20;
}

bool MinuitFit::err_flag()
{
	return errflag;
}


double MinuitFit::GlobalFCN(const double * par)
{
	const int points = no_of_points;
	int i;
	//calculate chisquare
	double chisq = 0;
	double delta;
	double straight[4];
	double inclined[4];
	straight[0] = 0;
	straight[1] = 1;
	inclined[0] = 2;
	inclined[1] = 3;
	inclined[2] = 4;
	inclined[3] = 5;
	straight[2] = 6;
	straight[3] = 7;

	// scaling
	double t;
	// points in which the line goes through the certain z plane
	for (i=0;i<4; i++)
	{
		//std::cout << errors[i] << std::endl;
		//delta  = (((y[i]-par[1])/par[0])-x[i])/errors[i];
		t = TMath::Abs(z[i] - zp);
		delta  = ;
		chisq += delta*delta;
	}
	//std::cout << "chisq " << chisq << std::endl;
	return chisq;
}

void gfcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
	MinuitFit * rec = MinuitFit::GetInstance();
	f = rec->GlobalFCN( par ); 
}

std::vector<double> MinuitFit::fit_with_minuit()
{
	errflag = true;
	std::vector<double> output;
	TMinuit *gMinuit = new TMinuit(5);  //initialize TMinuit with a maximum of 5 params
	gMinuit->SetFCN(gfcn);
	gMinuit->SetPrintLevel(-1);

	Double_t arglist[10];
	Int_t ierflg = 0;

	arglist[0] = 2;
	gMinuit->mnexcm( "SET STR", arglist, 2,ierflg );

	arglist[0] = 1;
	gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

	// Set starting values and step sizes for parameters
	
	//double vstart[2] = {0.5, 1};
	double vstart[2] = {a_start, b_start};
	double step[2] = {0.1 , 0.1};
	gMinuit->mnparm(0, "a", vstart[0], step[0], 0, 0, ierflg);
	gMinuit->mnparm(1, "b", vstart[1], step[1], 0, 0, ierflg);

	arglist[0] = 500; //was 500
	arglist[1] = 1.;
	gMinuit->mnexcm("MINIMIZE", arglist ,2,ierflg);

	errflag = ierflg; // IERFLG=0 if no problems

	// acces the results
	TString namea = "a";
	TString nameb = "b";
	Double_t val, err, llim, ulim;
	Int_t  aaa;
	double *params = new double[2];
	gMinuit->mnpout( 0, namea, val, err, llim, ulim, aaa );
	params[0] = val;
	gMinuit->mnpout( 1, nameb, val, err, llim, ulim, aaa );
	params[1] = val;

	double chisq=0;
	double delta=0;
	int i;
	int points =no_of_points;

	for (i=0;i<points; i++)
	{
		delta  = (((y[i]-params[1])/params[0])-x[i])/errors[i];
		chisq += delta*delta;
	}
	
	output.push_back(params[0]);
	output.push_back(params[1]);
	output.push_back(chisq);

	delete gMinuit;

	return output;
}

