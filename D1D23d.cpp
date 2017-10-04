#include "D1D23d.h"

D1D23d::D1D23d() { }

D1D23d::D1D23d(const Config &_config)
{
	half_x_dim_D1 = _config.D1_half_x_dim;
	half_z_dim_D1 = _config.D1_half_z_dim;
	x_lab_position_D1 = _config.D1_x_lab_position;
	y_lab_position_D1 = _config.D1_y_lab_position;
	z_lab_position_D1 = _config.D1_z_lab_position;

	half_x_dim_D2 = _config.D2_half_x_dim;
	half_z_dim_D2 = _config.D2_half_z_dim;
	x_lab_position_D2 = _config.D2_x_lab_position;
	y_lab_position_D2 = _config.D2_y_lab_position;
	z_lab_position_D2 = _config.D2_z_lab_position;

	// points in the geometric centre of DCs
	D1point.SetXYZ(0, 0, 0);
	D2point.SetXYZ(0, 0, 0);
	
	D1_x_rot = _config.D1_x_rotation_angle; 
	D1_y_rot = _config.D1_y_rotation_angle; 
	D1_z_rot = _config.D1_z_rotation_angle;
	D2_x_rot = _config.D2_x_rotation_angle; 
	D2_y_rot = _config.D2_y_rotation_angle; 
	D2_z_rot = _config.D2_z_rotation_angle;

	// DCs vectors: bound in the centre of DC & point up 
	D1vectorX.SetXYZ(1, 0, 0);
	D2vectorX.SetXYZ(1, 0, 0);
	D1vectorY.SetXYZ(0, 1, 0);
	D2vectorY.SetXYZ(0, 1, 0);
	D1vectorZ.SetXYZ(0, 0, 1);
	D2vectorZ.SetXYZ(0, 0, 1);

	phi = new TH1F("phi", "phi; phi_xz [deg]; N", 200, 75, 105);
	theta = new TH1F("theta", "theta; theta_yz [deg]; N", 200, 75, 105);
	chi2 = new TH1F("#chi^{2}","#chi^{2};#chi^{2};N", 1000, -0.001, 0.05);
	chi2_resc = new TH1F("#chi^{2}","#chi^{2};#chi^{2};N", 250, -0.25, 25);
	calc_px = new TH1F("calc_px",";calc_px,N",6250,-20,20);
	calc_py = new TH1F("calc_py",";calc_py,N",5000,-40,40);
	calc_pz = new TH1F("calc_pz",";calc_pz,N",500,-60,0);
	calc_vx = new TH1F("calc_vx",";calc_vx,N",20000,-0.5,0.5);
	calc_vy = new TH1F("calc_vy",";calc_vy,N",20000,-0.5,0.5);
	calc_vz = new TH1F("calc_vz",";calc_vz,N",50000,0.9,1.1);
	track_px = new TH1F("track_px",";track_px,N",6250,-20,20);
	track_py = new TH1F("track_py",";track_py,N",5000,-40,40);
	track_pz = new TH1F("track_pz",";track_pz,N",500,-60,0);
	track_vx = new TH1F("track_vx",";track_vx,N",20000,-0.5,0.5);
	track_vy = new TH1F("track_vy",";track_vy,N",20000,-0.5,0.5);
	track_vz = new TH1F("track_vz",";track_vz,N",50000,0.9,1.1);
}

D1D23d::~D1D23d() { } 


void D1D23d::tell_no_of_events()
{
	unsigned int no_of_chosen_events;
	no_of_chosen_events = TrackRecoData.size();
	std::cout << "NO OF EVENTS FOR TRACK RECONSTRUCTION: " << no_of_chosen_events << std::endl;
}

// get_data: only reads in data from d1 and d2
void D1D23d::get_data(data_for_track_reconstruction _single_event_data)
{
	d1d2_3d_data single_event_data;

	// here data for common reconstruction are shifted by appropriate offsets 
	for (int i = 0; i < 14; i++)
	{
		if (i<6)
		{
			single_event_data.HitPoints[i].SetX(_single_event_data.D2.positionsHitsX[i]);
			single_event_data.x_err_hit_pos[i] = _single_event_data.D2.errorsX[i];
			single_event_data.HitPoints[i].SetZ(_single_event_data.D2.positionsZ[i]);
			single_event_data.HitPoints[i].SetY(y_lab_position_D2);
			single_event_data.HitVectors[i].SetZ(0);
			if (i==0||i==1)
			{
				single_event_data.HitVectors[i].SetX(TMath::Cos(59*TMath::DegToRad()));
				single_event_data.HitVectors[i].SetY(TMath::Sin(59*TMath::DegToRad()));
			}
			if (i==2||i==3)
			{
				single_event_data.HitVectors[i].SetX(-TMath::Cos(59*TMath::DegToRad()));
				single_event_data.HitVectors[i].SetY( TMath::Sin(59*TMath::DegToRad()));
			}
			if (i==4||i==5)
			{
				single_event_data.HitVectors[i].SetX(0);
				single_event_data.HitVectors[i].SetY(1);
			}
		}
		else
		{
			single_event_data.HitPoints[i].SetX(_single_event_data.D1.positionsHitsX[i-6]);
			single_event_data.x_err_hit_pos[i] = _single_event_data.D1.errorsX[i-6];
			single_event_data.HitPoints[i].SetZ(_single_event_data.D1.positionsZ[i-6]);
			single_event_data.HitPoints[i].SetY(y_lab_position_D1);
			single_event_data.HitVectors[i].SetZ(0);
			if (i==0+6||i==1+6||i==6+6||i==7+6)
			{
				single_event_data.HitVectors[i].SetX(0);
				single_event_data.HitVectors[i].SetY(1);
			}
			if (i==2+6||i==3+6)
			{
				single_event_data.HitVectors[i].SetX(TMath::Cos(59*TMath::DegToRad()));
				single_event_data.HitVectors[i].SetY(TMath::Sin(59*TMath::DegToRad()));
			}
			if (i==4+6||i==5+6)
			{
				single_event_data.HitVectors[i].SetX(-TMath::Cos(59*TMath::DegToRad()));
				single_event_data.HitVectors[i].SetY( TMath::Sin(59*TMath::DegToRad()));
			}

		}
	}
	TrackRecoData.push_back(single_event_data);
}

void D1D23d::set_config_positions()
{
	// rotations
	rotateD1(D1_x_rot,D1_y_rot,D1_z_rot);
	rotateD2(D2_x_rot,D2_y_rot,D2_z_rot);
	// shifts
	shiftD1(x_lab_position_D1, y_lab_position_D1, z_lab_position_D1, 0);
	shiftD2(x_lab_position_D2, y_lab_position_D2, z_lab_position_D2, 0);
}

void D1D23d::rotateD1(double _ax, double _ay, double _az)
{
	double ax, ay, az;
	// deg to rad
	ax = _ax*TMath::DegToRad();
	ay = _ay*TMath::DegToRad();
	az = _az*TMath::DegToRad();
	int no_of_chosen_events = TrackRecoData.size();
	//std::cout << "Rotating D1..." << std::endl;

	TVector3 RefAxis0, RefAxis1, RefAxis2;	

	// rotate around DCs x axis
	RefAxis0 = D2vectorX;
	D2vectorY.Rotate(ax,RefAxis0);
	D2vectorZ.Rotate(ax,RefAxis0);
	RefAxis1 = D1vectorY;
	//std::cout << "x " << std::endl;
	//std::cout << D1vectorX.X() << " " << D1vectorX.Y() << " " << D1vectorX.Z() << " " << std::endl;
	//std::cout << D1vectorY.X() << " " << D1vectorY.Y() << " " << D1vectorY.Z() << " " << std::endl;
	//std::cout << D1vectorZ.X() << " " << D1vectorZ.Y() << " " << D1vectorZ.Z() << " " << std::endl;
	// rotate around DCs y axis (DC xz plane)
	D1vectorZ.Rotate(ay,RefAxis1);
	D1vectorX.Rotate(ay,RefAxis1);
	RefAxis2 = D1vectorZ;
	//std::cout << "y " << std::endl;
	//std::cout << D1vectorX.X() << " " << D1vectorX.Y() << " " << D1vectorX.Z() << " " << std::endl;
	//std::cout << D1vectorY.X() << " " << D1vectorY.Y() << " " << D1vectorY.Z() << " " << std::endl;
	//std::cout << D1vectorZ.X() << " " << D1vectorZ.Y() << " " << D1vectorZ.Z() << " " << std::endl;
	// rotate around DCs z axis
	D1vectorX.Rotate(az,RefAxis2);
	D1vectorY.Rotate(az,RefAxis2);
	//std::cout << "z " << std::endl;
	//std::cout << D1vectorX.X() << " " << D1vectorX.Y() << " " << D1vectorX.Z() << " " << std::endl;
	//std::cout << D1vectorY.X() << " " << D1vectorY.Y() << " " << D1vectorY.Z() << " " << std::endl;
	//std::cout << D1vectorZ.X() << " " << D1vectorZ.Y() << " " << D1vectorZ.Z() << " " << std::endl;

	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		for (int j = 0; j < 8; j++) // here just added x and z offsets for correct start parameters
		{
			TrackRecoData.at(i).HitPoints[j+6].Rotate(ax,RefAxis0);
			TrackRecoData.at(i).HitVectors[j+6].Rotate(ax,RefAxis0);
			TrackRecoData.at(i).HitPoints[j+6].Rotate(ay,RefAxis1);
			TrackRecoData.at(i).HitVectors[j+6].Rotate(ay,RefAxis1);
			TrackRecoData.at(i).HitPoints[j+6].Rotate(az,RefAxis2);
			TrackRecoData.at(i).HitVectors[j+6].Rotate(az,RefAxis2);
			//std::cout << j + 6 + 1 << "X " << TrackRecoData.at(i).HitVectors[j+6].X() << std::endl;
			//std::cout << j + 6 + 1 << "Y " << TrackRecoData.at(i).HitVectors[j+6].Y() << std::endl;
			//std::cout << j + 6 + 1 << "Z " << TrackRecoData.at(i).HitVectors[j+6].Z() << std::endl;

		}
	}
}

void D1D23d::rotateD2(double _ax, double _ay, double _az)
{
	double ax, ay, az;
	// deg to rad
	ax = _ax*TMath::DegToRad();
	ay = _ay*TMath::DegToRad();
	az = _az*TMath::DegToRad();
	int no_of_chosen_events = TrackRecoData.size();
	//std::cout << "Rotating D2..." << std::endl;

	TVector3 RefAxis0, RefAxis1, RefAxis2;	

	// rotate around DCs x axis
	RefAxis0 = D2vectorX;
	D2vectorY.Rotate(ax,RefAxis0);
	D2vectorZ.Rotate(ax,RefAxis0);
	RefAxis1 = D2vectorY;
	//std::cout << "x " << std::endl;
	//std::cout << D1vectorX.X() << " " << D1vectorX.Y() << " " << D1vectorX.Z() << " " << std::endl;
	//std::cout << D1vectorY.X() << " " << D1vectorY.Y() << " " << D1vectorY.Z() << " " << std::endl;
	//std::cout << D1vectorZ.X() << " " << D1vectorZ.Y() << " " << D1vectorZ.Z() << " " << std::endl;
	// rotate around DCs y axis (DC xz plane)
	D2vectorZ.Rotate(ay,RefAxis1);
	D2vectorX.Rotate(ay,RefAxis1);
	RefAxis2 = D2vectorZ;
	//std::cout << "y " << std::endl;
	//std::cout << D1vectorX.X() << " " << D1vectorX.Y() << " " << D1vectorX.Z() << " " << std::endl;
	//std::cout << D1vectorY.X() << " " << D1vectorY.Y() << " " << D1vectorY.Z() << " " << std::endl;
	//std::cout << D1vectorZ.X() << " " << D1vectorZ.Y() << " " << D1vectorZ.Z() << " " << std::endl;
	// rotate around DCs z axis
	D2vectorX.Rotate(az,RefAxis2);
	D2vectorY.Rotate(az,RefAxis2);
	//std::cout << "z " << std::endl;
	//std::cout << D1vectorX.X() << " " << D1vectorX.Y() << " " << D1vectorX.Z() << " " << std::endl;
	//std::cout << D1vectorY.X() << " " << D1vectorY.Y() << " " << D1vectorY.Z() << " " << std::endl;
	//std::cout << D1vectorZ.X() << " " << D1vectorZ.Y() << " " << D1vectorZ.Z() << " " << std::endl;

	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		for (int j = 0; j < 6; j++) // here just added x and z offsets for correct start parameters
		{
			TrackRecoData.at(i).HitPoints[j].Rotate(ax,RefAxis0);
			TrackRecoData.at(i).HitVectors[j].Rotate(ax,RefAxis0);
			TrackRecoData.at(i).HitPoints[j].Rotate(ay,RefAxis1);
			TrackRecoData.at(i).HitVectors[j].Rotate(ay,RefAxis1);
			TrackRecoData.at(i).HitPoints[j].Rotate(az,RefAxis2);
			TrackRecoData.at(i).HitVectors[j].Rotate(az,RefAxis2);
		}
	}
}

void D1D23d::shiftD1(double _sx, double _sy, double _sz, bool change_lab)
{
	if (change_lab)
	{
		z_lab_position_D2 += _sx;
		z_lab_position_D2 += _sy;
		z_lab_position_D2 += _sz;
	}
	D1point.SetX(D1point.X()+ _sx);
	D1point.SetY(D1point.Y()+ _sy);
	D1point.SetZ(D1point.Z()+ _sz);
	double x,y,z;

	int no_of_chosen_events = TrackRecoData.size();
	//std::cout << "Shifting D1..." << std::endl;
	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			x = TrackRecoData.at(i).HitPoints[j+6].X();
			y = TrackRecoData.at(i).HitPoints[j+6].Y();
			z = TrackRecoData.at(i).HitPoints[j+6].Z();
			TrackRecoData.at(i).HitPoints[j+6].SetX(x + _sx);
			TrackRecoData.at(i).HitPoints[j+6].SetY(y + _sy);
			TrackRecoData.at(i).HitPoints[j+6].SetZ(z + _sz);
		}
	}
}

void D1D23d::shiftD2(double _sx, double _sy, double _sz, bool change_lab)
{
	if (change_lab)
	{
		z_lab_position_D2 += _sx;
		z_lab_position_D2 += _sy;
		z_lab_position_D2 += _sz;
	}

	D2point.SetX(D2point.X()+ _sx);
	D2point.SetY(D2point.Y()+ _sy);
	D2point.SetZ(D2point.Z()+ _sz);
	double x,y,z;

	int no_of_chosen_events = TrackRecoData.size();
	//std::cout << "Shifting D2..." << std::endl;
	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			x = TrackRecoData.at(i).HitPoints[j].X();
			y = TrackRecoData.at(i).HitPoints[j].Y();
			z = TrackRecoData.at(i).HitPoints[j].Z();
			TrackRecoData.at(i).HitPoints[j].SetX(x + _sx);
			TrackRecoData.at(i).HitPoints[j].SetY(y + _sy);
			TrackRecoData.at(i).HitPoints[j].SetZ(z + _sz);
		}
	}
}


void D1D23d::calculate_init_params()
{
	// for approximate track reconstruction
	double wires_positionsX_all[14];
	double hits_positionsX_all[14];
	double hits_positionsZ_all[14];
	double errors_all[14];
	//--------------------------------------
	unsigned int no_of_chosen_events;
	no_of_chosen_events = TrackRecoData.size();
	std::cout << "Fit in 3d..." << std::endl;
	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		for (int j = 0; j < 14; j++) // here just added x and z offsets for correct start parameters
		{
			if (j < 6)
			{
				wires_positionsX_all[j] = 0; // unused, just filling
				hits_positionsX_all[j] = TrackRecoData.at(i).HitPoints[j].X() + x_lab_position_D2;
				hits_positionsZ_all[j] = TrackRecoData.at(i).HitPoints[j].Z() + z_lab_position_D2;
				errors_all[j]=TrackRecoData.at(i).x_err_hit_pos[j];
			}
			else
			{
				wires_positionsX_all[j] = 0; // unused, just filling
				hits_positionsX_all[j] = TrackRecoData.at(i).HitPoints[j].X() + x_lab_position_D1;
				hits_positionsZ_all[j] = TrackRecoData.at(i).HitPoints[j].Z() + z_lab_position_D1;
				errors_all[j]=TrackRecoData.at(i).x_err_hit_pos[j];
			}
			
		}
		
		if (0==i%10000) std::cout << "    " << i << " out of " << no_of_chosen_events << " done" << std::endl;

		TrackCalc *trackcalc = new TrackCalc(i);
		trackcalc -> TrackCalc::set_no_of_iteration(0);
		trackcalc -> TrackCalc::set_values(hits_positionsX_all,hits_positionsZ_all,errors_all, wires_positionsX_all);
		trackcalc -> TrackCalc::set_z_reference((8*z_lab_position_D1 + 6*z_lab_position_D2)*pow(14,-1));
		trackcalc -> TrackCalc::fit_straight_layer();
		trackcalc -> TrackCalc::fit_inclined_layers();
		trackcalc -> TrackCalc::calculate_xy_functions();
		trackcalc -> TrackCalc::set_hit_planes_vectors();
		trackcalc -> TrackCalc::calculate_normal_to_hit_planes();
		trackcalc -> TrackCalc::calculate_hit_planes_eq();
		trackcalc -> TrackCalc::calculate_intersection_vectors();
		trackcalc -> TrackCalc::calculate_intersection_points();
		trackcalc -> TrackCalc::calculate_3d_track_parameters();
		TrackRecoData.at(i).ApproxTrackPoint  = trackcalc -> TrackCalc::return_approx_track_point();
		TrackRecoData.at(i).ApproxTrackVector = trackcalc -> TrackCalc::return_approx_track_vector();
		calc_px -> Fill(TrackRecoData.at(i).ApproxTrackPoint.X());
		calc_py -> Fill(TrackRecoData.at(i).ApproxTrackPoint.Y());
		calc_pz -> Fill(TrackRecoData.at(i).ApproxTrackPoint.Z());
		calc_vx -> Fill(TrackRecoData.at(i).ApproxTrackVector.X());
		calc_vy -> Fill(TrackRecoData.at(i).ApproxTrackVector.Y());
		calc_vz -> Fill(TrackRecoData.at(i).ApproxTrackVector.Z());
	}
}

void D1D23d::fit_in_3d()
{
	FitToLines * fit;
	unsigned int no_of_chosen_events = TrackRecoData.size();
	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		fit = FitToLines::GetInstance();
		for (int j = 0; j < 14; j++)
		{
			fit -> set_line(TrackRecoData.at(i).HitPoints[j],TrackRecoData.at(i).HitVectors[j]);
		}
		fit -> set_init_params(TrackRecoData.at(i).ApproxTrackPoint,TrackRecoData.at(i).ApproxTrackVector);
		fit -> set_z_reference((8*z_lab_position_D1 + 6*z_lab_position_D2)*pow(14,-1));
		//std::cout << (8*z_lab_position_D1 + 6*z_lab_position_D2)*pow(14,-1) << std::endl;
		fit -> fit_with_minuit();
		TrackRecoData.at(i).errflag = fit -> err_flag();
		TrackRecoData.at(i).TrackPoint = fit -> get_track_point();
		TrackRecoData.at(i).TrackVector = fit -> get_track_vector();
		TrackRecoData.at(i).chi2 = fit -> calculate_chisq();
		delete fit;
	}
}

double D1D23d::get_mean_chisq()
{
	double mean_chisq = 0;
	for (int i = 0; i < TrackRecoData.size(); i++)
	{		
		if (!TrackRecoData.at(i).errflag)
		{
			mean_chisq = mean_chisq + TrackRecoData.at(i).chi2;
			//std::cout << TrackRecoData.at(i).chi2 << std::endl;
		}
	}
	//std::cout << TrackRecoData.size() << std::endl;
	//std::cout << mean_chisq << std::endl;
	mean_chisq = mean_chisq*pow(TrackRecoData.size(),-1);
	return mean_chisq;
}

void D1D23d::fill_histos()
{
	unsigned int no_of_chosen_events = TrackRecoData.size();
	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		chi2 -> Fill(TrackRecoData.at(i).chi2);
		phi -> Fill(calculate_phi_xz(TrackRecoData.at(i).TrackVector.X(),TrackRecoData.at(i).TrackVector.Z()));
		theta -> Fill(calculate_phi_xz(TrackRecoData.at(i).TrackVector.Y(),TrackRecoData.at(i).TrackVector.Z()));
		track_px -> Fill(TrackRecoData.at(i).TrackPoint.X());
		track_py -> Fill(TrackRecoData.at(i).TrackPoint.Y());
		track_pz -> Fill(TrackRecoData.at(i).TrackPoint.Z());
		track_vx -> Fill(TrackRecoData.at(i).TrackVector.X());
		track_vy -> Fill(TrackRecoData.at(i).TrackVector.Y());
		track_vz -> Fill(TrackRecoData.at(i).TrackVector.Z());
	}
}

void D1D23d::save_histos()
{
	gDirectory->pwd();
	chi2 -> Write();
	phi -> Write();
	theta -> Write();
	calc_px -> Write();
	track_px -> Write();
	calc_py -> Write();
	track_py -> Write();
	calc_pz -> Write();
	track_pz -> Write();
	calc_vx -> Write();
	track_vx -> Write();
	calc_vy -> Write();
	track_vy -> Write();
	calc_vz -> Write();
	track_vz -> Write();
	
}

double D1D23d::calculate_phi_xz(double vx, double vz)
{
	double phi_xz;
	double norm;
	norm = pow(vx*vx+vz*vz,0.5);
	vx = vx*pow(norm,-1);
	vz = vz*pow(norm,-1);
	phi_xz = TMath::ACos(vx)*180*pow(3.14,-1);
	return phi_xz;
}

double D1D23d::calculate_theta_yz(double vy, double vz)
{
	double theta_yz;
	double norm;
	norm = pow(vz*vz+vy*vy,0.5);
	vz = vz*pow(norm,-1);
	vy = vy*pow(norm,-1);
	theta_yz = TMath::ACos(vy)*180*pow(3.14,-1);
	return theta_yz;
}

double D1D23d::draw_chambers()
{
	TCanvas *test = new TCanvas("name","name");
	test->SetFillColor(0);
	test->SetBorderMode(0);
	test->SetBorderSize(2);
	test->SetFrameBorderMode(0);
	TView3D *view = (TView3D*) TView::CreateView(1);
	view->SetRange(-70,-20,-70,70,20,20);
	view->ShowAxis();
	TAxis3D *axis = TAxis3D::GetPadAxis(); // Get pointer to axis
    if(axis) {
        axis->SetLabelSize(0.02);
        axis->SetLabelOffset(-0.02, "z");
        axis->SetLabelColor(1);
        axis->SetAxisColor(1);
        axis->SetXTitle("X");
        axis->SetYTitle("Y");
        axis->SetZTitle("Z");
    }

    TPolyLine3D *D1vecX = new TPolyLine3D(2);
	D1vecX->SetPoint(0,D1point.X(), D1point.Y(), D1point.Z());
	D1vecX->SetPoint(1,D1point.X()+D1vectorX.X(), D1point.Y()+D1vectorX.Y(), D1point.Z()+D1vectorX.Z());
	D1vecX->SetLineColor(kBlue);
	D1vecX->SetLineWidth(2);
	D1vecX->Draw();

	gDirectory -> pwd();
    //test -> Write();
    view -> Write();

}