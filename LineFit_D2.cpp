#include "LineFit_D2.h"

LineFit_D2 * LineFit_D2::_this = NULL;

LineFit_D2 * LineFit_D2::GetInstance(){ 
  if( _this == NULL ){
    _this = new LineFit_D2();
  }
  return _this; 
}

LineFit_D2::LineFit_D2()
{
	no_of_points = 6;
	excluded_layer = -1;
}

void LineFit_D2::set_z_values(double *_z)
{
	for (int i = 0; i < 6; i++)
	{
		z[i] = _z[i];
	}
	zp = 0;//z[0]-20;
}

void LineFit_D2::set_x_straight_values(double *_x)
{
	for (int i = 0; i < 2; i++)
	{
		x[i+4] = _x[i+4];
	}
}

void LineFit_D2::set_x_errors(double *_errors)
{
	for (int i = 0; i < 6; i++)
	{
		errors[i] = _errors[i];
	}
	for (int i = 0; i < 4; i++)
	{
		if (errors[i]!=1) errors[i] = a[i]/(pow(a[i]*a[i]+1,0.5)*TMath::Cos(31*TMath::DegToRad()))*errors[2+i];
	}

}

void LineFit_D2::set_incl_hit_lines_params(double *_a, double *_b)
{
	for (int i = 0; i < 4; i++)
	{
		a[i] = _a[i];
		b[i] = _b[i];
	}
}

void LineFit_D2::set_track_point(double _track_x, double _track_y, double _track_z)
{
	track_x = _track_x;
	track_y = _track_y;
	track_z = _track_z;
}

void LineFit_D2::set_track_vector(double _track_ux, double _track_uy, double _track_uz)
{
	track_ux = _track_ux;
	track_uy = _track_uy;
	track_uz = _track_uz;
	//std::cout << track_ux << std::endl;
	//std::cout << track_uy << std::endl;
	//std::cout << track_uz << std::endl;
}

void LineFit_D2::set_excluded_layer(int _excluded_layer)
{
	excluded_layer = _excluded_layer;
}

bool LineFit_D2::err_flag()
{
	return errflag;
}


double LineFit_D2::GlobalFCN(const double * par)
{
	const int points = no_of_points;
	int i;
	//calculate chisquare
	double chisq = 0;
	double delta = 0;
	
	double layer_chisq[6];
	int straight[2];
//	int inclined[4];
	straight[0] = 4;
	straight[1] = 5;

	// scaling
	double t;
	// points in which the line goes through the certain z plane
	double xi, yi;
		// === calculation of deltas*delta for all layers separately ===
	// straight
	// layer 5
	t = z[4] - zp;
	xi = t*par[2] + par[0];
	yi = t*par[3] + par[1];
	delta  = x[0] - xi;
	layer_chisq[4] = (delta*delta)/(errors[0]*errors[0]);
	// layer 6
	t = z[5] - zp;
	xi = t*par[2] + par[0];
	yi = t*par[3] + par[1];
	delta  = x[1] - xi;
	layer_chisq[5] = (delta*delta)/(errors[1]*errors[1]);

	for (int i = 0; i < 4; i++)
	{
		t = z[i] - zp;
		xi = t*par[2] + par[0];
		yi = t*par[3] + par[1];
		delta  = (a[i]*xi-yi+b[i])*(a[i]*xi-yi+b[i])/(a[i]*a[i]+1);
		layer_chisq[i] = delta/(errors[i]*errors[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		if (i!=excluded_layer) chisq = chisq + layer_chisq[i];
	}
	return chisq;
}

double LineFit_D2::get_chisq()
{
	double chisq = 0;
	double layer_chisq[8];
	double delta = 0;
	int straight[2];
	straight[0] = 4;
	straight[1] = 5;

	double par[4];
	par[0] = xp;
	par[1] = yp;
	par[2] = ux;
	par[3] = uy; 
	// here it is ok - uz=1

	// scaling
	double t;
	// points in which the line goes through the certain z plane
	double xi, yi;
	// straight
	// layer 1
	t = z[4] - zp;
	xi = t*par[2] + par[0];
	yi = t*par[3] + par[1];
	delta  = x[0] - xi;
	layer_chisq[0] = (delta*delta)/(errors[0]*errors[0]);
	// layer 2
	t = z[5] - zp;
	xi = t*par[2] + par[0];
	yi = t*par[3] + par[1];
	delta  = x[1] - xi;
	layer_chisq[1] = (delta*delta)/(errors[1]*errors[1]);

	for (int i = 0; i < 4; i++)
	{
		t = z[i] - zp;
		xi = t*par[2] + par[0];
		yi = t*par[3] + par[1];
		delta  = (a[i]*xi-yi+b[i])*(a[i]*xi-yi+b[i])/(a[i]*a[i]+1);
		layer_chisq[i] = delta/(errors[i]*errors[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		if (i!=excluded_layer) chisq = chisq + layer_chisq[i];
	}
	return chisq;
}

void d2fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
	LineFit_D2 * rec = LineFit_D2::GetInstance();
	f = rec->GlobalFCN( par ); 
}

void LineFit_D2::calculate_start_params()
{
	double t;
	t = 1/track_uz;
	start_ux = t*track_ux;
	//std::cout << "ux " << start_ux << std::endl;
	start_uy = t*track_uy;

	t = (zp - track_z)/track_uz;
	start_xp = track_x + t*track_ux;
	start_yp = track_y + t*track_uy;
}

void LineFit_D2::fit_with_minuit()
{
	errflag = true;
	std::vector<double> output;
	TMinuit *gMinuit = new TMinuit(7);  //initialize TMinuit with a maximum of 5 params
	gMinuit->SetFCN(d2fcn);
	gMinuit->SetPrintLevel(-1);

	Double_t arglist[10];
	Int_t ierflg = 0;

	// set strategy - about no of calls during minimization
	// 0 - optimize time, less calls
	// 1 - normal
	// 2 - optimize result, time consuming (wasted calls)
	arglist[0] = 2;
	gMinuit->mnexcm( "SET STR", arglist, 1,ierflg );

	// Sets the value of up (default value= 1.), defining parameter errors.
	// MINUIT defines parameter errors as the change in parameter value required to change the function value by up.
	// Normally, for chisquared fits up=1, and for negative log likelihood, up=0.5.
	arglist[0] = 1;
	gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);

	// Set start values and step sizes for parameters
	double vstart[4] = {start_xp, start_yp, start_ux, start_uy};
	double step[4] = {0.01 , 0.01, 0.001, 0.001};
	gMinuit->mnparm(0, "xp", vstart[0], step[0], 0, 0, ierflg);
	gMinuit->mnparm(1, "yp", vstart[1], step[1], 0, 0, ierflg);
	gMinuit->mnparm(2, "ux", vstart[2], step[2], 0, 0, ierflg);
	gMinuit->mnparm(3, "uy", vstart[3], step[3], 0, 0, ierflg);

	arglist[0] = 500; //was 500
	arglist[1] = 1.;
	gMinuit->mnexcm("MINIMIZE", arglist ,1,ierflg);
	errflag = ierflg; // IERFLG=0 if no problems

	// acces the results
	TString name[4];
	name[0] = "xp";
	name[1] = "yp";
	name[2] = "ux";
	name[3] = "uy";

	Double_t val, err, llim, ulim;
	Int_t  aaa;
	double *params = new double[4];
	gMinuit->mnpout( 0, name[0], val, err, llim, ulim, aaa );
	params[0] = val;
	gMinuit->mnpout( 1, name[1], val, err, llim, ulim, aaa );
	params[1] = val;
	gMinuit->mnpout( 2, name[2], val, err, llim, ulim, aaa );
	params[2] = val;
	gMinuit->mnpout( 3, name[3], val, err, llim, ulim, aaa );
	params[3] = val;

//	double chisq=0;
//	double delta=0;
//	int i;
//	int points =no_of_points;

//	for (i=0;i<points; i++)
//	{
//		delta  = (((y[i]-params[1])/params[0])-x[i])/errors[i];
//		chisq += delta*delta;
//	}
	
	xp = params[0];
	yp = params[1];
	ux = params[2];
	uy = params[3];
	uz = 1;

	delete gMinuit;
}

TVector3 LineFit_D2::return_track_point()
{
	TVector3 track_point;
	track_point.SetX(xp);
	track_point.SetY(yp);
	track_point.SetZ(zp);
	//std::cout << "p1 " << xp << std::endl;
	//std::cout << "p2 " << yp << std::endl;
	//std::cout << "p3 " << zp << std::endl;
	return track_point;
}

TVector3 LineFit_D2::return_track_vector()
{
	TVector3 track_vector;
	track_vector.SetX(ux);
	track_vector.SetY(uy);
	track_vector.SetZ(uz);
	track_vector.Unit();
	return track_vector;
}