#include "UncorrelatedOpt.h"

UncorrelatedOpt * UncorrelatedOpt::_this = NULL;

UncorrelatedOpt * UncorrelatedOpt::GetInstance(){ 
  if( _this == NULL ){
    _this = new UncorrelatedOpt();
  }
  return _this; 
}

UncorrelatedOpt::UncorrelatedOpt()
{
	no_of_points = 8;
}

void UncorrelatedOpt::set_z_values(double *_z)
{
	for (int i = 0; i < 8; i++)
	{
		z[i] = _z[i];
	}
	zp = 0;//z[0]-20;
}

void UncorrelatedOpt::set_x_straight_values(double *_x)
{
	for (int i = 0; i < 4; i++)
	{
		x[i] = _x[i];
	}
}

void UncorrelatedOpt::set_incl_hit_lines_params(double *_a, double *_b)
{
	for (int i = 0; i < 4; i++)
	{
		a[i] = _a[i];
		b[i] = _b[i];
	}
}

void UncorrelatedOpt::set_track_point(double _track_x, double _track_y, double _track_z)
{
	initTrackPoint.SetX(_track_x);
	initTrackPoint.SetY(_track_y);
	initTrackPoint.SetZ(_track_z);
}

void UncorrelatedOpt::set_track_vector(double _track_ux, double _track_uy, double _track_uz)
{
	initTrackVector.SetX(_track_ux);
	initTrackVector.SetY(_track_uy);
	initTrackVector.SetZ(_track_uz);
}

bool UncorrelatedOpt::err_flag()
{
	return errflag;
}


double UncorrelatedOpt::GlobalFCN(const double * par)
{
	const int points = no_of_points;
	//calculate chisquare
	double chisq = 0;
	double delta = 0;
	int straight[4];
//	int inclined[4];
	straight[0] = 0;
	straight[1] = 1;
//	inclined[0] = 2;
//	inclined[1] = 3;
//	inclined[2] = 4;
//	inclined[3] = 5;
	straight[2] = 6;
	straight[3] = 7;

	TVector3 newTrackPoint, newTrackVector;
	TVector3 xz_plane;
	xz_plane.SetXYZ(1,0,1);
	ac_1 = initTrackVector.Cross(xz_plane);
	ac_1.Unit();
	ac_2 = initTrackVector.Cross(ac_1);
	ac_2.Unit();

	newTrackPoint = initTrackPoint + par[0]*ac_1 + par[1]*ac_2;
	newTrackVector = initTrackVector + par[2]*ac_1 + par[3]*ac_2;
	double ntv_z = newTrackVector.Z();
	newTrackVector.SetX(newTrackVector.X()/ntv_z);
	newTrackVector.SetY(newTrackVector.Y()/ntv_z);
	newTrackVector.SetZ(newTrackVector.Z()/ntv_z);

	// scaling
	double t;
	// points in which the line goes through the certain z plane
	double xi, yi;
	for (int i = 0; i < 4; i++)
	{
		//std::cout << errors[i] << std::endl;
		//delta  = (((y[i]-par[1])/par[0])-x[i])/errors[i];
		t = z[ straight[i] ] - zp;//TMath::Abs(z[ straight[i] ] - zp);
		xi = t*newTrackVector.X() + newTrackPoint.X();
		yi = t*newTrackVector.Y() + newTrackPoint.Y();
		delta  = x[i] - xi;
		chisq += delta*delta;
	}

	for (int i = 0; i < 4; i++)
	{
		t = z[2+i] - zp;//TMath::Abs(z[2+i] - zp); // 1st inclined layer no = 2 (3rd layer counting in the beam direction)
		xi = t*newTrackVector.X() + newTrackPoint.X();
		yi = t*newTrackVector.Y() + newTrackPoint.Y();
		delta  = (a[i]*xi-yi+b[i])*(a[i]*xi-yi+b[i])/(a[i]*a[i]+1);
		//std::cout << "delta: " << delta << std::endl;
		chisq += delta;
	}
	//std::cout << "chisq " << chisq << std::endl;
	return chisq;
}

double UncorrelatedOpt::get_chisq()
{
	double chisq = 0;
	double delta = 0;
	int straight[4];
	straight[0] = 0;
	straight[1] = 1;
	straight[2] = 6;
	straight[3] = 7;

	// scaling
	double t;
	// points in which the line goes through the certain z plane
	double xi, yi;
	for (int i=0;i<4; i++)
	{
		//std::cout << errors[i] << std::endl;
		//delta  = (((y[i]-par[1])/par[0])-x[i])/errors[i];
		t = z[ straight[i] ] - zp;//TMath::Abs(z[ straight[i] ] - zp);
		xi = t*fTrackVector.X()/fTrackVector.Z() + fTrackPoint.X();
		yi = t*fTrackVector.Y()/fTrackVector.Z() + fTrackPoint.Y();
		delta  = x[i] - xi;
		chisq += delta*delta;
	}

	for (int i = 0; i < 4; i++)
	{
		t = z[2+i] - zp;//TMath::Abs(z[2+i] - zp); // 1st inclined layer no = 2 (3rd layer counting in the beam direction)
		xi = t*fTrackVector.X()/fTrackVector.Z() + fTrackPoint.X();
		yi = t*fTrackVector.Y()/fTrackVector.Z() + fTrackPoint.Y();
		delta  = (a[i]*xi-yi+b[i])*(a[i]*xi-yi+b[i])/(a[i]*a[i]+1);
		//std::cout << "delta: " << delta << std::endl;
		chisq += delta;
	}
	// std::cout << "chisq " << chisq << std::endl;
	return chisq;
}

void hfcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
	UncorrelatedOpt * rec = UncorrelatedOpt::GetInstance();
	f = rec->GlobalFCN( par ); 
}

// void UncorrelatedOpt::calculate_start_params()
// {
// 	double t;
// 	t = 1/track_uz;
// 	start_ux = t*track_ux;
// 	start_uy = t*track_uy;

// 	t = (zp - track_z)/track_uz;
// 	start_xp = track_x + t*track_ux;
// 	start_yp = track_y + t*track_uy;
// }

void UncorrelatedOpt::fit_with_minuit()
{
	errflag = true;
	std::vector<double> output;
	TMinuit *gMinuit = new TMinuit(7);  //initialize TMinuit with a maximum of 5 params
	gMinuit->SetFCN(hfcn);
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
	double vstart[4] = {0, 0, 0, 0};
	double step[4] = {0.01 , 0.01, 0.001, 0.001};
	gMinuit->mnparm(0, "p_ac1", vstart[0], step[0], 0, 0, ierflg);
	gMinuit->mnparm(1, "p_ac2", vstart[1], step[1], 0, 0, ierflg);
	gMinuit->mnparm(2, "v_ac1", vstart[2], step[2], 0, 0, ierflg);
	gMinuit->mnparm(3, "v_ac2", vstart[3], step[3], 0, 0, ierflg);

	arglist[0] = 500; //was 500
	arglist[1] = 1.;
	gMinuit->mnexcm("MINIMIZE", arglist ,1,ierflg);
	errflag = ierflg; // IERFLG=0 if no problems

	// acces the results
	TString name[4];
	name[0] = "p_ac1";
	name[1] = "p_ac2";
	name[2] = "v_ac1";
	name[3] = "v_ac2";

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

	fTrackPoint = initTrackPoint+params[0]*ac_1+params[1]*ac_2;
	fTrackVector = initTrackVector+params[2]*ac_1+params[3]*ac_2;

	delete gMinuit;
}

TVector3 UncorrelatedOpt::return_track_point()
{
	return fTrackPoint;
}

TVector3 UncorrelatedOpt::return_track_vector()
{
	return fTrackVector;
}