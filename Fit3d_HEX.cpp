#include "Fit3d_HEX.h"

Fit3d_HEX::Fit3d_HEX()
{

}

Fit3d_HEX::Fit3d_HEX(int _event_no)
{
	z_reference = 0;
	event_no = _event_no;
	unbiased_fit = false;
}

Fit3d_HEX::~Fit3d_HEX()
{

}

void Fit3d_HEX::set_no_of_iteration(int _no_of_iteration)
{
	no_of_iteration = _no_of_iteration;
}

void Fit3d_HEX::set_values(double *_x, double *_y, double *_errors, double *_x_wires)
{
	// inclined
	x_inclined1[0]       = _x[1];
	//std::cout << "i1 " << x_inclined1[0] << std::endl;
	x_inclined1_wires[0] = _x_wires[1];
	z_inclined1[0]       = _y[1];
	errors_inclined1[0]   = _errors[1];
	x_inclined1[1]       = _x[2];
	//std::cout << "i1 " << x_inclined1[1] << std::endl;
	x_inclined1_wires[1] = _x_wires[2];
	z_inclined1[1]       = _y[2];
	errors_inclined1[1] = _errors[2];

	// inclined 2
	x_inclined2[0]       = _x[4];
	//std::cout << "i2 " << x_inclined2[0] << std::endl;
	x_inclined2_wires[0] = _x_wires[4];
	//std::cout << "wire " << x_inclined2_wires[0] << std::endl;
	z_inclined2[0]       = _y[4];
	errors_inclined2[0]  = _errors[4];
	x_inclined2[1]       = _x[5];
	//std::cout << "i2 " << x_inclined2[1] << std::endl;
	x_inclined2_wires[1] = _x_wires[5];
	z_inclined2[1]       = _y[5];
	errors_inclined2[1]  = _errors[5];

	// straight
	x_straight[0]       = _x[0];
	//std::cout << "s " << x_straight[0] << std::endl;
	x_straight_wires[0] = _x_wires[0];
	z_straight[0]       = _y[0];
	errors_straight[0]  = _errors[0];
	x_straight[1]       = _x[3];
	//std::cout << "s " << x_straight[1] << std::endl;
	x_straight_wires[1] = _x_wires[3];
	z_straight[1]       = _y[3];
	errors_straight[1]  = _errors[3];
}

void Fit3d_HEX::set_z_reference(double z)
{
	z_reference = z;
}

void Fit3d_HEX::fit_straight_layer()
{
	std::vector<double> results;
	MinuitFit * fit = MinuitFit::GetInstance();
	fit -> set_no_of_points(2);		
	fit -> MinuitFit::set_values(x_straight, z_straight, errors_straight);
	fit -> MinuitFit::perform_simplified_fit();
	results = fit -> MinuitFit::fit_with_minuit();
	z_x_a[0] = results.at(0);
	z_x_b[0] = results.at(1);
	//std::cout << "straight: " << std::endl;
	//std::cout << "    " << x_straight[0] << " " << x_straight[1] << std::endl;
	//std::cout << "    " << z_straight[0] << " " << z_straight[1] << std::endl;
	//std::cout << "  " << z_x_a[0] << " " << z_x_b[0] << std::endl;
	results.clear();
}

void Fit3d_HEX::fit_inclined_layers()
{
	std::vector<double> results;
	//MinuitFit * fit1 = MinuitFit::GetInstance();
	//fit1 -> set_no_of_points(2);		
	//fit1 -> MinuitFit::set_values(x_inclined1, z_inclined1, errors_inclined1);
	//fit1 -> MinuitFit::perform_simplified_fit();
	//results = fit1 -> MinuitFit::fit_with_minuit();
	//std::cout << " ----- " << std::endl;
	//std::cout << x_inclined1[0] << " " << z_inclined1[0] << " " << errors_inclined1[0] << std::endl;
	//std::cout << x_inclined1[1] << " " << z_inclined1[1] << " " << errors_inclined1[1] << std::endl;
	//z_x_a[1] = results.at(0);
	//z_x_b[1] = results.at(1);
	z_x_a[1] = (z_inclined1[0]-z_inclined1[1])/(x_inclined1[0]-x_inclined1[1]);
	z_x_b[1] = z_inclined1[0] - z_x_a[1]*x_inclined1[0];
	//std::cout << "inclined1: " << std::endl;
	//std::cout << "    " << x_inclined1[0] << " " << x_inclined1[1] << std::endl;
	//std::cout << "    " << z_inclined1[0] << " " << z_inclined1[1] << std::endl;
	//std::cout << "  " << z_x_a[1] << " " << z_x_b[1] << std::endl;
	

	//MinuitFit * fit2 = MinuitFit::GetInstance();
	//fit2 -> set_no_of_points(2);		
	//fit2 -> MinuitFit::set_values(x_inclined2, z_inclined2, errors_inclined2);
	//fit2 -> MinuitFit::perform_simplified_fit();
	//results = fit2 -> MinuitFit::fit_with_minuit();
	//z_x_a[2] = results.at(0);
	//z_x_b[2] = results.at(1);

	z_x_a[2] = (z_inclined2[0]-z_inclined2[1])/(x_inclined2[0]-x_inclined2[1]);
	z_x_b[2] = z_inclined2[0] - z_x_a[2]*x_inclined2[0];

	//std::cout << "inclined2: " << std::endl;
	//std::cout << "    " << x_inclined2[0] << " " << x_inclined2[1] << std::endl;
	//std::cout << "    " << z_inclined2[0] << " " << z_inclined2[1] << std::endl;
	//std::cout << "  " << z_x_a[2] << " " << z_x_b[2] << std::endl;
}

void Fit3d_HEX::calculate_xy_functions()
{
	// dla plaszczyzny z = 0
	// straight
	y_x_a[0] = 0;
	y_x_b[0][0] = 0;
	y_x_b[0][1] = 0;
	// inclined 1
	y_x_a[1] = -TMath::Tan(80*TMath::DegToRad());
	y_x_b[1][0] = -x_inclined1[0]*y_x_a[1];
	y_x_b[1][1] = -x_inclined1[1]*y_x_a[1];
	// inclined 2
	y_x_a[2] =  TMath::Tan(80*TMath::DegToRad());
	y_x_b[2][0] = -x_inclined2[0]*y_x_a[2];
	y_x_b[2][1] = -x_inclined2[1]*y_x_a[2];

	//std::cout << "y_x_b[1][0] " << y_x_b[1][0] << std::endl;
	//std::cout << "y_x_b[1][1] " << y_x_b[1][1] << std::endl;
	//std::cout << "y_x_b[2][0] " << y_x_b[2][0] << std::endl;
	//std::cout << "y_x_b[2][1] " << y_x_b[2][1] << std::endl;
}

void Fit3d_HEX::calculate_wires_xy_functions()
{
	// dla plaszczyzny z = 0
	// straight
	y_x_a_wire[0] = 0;
	y_x_b_wire[0][0] = 0;
	y_x_b_wire[0][1] = 0;
	// inclined 1
	y_x_a_wire[1] = -TMath::Tan(80*TMath::DegToRad());
	y_x_b_wire[1][0] = -x_inclined1_wires[0]*y_x_a_wire[1];
	y_x_b_wire[1][1] = -x_inclined1_wires[1]*y_x_a_wire[1];
	// inclined 2
	y_x_a_wire[2] = TMath::Tan(80*TMath::DegToRad());
	y_x_b_wire[2][0] = -x_inclined2_wires[0]*y_x_a_wire[2];
	y_x_b_wire[2][1] = -x_inclined2_wires[1]*y_x_a_wire[2];
}

void Fit3d_HEX::set_hit_planes_vectors()
{
	// xy plane
	xy_straight.SetXYZ(0,1,0); // x, y, z in the lab coordinates system
	xy_inclined1.SetXYZ(-TMath::Sin(10*3.14*pow(180,-1)),TMath::Cos(10*3.14*pow(180,-1)),0);
	xy_inclined2.SetXYZ( TMath::Sin(10*3.14*pow(180,-1)),TMath::Cos(10*3.14*pow(180,-1)),0);

	// xz plane
	xz_straight.SetXYZ(1,0,z_x_a[0]);
	xz_inclined1.SetXYZ(1,0,z_x_a[1]);
	xz_inclined2.SetXYZ(1,0,z_x_a[2]);

	//std::cout << "xz_inclined11.Z() " << xz_inclined1.Z() << std::endl;
	//std::cout << "xz_inclined12.Z() " << xz_inclined2.Z() << std::endl;

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

void Fit3d_HEX::calculate_normal_to_hit_planes()
{
	normal_straight  = xy_straight.Cross(xz_straight);
	normal_inclined1 = xy_inclined1.Cross(xz_inclined1);
	normal_inclined2 = xy_inclined2.Cross(xz_inclined2);

	// normalization
	normal_straight  = normal_straight.Unit();
	normal_inclined1 = normal_inclined1.Unit();
	normal_inclined2 = normal_inclined2.Unit();

	//std::cout << "normal_inclined1.X() " << normal_inclined1.X() << std::endl;
	//std::cout << "normal_inclined1.Y() " << normal_inclined1.Y() << std::endl;
	//std::cout << "normal_inclined1.Z() " << normal_inclined1.Z() << std::endl;
}

void Fit3d_HEX::calculate_hit_planes_eq()
{
	// A, B, C - known from vectors perpendicular to planes
	hit_plane_A[0] = normal_straight.X();
	hit_plane_B[0] = normal_straight.Y();
	hit_plane_C[0] = normal_straight.Z();

	hit_plane_A[1] = normal_inclined1.X();
	hit_plane_B[1] = normal_inclined1.Y();
	hit_plane_C[1] = normal_inclined1.Z();

	hit_plane_A[2] = normal_inclined2.X();
	hit_plane_B[2] = normal_inclined2.Y();
	hit_plane_C[2] = normal_inclined2.Z();

	double xp, yp, zp;
	// D 
	//straight
	zp = z_straight[0];
	xp = (zp - z_x_b[0])*pow(z_x_a[0],-1);
	yp = 0;
	hit_plane_D[0] = -(hit_plane_A[0]*xp + hit_plane_B[0]*yp + hit_plane_C[0]*zp);

	//inclined
	zp = z_inclined1[0];
	//xp = (zp -z_x_b[1])/z_x_a[1];
	//yp = y_x_a[1]*xp + y_x_b[1][0];
	//hit_plane_D[1] = -(hit_plane_A[1]*xp + hit_plane_B[1]*yp + hit_plane_C[1]*zp);
	hit_plane_D[1] = -(hit_plane_A[1]*x_inclined1[0] + hit_plane_B[1]*0 + hit_plane_C[1]*z_inclined1[0]);

	zp = z_inclined2[0];
	//xp = (zp -z_x_b[2])/z_x_a[2];
	//yp = y_x_a[2]*xp + y_x_b[2][0];
	//hit_plane_D[2] = -(hit_plane_A[2]*xp + hit_plane_B[2]*yp + hit_plane_C[2]*zp);
	hit_plane_D[2] = -(hit_plane_A[2]*x_inclined2[0] + hit_plane_B[2]*0 + hit_plane_C[2]*z_inclined2[0]);

	//std::cout << "x_inclined1[0] " << x_inclined1[0] << std::endl;
	//std::cout << "hit_plane_D[1] " << hit_plane_D[1] << std::endl;

}

void Fit3d_HEX::calculate_intersection_vectors() // intersection line: vectors
{
	inter_si1 = normal_straight.Cross(normal_inclined1);
	inter_si2 = normal_straight.Cross(normal_inclined2);
	inter_i1i2 = normal_inclined1.Cross(normal_inclined2);

	inter_si1.SetX(inter_si1.X()/inter_si1.Z());
	inter_si1.SetY(inter_si1.Y()/inter_si1.Z());
	inter_si1.SetZ(inter_si1.Z()/inter_si1.Z());

	//std::cout << "inter_si1.X() " << inter_si1.X() <<  std::endl;
	//std::cout << "inter_si1.Y() " << inter_si1.Y() <<  std::endl;
	//std::cout << "inter_si1.Z() " << inter_si1.Z() <<  std::endl;

	inter_si2.SetX(inter_si2.X()/inter_si2.Z());
	inter_si2.SetY(inter_si2.Y()/inter_si2.Z());
	inter_si2.SetZ(inter_si2.Z()/inter_si2.Z());

	inter_i1i2.SetX(inter_i1i2.X()/inter_i1i2.Z());
	inter_i1i2.SetY(inter_i1i2.Y()/inter_i1i2.Z());
	inter_i1i2.SetZ(inter_i1i2.Z()/inter_i1i2.Z());

	//inter_si1 = inter_si1.Unit();
	//inter_si2 = inter_si2.Unit();
	//inter_i1i2 = inter_i1i2.Unit();	
}

void Fit3d_HEX::calculate_intersection_points()// intersection line: points
{
	inter_point_si1.SetZ(0);
	inter_point_si2.SetZ(0);
	inter_point_i1i2.SetZ(0);

	inter_point_si1.SetX((hit_plane_B[1]*hit_plane_D[0] - hit_plane_B[0]*hit_plane_D[1])*pow(hit_plane_A[1]*hit_plane_B[0] - hit_plane_A[0]*hit_plane_B[1],-1));
	inter_point_i1i2.SetX((hit_plane_B[2]*hit_plane_D[1] - hit_plane_B[1]*hit_plane_D[2])*pow(hit_plane_A[2]*hit_plane_B[1] - hit_plane_A[1]*hit_plane_B[2],-1));
	inter_point_si2.SetX((hit_plane_B[2]*hit_plane_D[0] - hit_plane_B[0]*hit_plane_D[2])*pow(hit_plane_A[2]*hit_plane_B[0] - hit_plane_A[0]*hit_plane_B[2],-1));

	inter_point_si1.SetY((-hit_plane_A[0]*hit_plane_D[1] + hit_plane_A[1]*hit_plane_D[0])*pow(hit_plane_A[0]*hit_plane_B[1] - hit_plane_A[1]*hit_plane_B[0],-1));
	inter_point_i1i2.SetY((-hit_plane_A[1]*hit_plane_D[2] + hit_plane_A[2]*hit_plane_D[1])*pow(hit_plane_A[1]*hit_plane_B[2] - hit_plane_A[2]*hit_plane_B[1],-1));
	inter_point_si2.SetY((-hit_plane_A[2]*hit_plane_D[0] + hit_plane_A[0]*hit_plane_D[2])*pow(hit_plane_A[2]*hit_plane_B[0] - hit_plane_A[0]*hit_plane_B[2],-1));

	//std::cout << "inter_point_si1.X() " << inter_point_si1.X() <<  std::endl;
	//std::cout << "inter_point_si1.Y() " << inter_point_si1.Y() <<  std::endl;
	//std::cout << "inter_point_si1.Z() " << inter_point_si1.Z() <<  std::endl;
}

void Fit3d_HEX::calculate_3d_track_parameters()
{
	TVector3 track_p_si1_1, track_p_si1_2, track_p_si2_1, track_p_si2_2, track_p_i1i2_1, track_p_i1i2_2;
	double scale;
	// points on the intersection line at z = reference
	track_p_si1_1.SetZ(0);
	track_p_si2_1.SetZ(0);
	track_p_i1i2_1.SetZ(0);
	//    s i1 // 10.05.17 - dlaczego ujemne?
	scale = -inter_point_si1.Z()/inter_si1.Z();
	track_p_si1_1.SetX(inter_point_si1.X()+scale*inter_si1.X());
	track_p_si1_1.SetY(inter_point_si1.Y()+scale*inter_si1.Y());
	//    s i2
	scale = -inter_point_si2.Z()/inter_si2.Z();
	track_p_si2_1.SetX(inter_point_si2.X()+scale*inter_si2.X());
	track_p_si2_1.SetY(inter_point_si2.Y()+scale*inter_si2.Y());
	//    i1 i2
	scale = -inter_point_i1i2.Z()/inter_i1i2.Z();
	track_p_i1i2_1.SetX(inter_point_i1i2.X()+scale*inter_i1i2.X());
	track_p_i1i2_1.SetY(inter_point_i1i2.Y()+scale*inter_i1i2.Y());

	// alternative method of calculation of parameters
	TVector3 alt_vector, alt_point;
	alt_vector.SetX((inter_si1.X() + inter_si2.X() + inter_i1i2.X())/3);
	alt_vector.SetY((inter_si1.Y() + inter_si2.Y() + inter_i1i2.Y())/3);
	alt_vector.SetZ((inter_si1.Z() + inter_si2.Z() + inter_i1i2.Z())/3);


	track3d_point.SetX((track_p_si1_1.X() + track_p_si2_1.X() + track_p_i1i2_1.X())/3);
	track3d_point.SetY((track_p_si1_1.Y() + track_p_si2_1.Y() + track_p_i1i2_1.Y())/3);
	track3d_point.SetZ((track_p_si1_1.Z() + track_p_si2_1.Z() + track_p_i1i2_1.Z())/3);

	track3d_vector = alt_vector.Unit();

	//std::cout << "track3d_vector.X() " << track3d_vector.X() << std::endl;
	//std::cout << "track3d_vector.Y() " << track3d_vector.Y() << std::endl;

	//std::cout << "1 " << alt_vector.X() << std::endl;
	//std::cout << "2ux " << track3d_vector.X() << std::endl;
	//std::cout << "p1 " << alt_point.X() << " " << alt_point.Y() << std::endl;
	//std::cout << "p2 " << track3d_point.X() << " " << track3d_point.Y() << std::endl;

}

void Fit3d_HEX::set_detector_position(double _x_lab_position, double _z_lab_position, double _half_x_dim, double _half_z_dim, double _distance_to_1st_layer)
{
	x_lab_position = _x_lab_position;
	z_lab_position = _z_lab_position;
	half_x_dim = _half_x_dim;
	half_z_dim = _half_z_dim;
	distance_to_1st_layer = _distance_to_1st_layer;
}


// =================== fit line to 8 lines ===========================
void Fit3d_HEX::make_fit_to_lines(bool _unbiased_fit)
{
	double z[6];
	z[0] = z_straight[0];
	z[1] = z_inclined1[0];
	z[2] = z_inclined1[1];
	z[3] = z_straight[1];
	z[4] = z_inclined2[0];
	z[5] = z_inclined2[1];

	double errors[6];
	errors[0] = errors_straight[0];
	errors[1] = errors_inclined1[0];
	errors[2] = errors_inclined1[1];
	errors[3] = errors_straight[1];
	errors[4] = errors_inclined2[0];
	errors[5] = errors_inclined2[1];

	double a[4];
	a[0] = y_x_a[1];
	a[1] = y_x_a[1];
	a[2] = y_x_a[2];
	a[3] = y_x_a[2];

	double b[4];
	b[0] = y_x_b[1][0];
	b[1] = y_x_b[1][1];
	b[2] = y_x_b[2][0];
	b[3] = y_x_b[2][1];

	// biased
	LineFit_HEX * lineFit3d_HEX = LineFit_HEX::GetInstance();
	lineFit3d_HEX -> LineFit_HEX::set_z_values(z);
	lineFit3d_HEX -> LineFit_HEX::set_z_reference(z_reference);
	lineFit3d_HEX -> LineFit_HEX::set_x_straight_values(x_straight);
	lineFit3d_HEX -> LineFit_HEX::set_incl_hit_lines_params(a, b);
	lineFit3d_HEX -> LineFit_HEX::set_x_errors(errors);
	//std::cout << "track3d_point.X() " << track3d_point.X() << std::endl;
	//std::cout << "track3d_point.Y() " << track3d_point.Y() << std::endl;
	//std::cout << "track3d_point.Z() " << track3d_point.Z() << std::endl;
	//std::cout << "track3d_vector.X() " << track3d_vector.X() << std::endl;
	//std::cout << "track3d_vector.Y() " << track3d_vector.Y() << std::endl;
	//std::cout << "track3d_vector.Z() " << track3d_vector.Z() << std::endl;
	lineFit3d_HEX -> LineFit_HEX::set_track_point(track3d_point.X(), track3d_point.Y(), track3d_point.Z());
	lineFit3d_HEX -> LineFit_HEX::set_track_vector(track3d_vector.X(), track3d_vector.Y(), track3d_vector.Z()); //(track3d_vector.X(), track3d_vector.Y(), track3d_vector.Z());
	lineFit3d_HEX -> LineFit_HEX::calculate_start_params();
	lineFit3d_HEX -> LineFit_HEX::set_excluded_layer(-1);
	lineFit3d_HEX -> LineFit_HEX::fit_with_minuit();
	track3d_fit_point = lineFit3d_HEX -> LineFit_HEX::return_track_point();
	track3d_fit_vector = lineFit3d_HEX -> LineFit_HEX::return_track_vector(); // normalized to 1 (NOT to uz = 1)
	errflag = lineFit3d_HEX -> LineFit_HEX::err_flag();
	chisq = lineFit3d_HEX -> LineFit_HEX::get_chisq();
	//std::cout << " chisq " << chisq << std::endl;
	lineFit3d_HEX -> LineFit_HEX::~LineFit_HEX();

	// unbiased
//	unbiased_fit = _unbiased_fit;
//	LineFit_HEX * lineFit3d_HEX_Unbiased[6];
//	for (int i = 0; i < 6; i++)
//	{
//		lineFit3d_HEX_Unbiased[i] = LineFit_HEX::GetInstance();
//		if (unbiased_fit) lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::set_excluded_layer(i);
//		else lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::set_excluded_layer(-1);
//		lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::set_z_values(z);
//		lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::set_z_reference(z_reference);
//		lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::set_x_straight_values(x_straight);
//		lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::set_incl_hit_lines_params(a, b);
//		lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::set_x_errors(errors);
//		lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::set_track_point(track3d_point.X(), track3d_point.Y(), track3d_point.Z());
//		lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::set_track_vector(track3d_vector.X(), track3d_vector.Y(), track3d_vector.Z());
//		lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::calculate_start_params();
//		lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::fit_with_minuit();
//		track3d_fit_point_unbiased[i] = lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::return_track_point();
//		track3d_fit_vector_unbiased[i] = lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::return_track_vector();
//		errflag_unbiased[i] = lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::err_flag();
//		chisq_unbiased[i] = lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::get_chisq();
//		lineFit3d_HEX_Unbiased[i] -> LineFit_HEX::~LineFit_HEX();
//	}
	// UncorrelatedOpt * track_optimization = UncorrelatedOpt::GetInstance();
	// track_optimization -> UncorrelatedOpt::set_z_values(z);
	// track_optimization -> UncorrelatedOpt::set_x_straight_values(x_straight);
	// track_optimization -> UncorrelatedOpt::set_incl_hit_lines_params(a, b);
	// track_optimization -> UncorrelatedOpt::set_track_point(track3d_point.X(), track3d_point.Y(), track3d_point.Z());
	// track_optimization -> UncorrelatedOpt::set_track_vector(track3d_vector.X(), track3d_vector.Y(), track3d_vector.Z());
	// track_optimization -> UncorrelatedOpt::fit_with_minuit();
	// track3d_fit_point = track_optimization -> UncorrelatedOpt::return_track_point();
	// track3d_fit_vector = track_optimization -> UncorrelatedOpt::return_track_vector();
	// errflag = track_optimization -> UncorrelatedOpt::err_flag();
	// chisq = track_optimization -> UncorrelatedOpt::get_chisq();
}

bool Fit3d_HEX::err_flag()
{
	if(unbiased_fit)
	{
		errflag = errflag_unbiased[0]&&errflag_unbiased[1]&&errflag_unbiased[2]&&errflag_unbiased[3]&&errflag_unbiased[4]&&errflag_unbiased[5];
	}
	return errflag;
}

double Fit3d_HEX::get_chisq()
{
	return chisq;
}

double Fit3d_HEX::get_chisq(int _layer)
{
	return chisq_unbiased[_layer];
}

double Fit3d_HEX::get_track_8lines_projection_params(int direction, int a_b)
{
	double A, B, C; // track projection parameters
	// line Ax + By +C = 0
	// [A,B] - vector perpendicular to the track
	// [projection_x, projection_y] - vector parallel to the track
	// [-projection_y, projection_x] - vector perpendicular to the track
	if (direction==0) // straight
	{
		A = -projection_straight_fit.Z();
		B = projection_straight_fit.X();
	}

	if (direction==1) // inclined1
	{
		A = -projection_inclined1_fit.Y();
		B = projection_inclined1_fit.X();
	}

	if (direction==2) // inclined2
	{
		A = -projection_inclined2_fit.Y();
		B = projection_inclined2_fit.X();
	}

	// point which belongs to the 3d track belongs also to each of the projections
	// Axp + Byp + C == 0
	double xp, yp;
	xp = track3d_fit_point.X();
	yp = track3d_fit_point.Y();

	C = -(A*xp + B*yp);

	// By = -Ax -C
	// y = -A/B*x -C/B
	// y =    a*x+ b
	double a, b;
	a = -A/B;
	b = -C/B;

	//std::cout << "A: " << TMath::ATan(a)*TMath::RadToDeg() << std::endl;

	double return_par;
	if (a_b == 0) return_par = a;
	if (a_b == 1) return_par = b;

	return return_par;
}

TVector3 Fit3d_HEX::return_track_point()
{
	return track3d_fit_point;
}

TVector3 Fit3d_HEX::return_track_point(int _layer_no)
{
	return track3d_fit_point_unbiased[ _layer_no ];
}

TVector3 Fit3d_HEX::return_track_vector()
{
	return track3d_fit_vector;
}

TVector3 Fit3d_HEX::return_track_vector(int _layer_no)
{
	return track3d_fit_vector_unbiased[ _layer_no ];
}

void Fit3d_HEX::calculate_wire_track_distances()
{
	int straight[2];
	int inclined[4];
	straight[0] = 0;
	straight[1] = 3;
	inclined[0] = 1;
	inclined[1] = 2;
	inclined[2] = 4;
	inclined[3] = 5;

	double z[4];
	z[0] = z_inclined1[0];
	z[1] = z_inclined1[1];
	z[2] = z_inclined2[0];
	z[3] = z_inclined2[1];

	double a[4];
	a[0] = y_x_a_wire[1];
	a[1] = y_x_a_wire[1];
	a[2] = y_x_a_wire[2];
	a[3] = y_x_a_wire[2];

	double b[4];
	b[0] = y_x_b_wire[1][0];
	b[1] = y_x_b_wire[1][1];
	b[2] = y_x_b_wire[2][0];
	b[3] = y_x_b_wire[2][1];

	// scaling
	double t, t2;
	// points in which the line goes through the certain z plane
	double xi, yi;
	double xp[6], yp[6], zp[6];
	double ux[6], uy[6], uz[6];
	if (unbiased_fit==false)
	{
		for (int i = 0; i < 6; i++)
		{
			zp[i] = track3d_fit_point.Z();
			//std::cout << track3d_fit_point.Z() << std::endl;
			xp[i] = track3d_fit_point.X();
			yp[i] = track3d_fit_point.Y();
			ux[i] = track3d_fit_vector.X();
			uy[i] = track3d_fit_vector.Y();
			uz[i] = track3d_fit_vector.Z();

			//std::cout << "a " << uz[i] << std::endl;
		}
	}
	if (unbiased_fit==true)
	{
		for (int i = 0; i < 6; i++)
		{
			zp[i] = track3d_fit_point_unbiased[i].Z();
			xp[i] = track3d_fit_point_unbiased[i].X();
			yp[i] = track3d_fit_point_unbiased[i].Y();
			ux[i] = track3d_fit_vector_unbiased[i].X();
			uy[i] = track3d_fit_vector_unbiased[i].Y();
			uz[i] = track3d_fit_vector_unbiased[i].Z();
			//std::cout << "a " << uz[i] << std::endl;
		}
	}
	
	for (int i=0;i<2; i++)
	{
		//delta  = (((y[i]-par[1])/par[0])-x[i])/errors[i];
		t = z_straight[i] - zp[ straight[i] ];//TMath::Abs(z[ straight[i] ] - zp);
		//std::cout << "t: " << t << " z: " << z_straight[i] << std::endl;
		t2 = 1/uz[ straight[i] ];
		xi = t*t2*ux[ straight[i] ] + xp[ straight[i] ];
		//std::cout << "x_straight_wires[i] " << x_straight_wires[i] << " xi " << xi << std::endl;
		yi = t*t2*uy[ straight[i] ] + yp[ straight[i] ];
		wire_track_dist[ straight[i] ]  = TMath::Abs(x_straight_wires[i] - xi);
		//std::cout << "str " << straight[i]+1 << " " << wire_track_dist[ straight[i] ] << std::endl;
	}

	for (int i = 0; i < 4; i++)
	{
		t = z[i] - zp[ inclined[i] ];
		t2 = 1/uz[ inclined[i] ];
		xi = t*t2*ux[ inclined[i] ] + xp[ inclined[i] ];
		yi = t*t2*uy[ inclined[i] ] + yp[ inclined[i] ];
		wire_track_dist[ inclined[i] ]  = TMath::Abs(a[i]*xi-yi+b[i])*pow(pow((a[i]*a[i]+1),0.5),-1);
		//std::cout << "incl " << inclined[i]+1 << " " << wire_track_dist[ inclined[i] ] << std::endl;
	}

	//for (int i = 0; i < 6; i++)
	//{
		//std::cout << "l " << i+1 << std::endl;
		//if (i==0) std::cout << "z " << z_straight[0] << std::endl;
		//if (i==1) std::cout << "z " << z[0] << std::endl;
		//if (i==2) std::cout << "z " << z[1] << std::endl;
		//if (i==3) std::cout << "z " << z_straight[1] << std::endl;
		//if (i==4) std::cout << "z " << z[2] << std::endl;
		//if (i==5) std::cout << "z " << z[3] << std::endl;
		//std::cout << " " << i+1 << " " << wire_track_dist[ i ] << std::endl;
	//}

}

double Fit3d_HEX::get_wire_track_dist(int _layer_no)
{
	return wire_track_dist[_layer_no];
}

double Fit3d_HEX::calculate_phi_xz()
{
	double phi_xz;
	// calculate vector projected onto xz plane
	double vx, vz, norm;
	vx = track3d_fit_vector.X();
	vz = track3d_fit_vector.Z();
	norm = pow(vx*vx+vz*vz,0.5);
	vx = vx*pow(norm,-1);
	vz = vz*pow(norm,-1);
	// calculate angle between Ox and vector
	phi_xz = TMath::ACos(vx)*180*pow(3.14,-1);
	return phi_xz;
}

double Fit3d_HEX::calculate_phi_xz(int _layer_no)
{
	double phi_xz;
	// calculate vector projected onto xz plane
	double vx, vz, norm;
	vx = track3d_fit_vector_unbiased[_layer_no].X();
	vz = track3d_fit_vector_unbiased[_layer_no].Z();
	norm = pow(vx*vx+vz*vz,0.5);
	vx = vx*pow(norm,-1);
	vz = vz*pow(norm,-1);
	// calculate angle between Ox and vector
	phi_xz = TMath::ACos(vx)*180*pow(3.14,-1);
	return phi_xz;
}

double Fit3d_HEX::calculate_theta_y()
{
	double theta_y = 0;
	double vz, vy, norm;
	vz = track3d_fit_vector.Z();
	vy = track3d_fit_vector.Y();
	norm = pow(vz*vz+vy*vy,0.5);
	vz = vz*pow(norm,-1);
	vy = vy*pow(norm,-1);
	// calculate angle between Ox and vector
	theta_y = TMath::ACos(vy)*180*pow(3.14,-1);
	return theta_y;
}

double Fit3d_HEX::calculate_theta_y(int _layer_no)
{
	double theta_y = 0;
	double vz, vy, norm;
	vz = track3d_fit_vector_unbiased[_layer_no].Z();
	vy = track3d_fit_vector_unbiased[_layer_no].Y();
	norm = pow(vz*vz+vy*vy,0.5);
	vz = vz*pow(norm,-1);
	vy = vy*pow(norm,-1);
	// calculate angle between Ox and vector
	theta_y = TMath::ACos(vy)*180*pow(3.14,-1);
	return theta_y;
}