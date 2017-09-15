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
	no_of_points = 6;
}

void MinuitFit::set_no_of_points(int npoints)
{
	no_of_points = npoints;
}


void MinuitFit::set_values(double *_x, double *_y, double *_errors)
{
	std::cout << "set values " << std::endl;
	for (int i = 0; i < no_of_points; i++)
	{
		x[i] = _x[i];
		y[i] = _y[i];
		errors[i] = _errors[i];
		std::cout << "x[i] " << x[i] << " " << y[i] << " " << errors[i] << std::endl;
	}
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
	for (i=0;i<points; i++)
	{
		//std::cout << errors[i] << std::endl;
		delta  = (((y[i]-par[1])/par[0])-x[i])/errors[i];
		chisq += delta*delta;
		//std::cout << i << " delta " << delta << std::endl;
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
	gMinuit->mnexcm("SET ERR", arglist ,2,ierflg);

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

void MinuitFit::perform_simplified_fit()
{
	linear_fit = new TF1("linear_fit","[0]*x + [1]",x[0]-10,x[1]+10); // was x[10]
	linear_fit -> SetParameter(0,0.5);
	linear_fit -> SetParameter(1,1.0);
	linear_fit -> SetParName(0,"a");
	linear_fit -> SetParName(1,"b");
	linear_fit_graph = new TGraph(no_of_points,x,y);
	linear_fit_graph -> Fit(linear_fit, "Q");
	a_start = linear_fit -> GetParameter(0);
	b_start = linear_fit -> GetParameter(1);
	std::cout << "a" << a_start << " " << b_start << std::endl;
	delete linear_fit;
	delete linear_fit_graph;
}

void MinuitFit::perform_simplified_fit_calc_coeff()
{
	std::cout << " perform_simplified_fit_calc_coeff " << std::endl;
	double sx = 0;
	double sy = 0; 
	double sx2 = 0;
	double sxy = 0;
	for (int i = 0; i < no_of_points; i++)
	{
		std::cout << "x[i]" << x[i] << " y[i] " << y[i] << std::endl;
		sx  = sx  + x[i];
		sx2 = sx2 + x[i]*x[i];
		sy  = sy  + y[i];
		sxy = sxy + x[i]*y[i];
	}
	a_start = (no_of_points*sxy - sx*sy)*pow(no_of_points*sx2 - sx*sx ,-1);
	b_start = (sy - a_start*sx)*pow(no_of_points,-1);
	std::cout << "a " << a_start << " " << b_start << std::endl;

}