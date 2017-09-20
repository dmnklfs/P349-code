#include "FitD1D2.h"

FitD1D2::FitD1D2()
{

}

FitD1D2::FitD1D2(int _event_no)
{
	event_no = _event_no;
	unbiased_fit = false;
	z_reference = 0;
}

FitD1D2::~FitD1D2()
{

}

void FitD1D2::set_no_of_iteration(int _no_of_iteration)
{
	no_of_iteration = _no_of_iteration;
}

void FitD1D2::set_values(double *_x, double *_y, double *_errors, double *_x_wires)
{
	// straight
	x_straight[0]       = _x[4];
	x_straight_wires[0] = _x_wires[4];
	z_straight[0]       = _y[4];
	errors_straight[0]  = _errors[4];

	x_straight[1]       = _x[5];
	x_straight_wires[1] = _x_wires[5];
	z_straight[1]       = _y[5];
	errors_straight[1]  = _errors[5];

	x_straight[2]       = _x[6];
	x_straight_wires[2] = _x_wires[6];
	z_straight[2]       = _y[6];
	errors_straight[2]  = _errors[6];

	x_straight[3]       = _x[7];
	x_straight_wires[3] = _x_wires[7];
	z_straight[3]       = _y[7];
	errors_straight[3]  = _errors[7];

	x_straight[4]       = _x[12];
	x_straight_wires[4] = _x_wires[12];
	z_straight[4]       = _y[12];
	errors_straight[4]  = _errors[12];

	x_straight[5]       = _x[13];
	x_straight_wires[5] = _x_wires[13];
	z_straight[5]       = _y[13];
	errors_straight[5]  = _errors[13];

	// inclined
	x_inclined1[0]       = _x[0];
	x_inclined1_wires[0] = _x_wires[0];
	z_inclined1[0]       = _y[0];
	errors_inclined1[0]  = _errors[0];

	x_inclined1[1]       = _x[1];
	x_inclined1_wires[1] = _x_wires[1];
	z_inclined1[1]       = _y[1];
	errors_inclined1[1]  = _errors[1];

	x_inclined1[2]       = _x[8];
	x_inclined1_wires[2] = _x_wires[8];
	z_inclined1[2]       = _y[8];
	errors_inclined1[2]  = _errors[8];

	x_inclined1[3]       = _x[9];
	x_inclined1_wires[3] = _x_wires[9];
	z_inclined1[3]       = _y[9];
	errors_inclined1[3]  = _errors[9];


	x_inclined2[0]       = _x[2];
	x_inclined2_wires[0] = _x_wires[2];
	z_inclined2[0]       = _y[2];
	errors_inclined2[0]  = _errors[2];

	x_inclined2[1]       = _x[3];
	x_inclined2_wires[1] = _x_wires[3];
	z_inclined2[1]       = _y[3];
	errors_inclined2[1]  = _errors[3];

	x_inclined2[2]       = _x[10];
	x_inclined2_wires[2] = _x_wires[10];
	z_inclined2[2]       = _y[10];
	errors_inclined2[2]  = _errors[10];

	x_inclined2[3]       = _x[11];
	x_inclined2_wires[3] = _x_wires[11];
	z_inclined2[3]       = _y[11];
	errors_inclined2[3]  = _errors[11];
}

void FitD1D2::set_z_reference(double z)
{
	z_reference = z;
}

void FitD1D2::fit_straight_layer()
{
	std::vector<double> results;
	MinuitFit * fit = MinuitFit::GetInstance();
	fit -> MinuitFit::set_no_of_points(6);	
	fit -> MinuitFit::set_values(x_straight, z_straight, errors_straight);
	fit -> MinuitFit::perform_simplified_fit_calc_coeff();//perform_simplified_fit();
	results = fit -> MinuitFit::fit_with_minuit();
	z_x_a[0] = results.at(0);
	z_x_b[0] = results.at(1);
	//std::cout << z_x_a[0] << " " << z_x_b[0] << std::endl;
//	for (int i = 0; i < 6; i++)
//	{
//		std::cout << "{" << x_straight[i] << "," << z_straight[i] << "}" << std::endl;
//	}
	//std::cout << z_x_a[0] << " " << z_x_b[0] << std::endl;
	results.clear();
}

void FitD1D2::fit_inclined_layers()
{
	std::vector<double> results;

	MinuitFit * fit1 = MinuitFit::GetInstance();
	fit1 -> MinuitFit::set_no_of_points(4);		
	fit1 -> MinuitFit::set_values(x_inclined1, z_inclined1, errors_inclined1);
	fit1 -> MinuitFit::perform_simplified_fit();
	results = fit1 -> MinuitFit::fit_with_minuit();
	z_x_a[1] = results.at(0);
	z_x_b[1] = results.at(1);
	
	MinuitFit * fit2 = MinuitFit::GetInstance();
	fit2 -> MinuitFit::set_no_of_points(4);		
	fit2 -> MinuitFit::set_values(x_inclined2, z_inclined2, errors_inclined2);
	fit2 -> MinuitFit::perform_simplified_fit();
	results = fit2 -> MinuitFit::fit_with_minuit();
	z_x_a[2] = results.at(0);
	z_x_b[2] = results.at(1);
}

void FitD1D2::calculate_xy_functions()
{
	// dla plaszczyzny z = 0
	// straight
	y_x_a[0] = 0;
	y_x_b[0][0] = 0;
	y_x_b[0][1] = 0;
	y_x_b[0][2] = 0;
	y_x_b[0][3] = 0;
	// inclined 1
	y_x_a[1] = TMath::Tan(59*3.14*pow(180,-1));
	y_x_b[1][0] = -x_inclined1[0]*y_x_a[1];
	y_x_b[1][1] = -x_inclined1[1]*y_x_a[1];
	y_x_b[1][2] = -x_inclined1[2]*y_x_a[1];
	y_x_b[1][3] = -x_inclined1[3]*y_x_a[1];
	// inclined 2
	y_x_a[2] =-TMath::Tan(59*3.14*pow(180,-1));
	y_x_b[2][0] = -x_inclined2[0]*y_x_a[2];
	y_x_b[2][1] = -x_inclined2[1]*y_x_a[2];
	y_x_b[2][2] = -x_inclined2[2]*y_x_a[2];
	y_x_b[2][3] = -x_inclined2[3]*y_x_a[2];
}

void FitD1D2::calculate_wires_xy_functions()
{
	// dla plaszczyzny z = 0
	// straight
	y_x_a_wire[0] = 0;
	y_x_b_wire[0][0] = 0;
	y_x_b_wire[0][1] = 0;
	y_x_b_wire[0][2] = 0;
	y_x_b_wire[0][3] = 0;
	// inclined 1
	y_x_a_wire[1] = TMath::Tan(59*3.14*pow(180,-1));
	y_x_b_wire[1][0] = -x_inclined1_wires[0]*y_x_a_wire[1];
	y_x_b_wire[1][1] = -x_inclined1_wires[1]*y_x_a_wire[1];
	y_x_b_wire[1][2] = -x_inclined1_wires[2]*y_x_a_wire[1];
	y_x_b_wire[1][3] = -x_inclined1_wires[3]*y_x_a_wire[1];
	// inclined 2
	y_x_a_wire[2] =-TMath::Tan(59*3.14*pow(180,-1));
	y_x_b_wire[2][0] = -x_inclined2_wires[0]*y_x_a_wire[2];
	y_x_b_wire[2][1] = -x_inclined2_wires[1]*y_x_a_wire[2];
	y_x_b_wire[2][2] = -x_inclined2_wires[2]*y_x_a_wire[2];
	y_x_b_wire[2][3] = -x_inclined2_wires[3]*y_x_a_wire[2];
}

void FitD1D2::set_hit_planes_vectors()
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

void FitD1D2::calculate_normal_to_hit_planes()
{
	normal_straight  = xy_straight.Cross(xz_straight);
	normal_inclined1 = xy_inclined1.Cross(xz_inclined1);
	normal_inclined2 = xy_inclined2.Cross(xz_inclined2);

	// normalization
	normal_straight  = normal_straight.Unit();
	normal_inclined1 = normal_inclined1.Unit();
	normal_inclined2 = normal_inclined2.Unit();
}

void FitD1D2::calculate_hit_planes_eq()
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

}

void FitD1D2::calculate_intersection_vectors() // intersection line: vectors
{
	inter_si1 = normal_straight.Cross(normal_inclined1);
	inter_si2 = normal_straight.Cross(normal_inclined2);
	inter_i1i2 = normal_inclined1.Cross(normal_inclined2);

	inter_si1.SetX(inter_si1.X()/inter_si1.Z());
	inter_si1.SetY(inter_si1.Y()/inter_si1.Z());
	inter_si1.SetZ(inter_si1.Z()/inter_si1.Z());

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

void FitD1D2::calculate_intersection_points()// intersection line: points
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
}

void FitD1D2::calculate_3d_track_parameters()
{
	TVector3 track_p_si1_1, track_p_si1_2, track_p_si2_1, track_p_si2_2, track_p_i1i2_1, track_p_i1i2_2;
	double scale;
	// points on the intersection line at z = 0
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
	// points on the intersection line at z = 3
	double tempz = 3;
	track_p_si1_2.SetZ(tempz);
	track_p_si2_2.SetZ(tempz);
	track_p_i1i2_2.SetZ(tempz);
	//    s i1
	scale = (tempz-inter_point_si1.Z())/inter_si1.Z();
	track_p_si1_2.SetX(inter_point_si1.X()+scale*inter_si1.X());
	track_p_si1_2.SetY(inter_point_si1.Y()+scale*inter_si1.Y());
	//    s i2
	scale = (tempz-inter_point_si2.Z())/inter_si2.Z();
	track_p_si2_2.SetX(inter_point_si2.X()+scale*inter_si2.X());
	track_p_si2_2.SetY(inter_point_si2.Y()+scale*inter_si2.Y());
	//    i1 i2
	scale = (tempz-inter_point_i1i2.Z())/inter_i1i2.Z();
	track_p_i1i2_2.SetX(inter_point_i1i2.X()+scale*inter_i1i2.X());
	track_p_i1i2_2.SetY(inter_point_i1i2.Y()+scale*inter_i1i2.Y());

	track3d_point.SetX((track_p_si1_1.X() + track_p_si2_1.X() + track_p_i1i2_1.X())/3);
	track3d_point.SetY((track_p_si1_1.Y() + track_p_si2_1.Y() + track_p_i1i2_1.Y())/3);
	track3d_point.SetZ((track_p_si1_1.Z() + track_p_si2_1.Z() + track_p_i1i2_1.Z())/3);

	TVector3 track3d_point2;
	track3d_point2.SetX((track_p_si1_2.X() + track_p_si2_2.X() + track_p_i1i2_2.X())/3);
	track3d_point2.SetY((track_p_si1_2.Y() + track_p_si2_2.Y() + track_p_i1i2_2.Y())/3);
	track3d_point2.SetZ((track_p_si1_2.Z() + track_p_si2_2.Z() + track_p_i1i2_2.Z())/3);

	track3d_vector.SetX(track3d_point2.X() - track3d_point.X());
	track3d_vector.SetY(track3d_point2.Y() - track3d_point.Y());
	track3d_vector.SetZ(track3d_point2.Z() - track3d_point.Z());

	// alternative method of calculation of parameters
	TVector3 alt_vector, alt_point;
	alt_vector.SetX((inter_si1.X() + inter_si2.X() + inter_i1i2.X())/3);
	alt_vector.SetY((inter_si1.Y() + inter_si2.Y() + inter_i1i2.Y())/3);
	alt_vector.SetZ((inter_si1.Z() + inter_si2.Z() + inter_i1i2.Z())/3);
	alt_vector.Unit();

	alt_point.SetX((inter_point_si1.X() + inter_point_i1i2.X() + inter_point_si2.X())/3);
	alt_point.SetY((inter_point_si1.Y() + inter_point_i1i2.Y() + inter_point_si2.Y())/3);
	alt_point.SetZ((inter_point_si1.Z() + inter_point_i1i2.Z() + inter_point_si2.Z())/3);

	track3d_vector = alt_vector.Unit();//track3d_vector.Unit();

	//std::cout << "1 " << alt_vector.X() << std::endl;
	//std::cout << "2ux " << track3d_vector.X() << std::endl;
	//std::cout << "p1 " << alt_point.X() << " " << alt_point.Y() << std::endl;
	//std::cout << "p2 " << track3d_point.X() << " " << track3d_point.Y() << std::endl;

}

void FitD1D2::calculate_projections_on_hit_planes_calculations() // unused, expect from drawings
{
	// to get the direction it is enough to remove from the track vetor
	// the part which is perpendicular to the certain plane

	double angle;

	// straight
	projection_straight.SetX(track3d_vector.X());
	projection_straight.SetY(0);
	projection_straight.SetZ(track3d_vector.Z());
	projection_straight.Unit();
	
	// inclined1
	angle = 31*TMath::DegToRad();
	TVector3 wire_direction_inclined1;
	wire_direction_inclined1.SetXYZ(TMath::Sin(angle), TMath::Cos(angle), 0);
	projection_inclined1 = track3d_vector - track3d_vector.Dot(wire_direction_inclined1)*wire_direction_inclined1;
	projection_inclined1.Unit();

	TVector3 wire_direction_inclined2;
	wire_direction_inclined2.SetXYZ(-TMath::Sin(angle), TMath::Cos(angle), 0);
	projection_inclined2 = track3d_vector - track3d_vector.Dot(wire_direction_inclined2)*wire_direction_inclined2;
	projection_inclined2.Unit();
	
}

void FitD1D2::calculate_projections_on_hit_planes_fit()
{
	double angle;

	// straight
	//std::cout << "track " << track3d_fit_vector.X() << std::endl;
	projection_straight_fit.SetX(track3d_fit_vector.X());
	projection_straight_fit.SetY(0);
	projection_straight_fit.SetZ(track3d_fit_vector.Z());
	projection_straight_fit.Unit();
	//std::cout << "projection track " << projection_straight_fit.X() << std::endl;
	
	// inclined1
	angle = 31*TMath::DegToRad();
	TVector3 wire_direction_inclined1;
	wire_direction_inclined1.SetXYZ(TMath::Sin(angle), TMath::Cos(angle), 0);
	projection_inclined1_fit = track3d_fit_vector - track3d_fit_vector.Dot(wire_direction_inclined1)*wire_direction_inclined1;
	projection_inclined1_fit.Unit();

	TVector3 wire_direction_inclined2;
	wire_direction_inclined2.SetXYZ(-TMath::Sin(angle), TMath::Cos(angle), 0);
	projection_inclined2_fit = track3d_fit_vector - track3d_fit_vector.Dot(wire_direction_inclined2)*wire_direction_inclined2;
	projection_inclined2_fit.Unit();
}

// =================== fit line to 8 lines ===========================
void FitD1D2::make_fit_to_lines(bool _unbiased_fit)
{
	unbiased_fit = _unbiased_fit;
	double z[14];
	z[0]  = z_inclined1[0];
	z[1]  = z_inclined1[1];
	z[2]  = z_inclined2[0];
	z[3]  = z_inclined2[1];
	z[4]  = z_straight[0];
	z[5]  = z_straight[1];
	z[6]  = z_straight[2];
	z[7]  = z_straight[3];
	z[8]  = z_inclined1[2];
	z[9]  = z_inclined1[3];
	z[10] = z_inclined2[2];
	z[11] = z_inclined2[3];
	z[12] = z_straight[4];
	z[13] = z_straight[5];

	double errors[14];
	errors[0]  = errors_inclined1[0];
	errors[1]  = errors_inclined1[1];
	errors[2]  = errors_inclined2[0];
	errors[3]  = errors_inclined2[1];
	errors[4]  = errors_straight[0];
	errors[5]  = errors_straight[1];
	errors[6]  = errors_straight[2];
	errors[7]  = errors_straight[3];
	errors[8]  = errors_inclined1[2];
	errors[9]  = errors_inclined1[3];
	errors[10] = errors_inclined2[2];
	errors[11] = errors_inclined2[3];
	errors[12] = errors_straight[4];
	errors[13] = errors_straight[5];

	// std::cout << "err " << errors[0] << std::endl;

	// for inclined, in the order
	double a[8];
	a[0] = y_x_a[1];
	a[1] = y_x_a[1];
	a[2] = y_x_a[2];
	a[3] = y_x_a[2];
	a[4] = y_x_a[1];
	a[5] = y_x_a[1];
	a[6] = y_x_a[2];
	a[7] = y_x_a[2];

	double b[8];
	b[0] = y_x_b[1][0];
	b[1] = y_x_b[1][1];
	b[2] = y_x_b[2][0];
	b[3] = y_x_b[2][1];
	b[4] = y_x_b[1][2];
	b[5] = y_x_b[1][3];
	b[6] = y_x_b[2][2];
	b[7] = y_x_b[2][3];


//	for (int i = 0; i < 8; i++)
//	{
//		std::cout << "b[i] " << b[i] << std::endl;
//	}

	// biased
	LineFitD1D2 * lineFitD1D2 = LineFitD1D2::GetInstance();
	lineFitD1D2 -> LineFitD1D2::set_z_values(z);
	lineFitD1D2 -> LineFitD1D2::set_z_reference(z_reference);
	lineFitD1D2 -> LineFitD1D2::set_x_straight_values(x_straight);
	lineFitD1D2 -> LineFitD1D2::set_incl_hit_lines_params(a, b);
	lineFitD1D2 -> LineFitD1D2::set_x_errors(errors);
	lineFitD1D2 -> LineFitD1D2::set_track_point(track3d_point.X(), track3d_point.Y(), track3d_point.Z());
	lineFitD1D2 -> LineFitD1D2::set_track_vector(track3d_vector.X(), track3d_vector.Y(), track3d_vector.Z()); //(track3d_vector.X(), track3d_vector.Y(), track3d_vector.Z());
	lineFitD1D2 -> LineFitD1D2::calculate_start_params();
	lineFitD1D2 -> LineFitD1D2::set_excluded_layer(-1);
	lineFitD1D2 -> LineFitD1D2::fit_with_minuit();
	track3d_fit_point = lineFitD1D2 -> LineFitD1D2::return_track_point();
	// /*std::cout << "in fit " << track3d_fit_point.Y() << std::endl;*/
	track3d_fit_vector = lineFitD1D2 -> LineFitD1D2::return_track_vector(); // normalized to 1 (NOT to uz = 1)
	errflag = lineFitD1D2 -> LineFitD1D2::err_flag();
	chisq = lineFitD1D2 -> LineFitD1D2::get_chisq();
	//std::cout << " all " << chisq << std::endl;
	lineFitD1D2 -> LineFitD1D2::~LineFitD1D2();

	if (_unbiased_fit)
	{
		LineFitD1D2 * lineFitD1D2Unbiased[14];
		for (int i = 0; i < 14; i++)
		{
			lineFitD1D2Unbiased[i] = LineFitD1D2::GetInstance();
			if (no_of_iteration == 4 || no_of_iteration == 5) lineFitD1D2Unbiased[i] -> LineFitD1D2::set_excluded_layer(-1);
			else lineFitD1D2Unbiased[i] -> LineFitD1D2::set_excluded_layer(i);
			lineFitD1D2Unbiased[i] -> LineFitD1D2::set_z_values(z);
			lineFitD1D2Unbiased[i] -> LineFitD1D2::set_z_reference(z_reference);
			lineFitD1D2Unbiased[i] -> LineFitD1D2::set_x_straight_values(x_straight);
			lineFitD1D2Unbiased[i] -> LineFitD1D2::set_incl_hit_lines_params(a, b);
			lineFitD1D2Unbiased[i] -> LineFitD1D2::set_x_errors(errors);
			lineFitD1D2Unbiased[i] -> LineFitD1D2::set_track_point(track3d_point.X(), track3d_point.Y(), track3d_point.Z());
			lineFitD1D2Unbiased[i] -> LineFitD1D2::set_track_vector(track3d_vector.X(), track3d_vector.Y(), track3d_vector.Z());
			lineFitD1D2Unbiased[i] -> LineFitD1D2::calculate_start_params();
			lineFitD1D2Unbiased[i] -> LineFitD1D2::fit_with_minuit();
			track3d_fit_point_unbiased[i] = lineFitD1D2Unbiased[i] -> LineFitD1D2::return_track_point();
			track3d_fit_vector_unbiased[i] = lineFitD1D2Unbiased[i] -> LineFitD1D2::return_track_vector();
			errflag_unbiased[i] = lineFitD1D2Unbiased[i] -> LineFitD1D2::err_flag();
			chisq_unbiased[i] = lineFitD1D2Unbiased[i] -> LineFitD1D2::get_chisq();
			lineFitD1D2Unbiased[i] -> LineFitD1D2::~LineFitD1D2();
		}
	}
	
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

bool FitD1D2::err_flag()
{
	if(unbiased_fit)
	{
		errflag = errflag_unbiased[0]&&errflag_unbiased[1]&&errflag_unbiased[2]&&errflag_unbiased[3]&&errflag_unbiased[4]&&errflag_unbiased[5]&&errflag_unbiased[6]&&errflag_unbiased[7]&&errflag_unbiased[8]&&errflag_unbiased[9]&&errflag_unbiased[10]&&errflag_unbiased[11]&&errflag_unbiased[12]&&errflag_unbiased[13];
	}
	return errflag;
}

double FitD1D2::get_chisq()
{
	return chisq;
}

double FitD1D2::get_chisq(int _layer)
{
	return chisq_unbiased[_layer];
}

double FitD1D2::get_track_8lines_projection_params(int direction, int a_b)
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

TVector3 FitD1D2::return_track_point()
{
	return track3d_fit_point;
}

TVector3 FitD1D2::return_track_point(int _layer_no)
{
	return track3d_fit_point_unbiased[ _layer_no ];
}

TVector3 FitD1D2::return_track_vector()
{
	return track3d_fit_vector;
}

TVector3 FitD1D2::return_track_vector(int _layer_no)
{
	return track3d_fit_vector_unbiased[ _layer_no ];
}

void FitD1D2::calculate_wire_track_distances()
{
	int straight[6];
	straight[0] = 4;
	straight[1] = 5;
	straight[2] = 6;
	straight[3] = 7;
	straight[4] =12;
	straight[5] =13;

	int inclined[8];
	inclined[0] = 0;
	inclined[1] = 1;
	inclined[2] = 2;
	inclined[3] = 3;
	inclined[4] = 8;
	inclined[5] = 9;
	inclined[6] =10;
	inclined[7] =11;


	// all inclined
	double z[8];
	z[0] = z_inclined1[0];
	z[1] = z_inclined1[1];
	z[2] = z_inclined2[0];
	z[3] = z_inclined2[1];
	z[4] = z_inclined1[2];
	z[5] = z_inclined1[3];
	z[6] = z_inclined2[2];
	z[7] = z_inclined2[3];

	double a[8];
	a[0] = y_x_a_wire[1];
	a[1] = y_x_a_wire[1];
	a[2] = y_x_a_wire[2];
	a[3] = y_x_a_wire[2];
	a[4] = y_x_a_wire[1];
	a[5] = y_x_a_wire[1];
	a[6] = y_x_a_wire[2];
	a[7] = y_x_a_wire[2];

	double b[8];
	b[0] = y_x_b_wire[1][0];
	b[1] = y_x_b_wire[1][1];
	b[2] = y_x_b_wire[2][0];
	b[3] = y_x_b_wire[2][1];
	b[4] = y_x_b_wire[1][2];
	b[5] = y_x_b_wire[1][3];
	b[6] = y_x_b_wire[2][2];
	b[7] = y_x_b_wire[2][3];

	// scaling
	double t, t2;
	// points in which the line goes through the certain z plane
	double xi, yi;
	double xp[14], yp[14], zp[14];
	double ux[14], uy[14], uz[14];
	if (unbiased_fit==false)
	{
		for (int i = 0; i < 14; i++)
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
		for (int i = 0; i < 14; i++)
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
	
	for (int i=0;i<6; i++)
	{
		//delta  = (((y[i]-par[1])/par[0])-x[i])/errors[i];
		t = z_straight[i] - zp[ straight[i] ];//TMath::Abs(z[ straight[i] ] - zp);
		//std::cout << "t: " << t << " z: " << z_straight[i] << std::endl;
		t2 = 1/uz[ straight[i] ];
		xi = t*t2*ux[ straight[i] ] + xp[ straight[i] ];
		yi = t*t2*uy[ straight[i] ] + yp[ straight[i] ];
		wire_track_dist[ straight[i] ]  = TMath::Abs(x_straight_wires[i] - xi);
		//std::cout << straight[i] << " " << wire_track_dist[ straight[i] ] << std::endl;
	}

	for (int i = 0; i < 8; i++)
	{
		t = z[i] - zp[ inclined[i] ];
		t2 = 1/uz[ inclined[i] ];
		xi = t*t2*ux[ inclined[i] ] + xp[ inclined[i] ];
		yi = t*t2*uy[ inclined[i] ] + yp[ inclined[i] ];
		wire_track_dist[ inclined[i] ]  = TMath::Abs(a[i]*xi-yi+b[i])*pow(pow((a[i]*a[i]+1),0.5),-1);
		//std::cout << inclined[i] << " " << wire_track_dist[ inclined[i] ] << std::endl;
	}
}

double FitD1D2::get_wire_track_dist(int _layer_no)
{
	return wire_track_dist[_layer_no];
}

double FitD1D2::calculate_phi_xz()
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

double FitD1D2::calculate_phi_xz(int _layer_no)
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

double FitD1D2::calculate_theta_y()
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

double FitD1D2::calculate_theta_y(int _layer_no)
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