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
	x_inclined1[0] = _x[2];
	z_inclined1[0] = _y[2];
	errors_inclined1[0] = _errors[2];
	x_inclined1[1] = _x[3];
	z_inclined1[1] = _y[3];
	errors_inclined1[1] = _errors[3];
	x_inclined2[0] = _x[4];
	z_inclined2[0] = _y[4];
	errors_inclined2[0] = _errors[4];
	x_inclined2[1] = _x[5];
	z_inclined2[1] = _y[5];
	errors_inclined2[1] = _errors[5];
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
	// straight
	y_x_a[0] = 0;
	y_x_b[0][0] = 0;
	y_x_b[0][1] = 0;
	// inclined 1
	y_x_a[1] = TMath::Tan(59*3.14*pow(180,-1));
	y_x_b[1][0] = -x_inclined1[0]*y_x_a[1];
	y_x_b[1][1] = -x_inclined1[1]*y_x_a[1];
	// inclined 2
	y_x_a[2] =-TMath::Tan(59*3.14*pow(180,-1));
	y_x_b[2][0] = -x_inclined2[0]*y_x_a[2];
	y_x_b[2][1] = -x_inclined2[1]*y_x_a[2];

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

void Fit3d::calculate_3d_track_parameters()
{
	TVector3 track_p_si1_1, track_p_si1_2, track_p_si2_1, track_p_si2_2, track_p_i1i2_1, track_p_i1i2_2;
	double scale;
	// points on the intersection line at z = 0
	track_p_si1_1.SetZ(0);
	track_p_si2_1.SetZ(0);
	track_p_i1i2_1.SetZ(0);
	//    s i1
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

void Fit3d::calculate_projections_on_hit_planes_calculations()
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

void Fit3d::calculate_projections_on_hit_planes_fit()
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

void Fit3d::draw_event()
{
	double tempx,tempy, tempz;
	TFile f3("file3.root","UPDATE");
	TString name = Form("test_%d", event_no);
	TCanvas *test = new TCanvas(name,name);
	test->SetFillColor(0);
	test->SetBorderMode(0);
	test->SetBorderSize(2);
	test->SetFrameBorderMode(0);
	// view options
	TView3D *view = (TView3D*) TView::CreateView(1);
	//    view range
	double x_range_min, x_range_max, y_range_min, y_range_max, z_range_min, z_range_max;
	double dc_height = 25;
	double dc_half_height = 0.5*dc_height;
	double dc_y_center = y_x_a[1]*(y_x_b[2][0]-y_x_b[1][0])/(y_x_a[1]-y_x_a[2])+y_x_b[1][0];
	x_range_min = -10;//x_lab_position-half_x_dim;
	x_range_max =  10;
	y_range_min = dc_y_center - dc_half_height;
	y_range_max = dc_y_center + dc_half_height;
	z_range_min = z_lab_position-half_z_dim;
	z_range_max = z_lab_position+half_z_dim;

	double dc_z_min = z_straight[0] - 3.3;
	double dc_z_max = z_straight[3] + 3.3;
	//    axis options
	// view->SetRange(x_range_min, y_range_min, z_range_min, x_range_max, y_range_max, z_range_max, 1);
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
	// drawing chamber 
	TMarker3DBox *drift_chamber = new TMarker3DBox (x_lab_position, dc_y_center, z_lab_position, half_x_dim, dc_half_height, half_z_dim, 0, 0);
	
	// ==================== straight hit planes ====================
	int color[3];
	color[0]=6;
	color[1]=38;
	color[2]=46;
	// ========== wires ==========
	// wire1
	TPolyLine3D *yx_fcn_straight_w1 = new TPolyLine3D(2);
	yx_fcn_straight_w1->SetPoint(0, x_straight[0], y_range_min, z_straight[0]);
	yx_fcn_straight_w1->SetPoint(1, x_straight[0], y_range_max, z_straight[0]);
	yx_fcn_straight_w1->SetLineColor(color[0]);
	yx_fcn_straight_w1->SetLineWidth(2);


	// wire2
	TPolyLine3D *yx_fcn_straight_w2 = new TPolyLine3D(2);
	yx_fcn_straight_w2->SetPoint(0, x_straight[1], y_range_min, z_straight[1]);
	yx_fcn_straight_w2->SetPoint(1, x_straight[1], y_range_max, z_straight[1]);
	yx_fcn_straight_w2->SetLineColor(color[0]);
	yx_fcn_straight_w2->SetLineWidth(2);


	// wire3
	TPolyLine3D *yx_fcn_straight_w3 = new TPolyLine3D(2);
	yx_fcn_straight_w3->SetPoint(0, x_straight[2], y_range_min, z_straight[2]);
	yx_fcn_straight_w3->SetPoint(1, x_straight[2], y_range_max, z_straight[2]);
	yx_fcn_straight_w3->SetLineColor(color[0]);
	yx_fcn_straight_w3->SetLineWidth(2);


	// wire4
	TPolyLine3D *yx_fcn_straight_w4 = new TPolyLine3D(2);
	yx_fcn_straight_w4->SetPoint(0, x_straight[3], y_range_min, z_straight[3]);
	yx_fcn_straight_w4->SetPoint(1, x_straight[3], y_range_max, z_straight[3]);
	yx_fcn_straight_w4->SetLineColor(color[0]);
	yx_fcn_straight_w4->SetLineWidth(2);


	// inclined hit plane 1
	// wire1
	TPolyLine3D *yx_fcn_inclined1_w1 = new TPolyLine3D(2);
	yx_fcn_inclined1_w1->SetPoint(0, (y_range_min - y_x_b[1][0])/y_x_a[1], y_range_min, z_inclined1[0]);
	yx_fcn_inclined1_w1->SetPoint(1, (y_range_max - y_x_b[1][0])/y_x_a[1], y_range_max, z_inclined1[0]);
	yx_fcn_inclined1_w1->SetLineColor(color[1]);
	yx_fcn_inclined1_w1->SetLineWidth(2);

	// wire2
	TPolyLine3D *yx_fcn_inclined1_w2 = new TPolyLine3D(2);
	yx_fcn_inclined1_w2->SetPoint(0, (y_range_min - y_x_b[1][1])/y_x_a[1], y_range_min, z_inclined1[1]);
	yx_fcn_inclined1_w2->SetPoint(1, (y_range_max - y_x_b[1][1])/y_x_a[1], y_range_max, z_inclined1[1]);
	yx_fcn_inclined1_w2->SetLineColor(color[1]);
	yx_fcn_inclined1_w2->SetLineWidth(2);

	// inclined hit plane 2
	// wire1
	TPolyLine3D *yx_fcn_inclined2_w1 = new TPolyLine3D(2);
	yx_fcn_inclined2_w1->SetPoint(0, (y_range_min - y_x_b[2][0])/y_x_a[2], y_range_min, z_inclined2[0]);
	yx_fcn_inclined2_w1->SetPoint(1, (y_range_max - y_x_b[2][0])/y_x_a[2], y_range_max, z_inclined2[0]);
	yx_fcn_inclined2_w1->SetLineWidth(3);
	yx_fcn_inclined2_w1->SetLineColor(color[2]);

	// wire2
	TPolyLine3D *yx_fcn_inclined2_w2 = new TPolyLine3D(2);
	yx_fcn_inclined2_w2->SetPoint(0, (y_range_min - y_x_b[2][1])/y_x_a[2], y_range_min, z_inclined2[1]);
	yx_fcn_inclined2_w2->SetPoint(1, (y_range_max - y_x_b[2][1])/y_x_a[2], y_range_max, z_inclined2[1]);
	yx_fcn_inclined2_w2->SetLineWidth(3);
	yx_fcn_inclined2_w2->SetLineColor(color[2]);

	// ========== planes ==========
	TPolyLine3D *straight_hit_plane = new TPolyLine3D(5);
	straight_hit_plane->SetPoint(0, (dc_z_min - z_x_b[0])*pow(z_x_a[0],-1), y_range_min, dc_z_min);
	straight_hit_plane->SetPoint(1, (dc_z_min - z_x_b[0])*pow(z_x_a[0],-1), y_range_max, dc_z_min);
	straight_hit_plane->SetPoint(2, (dc_z_max - z_x_b[0])*pow(z_x_a[0],-1), y_range_max, dc_z_max);
	straight_hit_plane->SetPoint(3, (dc_z_max - z_x_b[0])*pow(z_x_a[0],-1), y_range_min, dc_z_max);
	straight_hit_plane->SetPoint(4, (dc_z_min - z_x_b[0])*pow(z_x_a[0],-1), y_range_min, dc_z_min);
	straight_hit_plane->SetLineWidth(3);
	straight_hit_plane->SetLineColor(color[0]);

	TPolyLine3D *inclined1_hit_plane = new TPolyLine3D(5);
	inclined1_hit_plane->SetPoint(0, -TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_min - z_x_b[1])*pow(z_x_a[1],-1), 0 - dc_half_height, dc_z_min);
	inclined1_hit_plane->SetPoint(1, +TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_min - z_x_b[1])*pow(z_x_a[1],-1), 0 + dc_half_height, dc_z_min);
	inclined1_hit_plane->SetPoint(2, +TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_max - z_x_b[1])*pow(z_x_a[1],-1), 0 + dc_half_height, dc_z_max);
	inclined1_hit_plane->SetPoint(3, -TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_max - z_x_b[1])*pow(z_x_a[1],-1), 0 - dc_half_height, dc_z_max);
	inclined1_hit_plane->SetPoint(4, -TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_min - z_x_b[1])*pow(z_x_a[1],-1), 0 - dc_half_height, dc_z_min);
	inclined1_hit_plane->SetLineWidth(3);
	inclined1_hit_plane->SetLineColor(color[1]);
	TPolyLine3D *inclined1_hit_plane_center = new TPolyLine3D(2);
	inclined1_hit_plane_center->SetPoint(0, (dc_z_min - z_x_b[1])*pow(z_x_a[1],-1), 0, dc_z_min);
	inclined1_hit_plane_center->SetPoint(1, (dc_z_max - z_x_b[1])*pow(z_x_a[1],-1), 0, dc_z_max);
	inclined1_hit_plane_center->SetLineColor(color[1]);

	TPolyLine3D *inclined2_hit_plane = new TPolyLine3D(5);
	inclined2_hit_plane->SetPoint(0,  TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_min - z_x_b[2])*pow(z_x_a[2],-1), 0 - dc_half_height, dc_z_min);
	inclined2_hit_plane->SetPoint(1, -TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_min - z_x_b[2])*pow(z_x_a[2],-1), 0 + dc_half_height, dc_z_min);
	inclined2_hit_plane->SetPoint(2, -TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_max - z_x_b[2])*pow(z_x_a[2],-1), 0 + dc_half_height, dc_z_max);
	inclined2_hit_plane->SetPoint(3,  TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_max - z_x_b[2])*pow(z_x_a[2],-1), 0 - dc_half_height, dc_z_max);
	inclined2_hit_plane->SetPoint(4,  TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_min - z_x_b[2])*pow(z_x_a[2],-1), 0 - dc_half_height, dc_z_min);
	inclined2_hit_plane->SetLineWidth(3);
	inclined2_hit_plane->SetLineColor(color[2]);

	TPolyLine3D *inclined2_hit_plane_center = new TPolyLine3D(2);
	inclined2_hit_plane_center->SetPoint(0, (dc_z_min - z_x_b[2])*pow(z_x_a[2],-1), 0, dc_z_min);
	inclined2_hit_plane_center->SetPoint(1, (dc_z_max - z_x_b[2])*pow(z_x_a[2],-1), 0, dc_z_max);
	inclined2_hit_plane_center->SetLineColor(color[2]);

	// ==================== punkty nalezace do plaszczyzn ===============
	TPolyMarker3D *straight_plane_point = new TPolyMarker3D(1);
	straight_plane_point->SetPoint(0, (z_straight[0] - z_x_b[0])*pow(z_x_a[0],-1), 0, z_straight[0]);
    straight_plane_point->SetMarkerStyle(20);
    //straight_plane_point->Draw();

    TPolyMarker3D *inclined1_plane_point = new TPolyMarker3D(1);
	inclined1_plane_point->SetPoint(0, x_inclined1[0], 0, z_inclined1[0]);
    inclined1_plane_point->SetMarkerStyle(20);
    //inclined1_plane_point->Draw();

    TPolyMarker3D *inclined2_plane_point = new TPolyMarker3D(1);
	inclined2_plane_point->SetPoint(0, x_inclined2[0], 0, z_inclined2[0]);
    inclined2_plane_point->SetMarkerStyle(20);
    //inclined2_plane_point->Draw();


	// ==================== normal to the hit planes ====================
	double scale = 30;
	TPolyLine3D *normal_st = new TPolyLine3D(2);
	normal_st->SetPoint(0, (dc_z_min - z_x_b[0])*pow(z_x_a[0],-1), y_range_min, dc_z_min);
	normal_st->SetPoint(1, (dc_z_min - z_x_b[0])*pow(z_x_a[0],-1)+scale*normal_straight.X(), y_range_min+scale*normal_straight.Y(), dc_z_min+scale*normal_straight.Z());
	normal_st->SetLineWidth(3);
	normal_st->SetLineColor(color[0]);

	TPolyLine3D *normal_i1 = new TPolyLine3D(2);
	normal_i1->SetPoint(0, -TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_min - z_x_b[1])*pow(z_x_a[1],-1), 0 - dc_half_height, dc_z_min);
	normal_i1->SetPoint(1, -TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_min - z_x_b[1])*pow(z_x_a[1],-1)+scale*normal_inclined1.X(), 0 - dc_half_height+scale*normal_inclined1.Y(), dc_z_min+scale*normal_inclined1.Z());
	normal_i1->SetLineWidth(3);
	normal_i1->SetLineColor(color[1]);

	TPolyLine3D *in1_i1 = new TPolyLine3D(2);
	in1_i1->SetPoint(0, -TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_min - z_x_b[1])*pow(z_x_a[1],-1), 0 - dc_half_height, dc_z_min);
	in1_i1->SetPoint(1, -TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_min - z_x_b[1])*pow(z_x_a[1],-1)+scale*xz_inclined1[0], 0 - dc_half_height, dc_z_min+scale*xz_inclined1[2]);
	in1_i1->SetLineWidth(3);
	in1_i1->SetLineColor(color[0]);

	TPolyLine3D *in2_i1 = new TPolyLine3D(2);
	in2_i1->SetPoint(0, -TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_min - z_x_b[1])*pow(z_x_a[1],-1), 0 - dc_half_height, dc_z_min);
	in2_i1->SetPoint(1, -TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_min - z_x_b[1])*pow(z_x_a[1],-1)+scale*xy_inclined1[0], 0 - dc_half_height+scale*xy_inclined1[1], dc_z_min+scale*xy_inclined1[2]);
	in2_i1->SetLineWidth(3);
	in2_i1->SetLineColor(kRed);

	TPolyLine3D *normal_i2 = new TPolyLine3D(2);
	normal_i2->SetPoint(0,  TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_min - z_x_b[2])*pow(z_x_a[2],-1), 0 - dc_half_height, dc_z_min);
	normal_i2->SetPoint(1,  TMath::Tan(31*3.141592654/180)*dc_half_height + (dc_z_min - z_x_b[2])*pow(z_x_a[2],-1)+scale*normal_inclined2.X(), 0 - dc_half_height+scale*normal_inclined2.Y(), dc_z_min+scale*normal_inclined2.Z());
	normal_i2->SetLineWidth(3);
	normal_i2->SetLineColor(color[2]);

	// ==================== intersection points ==========================
	TPolyMarker3D *inter_p_si1 = new TPolyMarker3D(1);
    inter_p_si1->SetPoint(0, inter_point_si1.X(), inter_point_si1.Y(), inter_point_si1.Z());
    inter_p_si1->SetMarkerStyle(20);

    TPolyMarker3D *inter_p_si2 = new TPolyMarker3D(1);
    inter_p_si2->SetPoint(0, inter_point_si2.X(), inter_point_si2.Y(), inter_point_si2.Z());
    inter_p_si2->SetMarkerStyle(20);

    TPolyMarker3D *inter_p_i1i2 = new TPolyMarker3D(1);
    inter_p_i1i2->SetPoint(0, inter_point_i1i2.X(), inter_point_i1i2.Y(), inter_point_i1i2.Z());
    inter_p_i1i2->SetMarkerStyle(20);

    // ===================== hits in inclined =============================
    TPolyMarker3D *hit1 = new TPolyMarker3D(1);
    hit1->SetPoint(0, x_inclined1[0], 0, z_inclined1[0]);
    hit1->SetMarkerStyle(20);
    //hit1->Draw();

    TPolyMarker3D *hit2 = new TPolyMarker3D(1);
    hit2->SetPoint(0, x_inclined1[1], 0, z_inclined1[1]);
    hit2->SetMarkerStyle(20);
    //hit2->Draw();

    // ===================== intersection lines ===========================
	TPolyLine3D *inter_line_si1 = new TPolyLine3D(2);
	inter_line_si1->SetPoint(0,inter_point_si1.X()+scale*inter_si1.X(),inter_point_si1.Y()+scale*inter_si1.Y(),inter_point_si1.Z()+scale*inter_si1.Z());
	inter_line_si1->SetPoint(1,inter_point_si1.X()-scale*inter_si1.X(),inter_point_si1.Y()-scale*inter_si1.Y(),inter_point_si1.Z()-scale*inter_si1.Z());
	inter_line_si1->SetLineWidth(3);
	inter_line_si1->SetLineColor(1);

	TPolyLine3D *inter_line_si2 = new TPolyLine3D(2);
	inter_line_si2->SetPoint(0,inter_point_si2.X()+scale*inter_si2.X(),inter_point_si2.Y()+scale*inter_si2.Y(),inter_point_si2.Z()+scale*inter_si2.Z());
	inter_line_si2->SetPoint(1,inter_point_si2.X()-scale*inter_si2.X(),inter_point_si2.Y()-scale*inter_si2.Y(),inter_point_si2.Z()-scale*inter_si2.Z());
	inter_line_si2->SetLineWidth(3);
	inter_line_si2->SetLineColor(5);

	TPolyLine3D *inter_line_i1i2 = new TPolyLine3D(2);
	inter_line_i1i2->SetPoint(0,inter_point_i1i2.X()+scale*inter_i1i2.X(),inter_point_i1i2.Y()+scale*inter_i1i2.Y(),inter_point_i1i2.Z()+scale*inter_i1i2.Z());
	inter_line_i1i2->SetPoint(1,inter_point_i1i2.X()-scale*inter_i1i2.X(),inter_point_i1i2.Y()-scale*inter_i1i2.Y(),inter_point_i1i2.Z()-scale*inter_i1i2.Z());
	inter_line_i1i2->SetLineWidth(3);
	inter_line_i1i2->SetLineColor(3);

	// ========================= 3d TRACK =================================
	TPolyMarker3D *track_point = new TPolyMarker3D(1);
	track_point->SetPoint(0, track3d_point.X(), track3d_point.Y(), track3d_point.Z());
    track_point->SetMarkerStyle(20);
    track_point->SetMarkerColor(2);

    TPolyLine3D *track3d = new TPolyLine3D(2);
	track3d->SetPoint(0,track3d_point.X()+scale*track3d_vector.X(),track3d_point.Y()+scale*track3d_vector.Y(),track3d_point.Z()+scale*track3d_vector.Z());
	track3d->SetPoint(1,track3d_point.X()-scale*track3d_vector.X(),track3d_point.Y()-scale*track3d_vector.Y(),track3d_point.Z()-scale*track3d_vector.Z());
	track3d->SetLineWidth(3);
	track3d->SetLineColor(2);

	// ================== projections on the wire planes ===================
	TPolyLine3D *track3d_proj_straight = new TPolyLine3D(2);
	track3d_proj_straight->SetPoint(0,track3d_point.X()+scale*projection_straight.X(),track3d_point.Y()+scale*projection_straight.Y(),track3d_point.Z()+scale*projection_straight.Z());
	track3d_proj_straight->SetPoint(1,track3d_point.X()-scale*projection_straight.X(),track3d_point.Y()-scale*projection_straight.Y(),track3d_point.Z()-scale*projection_straight.Z());
	track3d_proj_straight->SetLineWidth(3);
	track3d_proj_straight->SetLineColor(kMagenta+2);

	TPolyLine3D *track3d_proj_inclined1 = new TPolyLine3D(2);
	track3d_proj_inclined1->SetPoint(0,track3d_point.X()+scale*projection_inclined1.X(),track3d_point.Y()+scale*projection_inclined1.Y(),track3d_point.Z()+scale*projection_inclined1.Z());
	track3d_proj_inclined1->SetPoint(1,track3d_point.X()-scale*projection_inclined1.X(),track3d_point.Y()-scale*projection_inclined1.Y(),track3d_point.Z()-scale*projection_inclined1.Z());
	track3d_proj_inclined1->SetLineWidth(3);
	track3d_proj_inclined1->SetLineColor(kBlue+1);

	TPolyLine3D *track3d_proj_inclined2 = new TPolyLine3D(2);
	track3d_proj_inclined2->SetPoint(0,track3d_point.X()+0.5*scale*projection_inclined2.X(),track3d_point.Y()+0.5*scale*projection_inclined2.Y(),track3d_point.Z()+0.5*scale*projection_inclined2.Z());
	track3d_proj_inclined2->SetPoint(1,track3d_point.X()-0.5*scale*projection_inclined2.X(),track3d_point.Y()-0.5*scale*projection_inclined2.Y(),track3d_point.Z()-0.5*scale*projection_inclined2.Z());
	track3d_proj_inclined2->SetLineWidth(3);
	track3d_proj_inclined2->SetLineColor(kOrange+2);

	// ==================== 8 lines fit ==================================
	TPolyLine3D *track3d_8lines_fit = new TPolyLine3D(2);
	track3d_8lines_fit->SetPoint(0,track3d_fit_point.X(),track3d_fit_point.Y(),track3d_fit_point.Z());
	track3d_8lines_fit->SetPoint(1,track3d_fit_point.X()+1.5*scale*track3d_fit_vector.X(),track3d_fit_point.Y()+1.5*scale*track3d_fit_vector.Y(),track3d_fit_point.Z()+1.5*scale*track3d_fit_vector.Z());
	track3d_8lines_fit->SetLineWidth(3);
	track3d_8lines_fit->SetLineColor(kGreen+2);

	// its projections
	TPolyLine3D *track3d_8lines_fit_straight = new TPolyLine3D(2);
	track3d_8lines_fit_straight->SetPoint(0,track3d_fit_point.X(),track3d_fit_point.Y(),track3d_fit_point.Z());
	track3d_8lines_fit_straight->SetPoint(1,track3d_fit_point.X()+1.5*scale*projection_straight_fit.X(),track3d_fit_point.Y()+1.5*scale*projection_straight_fit.Y(),track3d_fit_point.Z()+1.5*scale*projection_straight_fit.Z());
	track3d_8lines_fit_straight->SetLineWidth(3);
	track3d_8lines_fit_straight->SetLineColor(kAzure-1);

	TPolyLine3D *track3d_8lines_fit_inclined1 = new TPolyLine3D(2);
	track3d_8lines_fit_inclined1->SetPoint(0,track3d_fit_point.X(),track3d_fit_point.Y(),track3d_fit_point.Z());
	track3d_8lines_fit_inclined1->SetPoint(1,track3d_fit_point.X()+1.5*scale*projection_inclined1_fit.X(),track3d_fit_point.Y()+1.5*scale*projection_inclined1_fit.Y(),track3d_fit_point.Z()+1.5*scale*projection_inclined1_fit.Z());
	track3d_8lines_fit_inclined1->SetLineWidth(3);
	track3d_8lines_fit_inclined1->SetLineColor(kAzure-1);

	TPolyLine3D *track3d_8lines_fit_inclined2 = new TPolyLine3D(2);
	track3d_8lines_fit_inclined2->SetPoint(0,track3d_fit_point.X(),track3d_fit_point.Y(),track3d_fit_point.Z());
	track3d_8lines_fit_inclined2->SetPoint(1,track3d_fit_point.X()+1.5*scale*projection_inclined2_fit.X(),track3d_fit_point.Y()+1.5*scale*projection_inclined2_fit.Y(),track3d_fit_point.Z()+1.5*scale*projection_inclined2_fit.Z());
	track3d_8lines_fit_inclined2->SetLineWidth(3);
	track3d_8lines_fit_inclined2->SetLineColor(kAzure-1);

	//drift_chamber -> Draw();
	yx_fcn_straight_w1->Draw();
	yx_fcn_straight_w2->Draw();
	yx_fcn_straight_w3->Draw();
	yx_fcn_straight_w4->Draw();
	yx_fcn_inclined1_w1->Draw();
	yx_fcn_inclined1_w2->Draw();
	yx_fcn_inclined2_w1->Draw();
	yx_fcn_inclined2_w2->Draw();
	//straight_hit_plane->Draw();
	//inclined1_hit_plane->Draw();
	//inclined1_hit_plane_center->Draw();
	//inclined2_hit_plane->Draw();
	//inclined2_hit_plane_center->Draw();
	//inter_p_si1->Draw();
	//inter_p_si2->Draw();
	//inter_p_i1i2->Draw();
	//inter_line_si1->Draw();
	//inter_line_si2->Draw();
	//inter_line_i1i2->Draw();
	//normal_st->Draw();
	//normal_i1->Draw();
	//normal_i2->Draw();
	//in1_i1->Draw();
	//in2_i1->Draw();
	//track_point->Draw();
	track3d->Draw();
	//track3d_proj_straight->Draw();
	//track3d_proj_inclined1->Draw();
	//track3d_proj_inclined2->Draw();
	track3d_8lines_fit -> Draw();
	track3d_8lines_fit_straight -> Draw();
	track3d_8lines_fit_inclined1 -> Draw();
	track3d_8lines_fit_inclined2 -> Draw();

	test->Write();
	//test -> SaveAs(name, name);
	f3.Close();
}

// =================== fit line to 8 lines ===========================
void Fit3d::make_fit_to_lines()
{
	double z[8];
	z[0] = z_straight[0];
	z[1] = z_straight[1];
	z[2] = z_inclined1[0];
	z[3] = z_inclined1[1];
	z[4] = z_inclined2[0];
	z[5] = z_inclined2[1];
	z[6] = z_straight[2];
	z[7] = z_straight[3];

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

	LineFit * lineFit3d = LineFit::GetInstance();
	lineFit3d -> set_z_values(z);
	lineFit3d -> set_x_straight_values(x_straight);
	lineFit3d -> set_incl_hit_lines_params(a, b);
	lineFit3d -> set_track_point(track3d_point.X(), track3d_point.Y(), track3d_point.Z());
	lineFit3d -> set_track_vector(track3d_vector.X(), track3d_vector.Y(), track3d_vector.Z());
	lineFit3d -> calculate_start_params();
	lineFit3d -> fit_with_minuit();
	track3d_fit_point = lineFit3d -> return_track_point();
	track3d_fit_vector = lineFit3d -> return_track_vector();
	errflag = lineFit3d -> err_flag();
}

bool Fit3d::err_flag()
{
	return errflag;
}

double Fit3d::get_track_8lines_projection_params(int direction, int a_b)
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

TVector3 Fit3d::return_track_point()
{
	return track3d_fit_point;
}

TVector3 Fit3d::return_track_vector()
{
	return track3d_fit_vector;
}

void Fit3d::calculate_wire_track_distances()
{
	// scaling
	double t;
	// points in which the line goes through the certain z plane
	double xi, yi;
	double zp = track3d_fit_point.Z();
	std::cout << zp << std::endl;
	for (i=0;i<4; i++)
	{
		//std::cout << errors[i] << std::endl;
		//delta  = (((y[i]-par[1])/par[0])-x[i])/errors[i];
		t = z[ straight[i] ] - zp;//TMath::Abs(z[ straight[i] ] - zp);
		xi = t*track3d_fit_vector.X() + track3d_fit_point.X();
		yi = t*track3d_fit_vector.Y() + track3d_fit_point.Y();
		delta  = TMath::Abs(x_straight[i] - xi);
		wire_track_dist[i] = delta;
	}

	for (int i = 0; i < 4; i++)
	{
		t = z[2+i] - zp;//TMath::Abs(z[2+i] - zp); // 1st inclined layer no = 2 (3rd layer counting in the beam direction)
		xi = t*track3d_fit_vector.X() + track3d_fit_point.X();
		yi = t*track3d_fit_vector.Y() + track3d_fit_point.Y();
		delta  = (a[i]*xi-yi+b[i])*(a[i]*xi-yi+b[i])/(a[i]*a[i]+1);
		chisq += delta;
	}

}

double Fit3d::return_wire_track_dist(int _layer_no)
{

}
