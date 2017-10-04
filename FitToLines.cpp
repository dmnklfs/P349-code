#include "FitToLines.h"

FitToLines * FitToLines::_this = NULL;

FitToLines * FitToLines::GetInstance()
{ 
  if( _this == NULL )
  {
    _this = new FitToLines();
  }
  return _this; 
}

FitToLines::FitToLines(){  }

void d1d23dfcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
	FitToLines * rec = FitToLines::GetInstance();
	f = rec->GlobalFCN( par ); 
}

void FitToLines::set_line(TVector3 _point, TVector3 _direction)
{
	line3d aline;
	aline.point = _point;
	aline.direction = _direction;
	LinesToFit.push_back(aline);
}

void FitToLines::set_init_params(TVector3 _point, TVector3 _direction)
{
	InitTrackPoint = _point;
	InitTrackVector = _direction;
	InitTrackVector.SetX(InitTrackVector.X()*pow(InitTrackVector.Z(),-1));
	InitTrackVector.SetY(InitTrackVector.Y()*pow(InitTrackVector.Z(),-1));
	InitTrackVector.SetZ(InitTrackVector.Z()*pow(InitTrackVector.Z(),-1));
}

void FitToLines::set_z_reference(double _z_reference)
{
	z_reference = _z_reference;
}

double FitToLines::GlobalFCN(const double * par)
{
	const int points = LinesToFit.size();
	int i;
	//calculate chisquare
	double chisq = 0;
	double delta = 0;
	double zp, vz;
	double linex, liney, linez;
	vz = 1;
	zp = z_reference;
	TVector3 tpoint, tvector;
	tpoint.SetXYZ(par[0],par[1],z_reference);
	tvector.SetXYZ(par[2],par[3],vz);
	TVector3 lpoint, lvector;
	for (int i = 0; i < points; i++)
	{
		lpoint = LinesToFit.at(i).point;
		lvector = LinesToFit.at(i).direction;
		delta = fabs( ((tvector.Cross(lvector)).Dot(tpoint - lpoint))*pow((tvector.Cross(lvector)).Mag(),-1) );
		chisq += delta*delta;
		//bledy trzeba obl tak, jak poprzednio (bo na nie nie wplywa raczej obrot ukladu)
	}
	return chisq;
}

double FitToLines::calculate_chisq()
{
	const int points = LinesToFit.size();
	int i;
	//calculate chisquare
	double chisq = 0;
	double delta = 0;
	//par[0] = xp;
	//par[1] = yp;
	//par[2] = ux;
	//par[3] = uy;
	double zp, vz;
	double linex, liney, linez;
	vz = 1;
	zp = z_reference;
	TVector3 tpoint, tvector;
	tpoint = TrackPoint;
	tvector = TrackVector;
	TVector3 lpoint, lvector;
	for (int i = 0; i < points; i++)
	{
		lpoint = LinesToFit.at(i).point;
		lvector = LinesToFit.at(i).direction;
		delta = fabs( ((tvector.Cross(lvector)).Dot(tpoint - lpoint))*pow((tvector.Cross(lvector)).Mag(),-1) );
		chisq += delta*delta;
		//bledy trzeba obl tak, jak poprzednio (bo na nie nie wplywa raczej obrot ukladu)
	}
	//std::cout << chisq << std::endl;
	return chisq;
}

void FitToLines::fit_with_minuit()
{
	errflag = 1;
	std::vector<double> output;
	TMinuit *gMinuit = new TMinuit(7);  //initialize TMinuit with a maximum of 5 params
	gMinuit->SetFCN(d1d23dfcn);
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
	double vstart[4] = {InitTrackPoint.X(), InitTrackPoint.Y(), InitTrackVector.X(), InitTrackVector.Y()};
	double step[4] = {0.0001 , 0.0001, 0.00001, 0.00001};
	gMinuit->mnparm(0, "xp", vstart[0], step[0], 0, 0, ierflg);
	gMinuit->mnparm(1, "yp", vstart[1], step[1], 0, 0, ierflg);
	gMinuit->mnparm(2, "ux", vstart[2], step[2], 0, 0, ierflg);
	gMinuit->mnparm(3, "uy", vstart[3], step[3], 0, 0, ierflg);

	arglist[0] = 500; //was 500
	arglist[1] = 1.;
	gMinuit->mnexcm("MINIMIZE", arglist ,1,ierflg);
	//std::cout << errflag << std::endl;
	errflag = ierflg; // IERFLG=0 if no problems
	//std::cout << errflag << std::endl;
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
	
	TrackPoint.SetX(params[0]);
	TrackPoint.SetY(params[1]);
	TrackPoint.SetZ(z_reference);
	TrackVector.SetX(params[2]);
	TrackVector.SetY(params[3]);
	TrackVector.SetZ(1);

	delete gMinuit;
}

TVector3 FitToLines::get_track_vector()
{
	TrackVector = TrackVector.Unit();
	return TrackVector;
}

TVector3 FitToLines::get_track_point()
{
	return TrackPoint;
}

bool FitToLines::err_flag()
{
	return errflag;
}


