#include "Fit3d.h"

Fit3d::Fit3d()
{

}

Fit3d::Fit3d(int _event_no)
{
	event_no = _event_no;
}

Fit3d::~Fit3d()
{

}

void Fit3d::set_values(double *_x, double *_y, double *_errors)
{
	// straight
	x_straight[0] = _x[0];
	z_straight[0] = _y[0];
	errors_straight[0] = _errors[0];
	x_straight[1] = _x[1];
	z_straight[1] = _y[1];
	errors_straight[1] = _errors[1];
	x_straight[2] = _x[6];
	z_straight[2] = _y[6];
	errors_straight[2] = _errors[6];
	x_straight[3] = _x[7];
	z_straight[3] = _y[7];
	errors_straight[3] = _errors[7];

	// inclined
	x_inclined1[0] = _x[3];
	z_inclined1[0] = _y[3];
	errors_inclined1[0] = _errors[3];
	x_inclined1[1] = _x[4];
	z_inclined1[1] = _y[4];
	errors_inclined1[1] = _errors[4];
	x_inclined2[0] = _x[5];
	z_inclined2[0] = _y[5];
	errors_inclined2[0] = _errors[5];
	x_inclined2[1] = _x[6];
	z_inclined2[1] = _y[6];
	errors_inclined2[1] = _errors[6];
}

void Fit3d::fit_straight_layer()
{
	std::vector<double> results;
	MinuitFit * fit = MinuitFit::GetInstance();
	fit -> set_no_of_points(4);		
	fit -> MinuitFit::set_values(x_straight, z_straight, errors_straight);
	fit -> MinuitFit::perform_simplified_fit();
	results = fit -> MinuitFit::fit_with_minuit();
	z_x_a[0] = results.at(0);
	z_x_b[0] = results.at(1);
	results.clear();
}

void Fit3d::fit_inclined_layers()
{
	std::vector<double> results;
	MinuitFit * fit1 = MinuitFit::GetInstance();
	fit1 -> set_no_of_points(2);		
	fit1 -> MinuitFit::set_values(x_inclined1, z_inclined1, errors_inclined1);
	fit1 -> MinuitFit::perform_simplified_fit();
	results = fit1 -> MinuitFit::fit_with_minuit();
	//std::cout << " ----- " << std::endl;
	//std::cout << x_inclined1[0] << " " << z_inclined1[0] << " " << errors_inclined1[0] << std::endl;
	//std::cout << x_inclined1[1] << " " << z_inclined1[1] << " " << errors_inclined1[1] << std::endl;
	z_x_a[1] = results.at(0);
	z_x_b[1] = results.at(1);
	//std::cout << z_x_a[1] << " " << z_x_b[1] << std::endl;

	MinuitFit * fit2 = MinuitFit::GetInstance();
	fit2 -> set_no_of_points(2);		
	fit2 -> MinuitFit::set_values(x_inclined2, z_inclined2, errors_inclined2);
	fit2 -> MinuitFit::perform_simplified_fit();
	results = fit2 -> MinuitFit::fit_with_minuit();
	z_x_a[2] = results.at(0);
	z_x_b[2] = results.at(1);
}

void Fit3d::calculate_xy_functions()
{
	// dla plaszczyzny z = 0
	y_x_a[0] = 0;
	y_x_b[0] = 0;
	y_x_a[1] = TMath::Tan(59*3.14*pow(180,-1));
	y_x_b[1] = x_inclined1[0]*y_x_a[1];
	y_x_a[2] =-TMath::Tan(59*3.14*pow(180,-1));
	y_x_b[2] = x_inclined1[0]*y_x_a[1];

}

void Fit3d::set_hit_planes_vectors()
{
	// xy plane
	xy_straight.SetXYZ(0,1,0); // x, y, z in the lab coordinates system
	xy_inclined1.SetXYZ( TMath::Sin(31*3.14*pow(180,-1)),TMath::Cos(31*3.14*pow(180,-1)),0);
	xy_inclined2.SetXYZ(-TMath::Sin(31*3.14*pow(180,-1)),TMath::Cos(31*3.14*pow(180,-1)),0);

	// xz plane
	xz_straight.SetXYZ(1,0,z_x_a[0]);
	xz_inclined1.SetXYZ(1,0,z_x_a[1]);
	xz_inclined2.SetXYZ(1,0,z_x_a[2]);

	//std::cout << xy_inclined1.X() << " " << xy_inclined1.Y() << " " << xy_inclined1.Z() << std::endl;
	//std::cout << xz_inclined1.X() << " " << xz_inclined1.Y() << " " << xz_inclined1.Z() << std::endl;

	// normalization
	xy_straight  = xy_straight.Unit();
	xy_inclined1 = xy_inclined1.Unit();
	xy_inclined2 = xy_inclined2.Unit();
	xz_straight  = xz_straight.Unit();
	xz_inclined1 = xz_inclined1.Unit();
	xz_inclined2 = xz_inclined2.Unit();

	//std::cout << xy_inclined1.X() << " " << xy_inclined1.Y() << " " << xy_inclined1.Z() << std::endl;
	//std::cout << xz_inclined1.X() << " " << xz_inclined1.Y() << " " << xz_inclined1.Z() << std::endl;
} 

void Fit3d::calculate_normal_to_hit_planes()
{
	normal_straight  = xy_straight.Cross(xz_straight);
	normal_inclined1 = xy_inclined1.Cross(xz_inclined1);
	normal_inclined2 = xy_inclined2.Cross(xz_inclined2);

	// normalization
	normal_straight  = normal_straight.Unit();
	normal_inclined1 = normal_inclined1.Unit();
	normal_inclined2 = normal_inclined2.Unit();

	//std::cout << normal_inclined1.X() << " " << normal_inclined1.Y() << " " << normal_inclined1.Z() << std::endl;
	//std::cout << " --- " << std::endl;
}

void Fit3d::calculate_hit_planes_eq()
{
	// A, B, C - known from vectors perpendicular to planes
	hit_plane_A[0] = normal_straight.X();
	hit_plane_B[0] = normal_straight.Y();
	hit_plane_C[0] = normal_straight.Z();

	hit_plane_A[1] = normal_inclined1.X();
	hit_plane_B[1] = normal_inclined1.Y();
	hit_plane_C[1] = normal_inclined1.Z();

	hit_plane_A[1] = normal_inclined2.X();
	hit_plane_B[1] = normal_inclined2.Y();
	hit_plane_C[1] = normal_inclined2.Z();

	double xp, yp;
	// D 
	//straight
	xp = -z_x_b[0]*pow(z_x_a[0],-1);
	yp = 0;
	hit_plane_D[0] = -(hit_plane_A[0]*xp + hit_plane_B[0]*yp);

	//inclined
	xp = -z_x_b[1]*pow(z_x_a[1],-1);
	yp = y_x_a[1]*xp + y_x_b[1];
	hit_plane_D[1] = -(hit_plane_A[1]*xp + hit_plane_B[1]*yp);

	xp = -z_x_b[2]*pow(z_x_a[2],-1);
	yp = y_x_a[2]*xp + y_x_b[2];
	hit_plane_D[2] = -(hit_plane_A[2]*xp + hit_plane_B[2]*yp);

}

void Fit3d::calculate_intersection_vectors() // intersection line: vectors
{
	inter_si1 = normal_straight.Cross(normal_inclined1);
	inter_si2 = normal_straight.Cross(normal_inclined2);
	inter_i1i2 = normal_inclined1.Cross(normal_inclined2);

	inter_si1 = inter_si1.Unit();
	inter_si2 = inter_si2.Unit();
	inter_i1i2 = inter_i1i2.Unit();	
}

void Fit3d::calculate_intersection_points()// intersection line: points
{
	inter_point_si1.SetZ(z_straight[0]);
	inter_point_si2.SetZ(z_straight[0]);
	inter_point_i1i2.SetZ(z_straight[0]);

	inter_point_si1.SetX((hit_plane_B[0]*hit_plane_D[1] - hit_plane_B[1]*hit_plane_D[0])*pow(hit_plane_A[0]*hit_plane_B[1] - hit_plane_A[1]*hit_plane_B[0],-1));
	inter_point_si2.SetX((hit_plane_B[1]*hit_plane_D[2] - hit_plane_B[2]*hit_plane_D[1])*pow(hit_plane_A[1]*hit_plane_B[2] - hit_plane_A[2]*hit_plane_B[1],-1));
	inter_point_i1i2.SetX((hit_plane_B[2]*hit_plane_D[0] - hit_plane_B[0]*hit_plane_D[2])*pow(hit_plane_A[2]*hit_plane_B[0] - hit_plane_A[0]*hit_plane_B[2],-1));

	inter_point_si1.SetY((-hit_plane_A[0]*hit_plane_D[1] + hit_plane_A[1]*hit_plane_D[0])*pow(hit_plane_A[0]*hit_plane_B[1] - hit_plane_A[1]*hit_plane_B[0],-1));
	inter_point_si2.SetY((-hit_plane_A[1]*hit_plane_D[2] + hit_plane_A[2]*hit_plane_D[1])*pow(hit_plane_A[1]*hit_plane_B[2] - hit_plane_A[2]*hit_plane_B[1],-1));
	inter_point_i1i2.SetY((-hit_plane_A[2]*hit_plane_D[0] + hit_plane_A[0]*hit_plane_D[2])*pow(hit_plane_A[2]*hit_plane_B[0] - hit_plane_A[0]*hit_plane_B[2],-1));
}

void Fit3d::calculate_3d_track_parameters()
{
	track3d_point.SetX((inter_point_si1.X() + inter_point_si2.X() + inter_point_i1i2.X())*pow(3,-1));
	track3d_point.SetY((inter_point_si1.Y() + inter_point_si2.Y() + inter_point_i1i2.Y())*pow(3,-1));
	track3d_point.SetZ((inter_point_si1.Z() + inter_point_si2.Z() + inter_point_i1i2.Z())*pow(3,-1));

	track3d_vector = inter_si1 + inter_si2 + inter_i1i2;
	track3d_vector = track3d_vector.Unit();
}

void Fit3d::set_detector_position(double _x_lab_position, double _z_lab_position, double _half_x_dim, double _half_z_dim, double _distance_to_1st_layer)
{
	x_lab_position = _x_lab_position;
	z_lab_position = _z_lab_position;
	half_x_dim = _half_x_dim;
	half_z_dim = _half_z_dim;
	distance_to_1st_layer = _distance_to_1st_layer;
}

void Fit3d::draw_event()
{
	TString name = Form("test_%d.png", event_no);
	TCanvas *test = new TCanvas(name,name);
	// chamber
	TMarker3DBox *drift_chamber = new TMarker3DBox (x_lab_position, 0, z_lab_position, half_x_dim, 150, half_z_dim, 0, 0);
	drift_chamber -> Draw();
	// inclined wire
	TPolyLine3D *yx_fcn_i1 = new TPolyLine3D(2);
	yx_fcn_i1->SetPoint(0, (-75 - y_x_b[1])/y_x_a[1], -75, 0);
	yx_fcn_i1->SetPoint(1, ( 75 - y_x_b[1])/y_x_a[1],  75, 0);
	yx_fcn_i1->Draw();

	
	test -> SaveAs(name, name);
}