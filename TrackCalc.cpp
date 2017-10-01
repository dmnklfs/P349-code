#include "TrackCalc.h"

TrackCalc::TrackCalc()
{

}

TrackCalc::TrackCalc(int _event_no)
{
	event_no = _event_no;
	unbiased_fit = false;
	z_reference = 0;
}

TrackCalc::~TrackCalc()
{

}

void TrackCalc::set_no_of_iteration(int _no_of_iteration)
{
	no_of_iteration = _no_of_iteration;
}

void TrackCalc::set_values(double *_x, double *_y, double *_errors, double *_x_wires)
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

void TrackCalc::set_z_reference(double z)
{
	z_reference = z;
}

void TrackCalc::fit_straight_layer()
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

void TrackCalc::fit_inclined_layers()
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

void TrackCalc::calculate_xy_functions()
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

void TrackCalc::calculate_wires_xy_functions() // unused? 27.09.17
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

void TrackCalc::set_hit_planes_vectors()
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

void TrackCalc::calculate_normal_to_hit_planes()
{
	normal_straight  = xy_straight.Cross(xz_straight);
	normal_inclined1 = xy_inclined1.Cross(xz_inclined1);
	normal_inclined2 = xy_inclined2.Cross(xz_inclined2);

	// normalization
	normal_straight  = normal_straight.Unit();
	normal_inclined1 = normal_inclined1.Unit();
	normal_inclined2 = normal_inclined2.Unit();
}

void TrackCalc::calculate_hit_planes_eq()
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
	hit_plane_D[1] = -(hit_plane_A[1]*x_inclined1[0] + hit_plane_B[1]*0 + hit_plane_C[1]*z_inclined1[0]);

	zp = z_inclined2[0];
	hit_plane_D[2] = -(hit_plane_A[2]*x_inclined2[0] + hit_plane_B[2]*0 + hit_plane_C[2]*z_inclined2[0]);

}

void TrackCalc::calculate_intersection_vectors() // intersection line: vectors
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

void TrackCalc::calculate_intersection_points()// intersection line: points
{
	inter_point_si1.SetZ(z_reference);
	inter_point_si2.SetZ(z_reference);
	inter_point_i1i2.SetZ(z_reference);

	inter_point_si1.SetX((hit_plane_B[1]*(hit_plane_D[0] + z_reference*hit_plane_C[0]) - hit_plane_B[0]*(hit_plane_D[1] + z_reference*hit_plane_C[1]))*pow(hit_plane_A[1]*hit_plane_B[0] - hit_plane_A[0]*hit_plane_B[1],-1));
	inter_point_i1i2.SetX((hit_plane_B[2]*(hit_plane_D[1] + z_reference*hit_plane_C[1]) - hit_plane_B[1]*(hit_plane_D[2] + z_reference*hit_plane_C[2]))*pow(hit_plane_A[2]*hit_plane_B[1] - hit_plane_A[1]*hit_plane_B[2],-1));
	inter_point_si2.SetX((hit_plane_B[2]*(hit_plane_D[0] + z_reference*hit_plane_C[0]) - hit_plane_B[0]*(hit_plane_D[2] + z_reference*hit_plane_C[2]))*pow(hit_plane_A[2]*hit_plane_B[0] - hit_plane_A[0]*hit_plane_B[2],-1));

	inter_point_si1.SetY((-hit_plane_A[0]*(hit_plane_D[1] + z_reference*hit_plane_C[1]) + hit_plane_A[1]*(hit_plane_D[0] + z_reference*hit_plane_C[0]))*pow(hit_plane_A[0]*hit_plane_B[1] - hit_plane_A[1]*hit_plane_B[0],-1));
	inter_point_i1i2.SetY((-hit_plane_A[1]*(hit_plane_D[2] + z_reference*hit_plane_C[2]) + hit_plane_A[2]*(hit_plane_D[1] + z_reference*hit_plane_C[1]))*pow(hit_plane_A[1]*hit_plane_B[2] - hit_plane_A[2]*hit_plane_B[1],-1));
	inter_point_si2.SetY((-hit_plane_A[2]*(hit_plane_D[0] + z_reference*hit_plane_C[0]) + hit_plane_A[0]*(hit_plane_D[2] + z_reference*hit_plane_C[2]))*pow(hit_plane_A[2]*hit_plane_B[0] - hit_plane_A[0]*hit_plane_B[2],-1));
}

void TrackCalc::calculate_3d_track_parameters()
{
	TVector3 track_p_si1_1, track_p_si1_2, track_p_si2_1, track_p_si2_2, track_p_i1i2_1, track_p_i1i2_2;
	double scale;
	// points on the intersection line at z = reference
	track_p_si1_1.SetZ(z_reference);
	track_p_si2_1.SetZ(z_reference);
	track_p_i1i2_1.SetZ(z_reference);
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


	calculated_track3d_point.SetX((track_p_si1_1.X() + track_p_si2_1.X() + track_p_i1i2_1.X())/3);
	calculated_track3d_point.SetY((track_p_si1_1.Y() + track_p_si2_1.Y() + track_p_i1i2_1.Y())/3);
	calculated_track3d_point.SetZ((track_p_si1_1.Z() + track_p_si2_1.Z() + track_p_i1i2_1.Z())/3);

	calculated_track3d_vector = alt_vector.Unit();
	//calculated_track3d_vector.Unit();
	//std::cout << "1 " << alt_vector.X() << std::endl;
	//std::cout << "2ux " << calculated_track3d_vector.X() << std::endl;
	//std::cout << "p1 " << alt_point.X() << " " << alt_point.Y() << std::endl;
	//std::cout << "p2 " << calculated_track3d_point.X() << " " << calculated_track3d_point.Y() << std::endl;

}

TVector3 TrackCalc::return_approx_track_point()
{
	return calculated_track3d_point;
}

TVector3 TrackCalc::return_approx_track_vector()
{
	return calculated_track3d_vector;
}

