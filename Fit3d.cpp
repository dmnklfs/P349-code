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
	//MinuitFit * fit1 = MinuitFit::GetInstance();
	//fit1 -> set_no_of_points(2);		
	//fit1 -> MinuitFit::set_values(x_inclined1, z_inclined1, errors_inclined1);
	//fit1 -> MinuitFit::perform_simplified_fit();
	//results = fit1 -> MinuitFit::fit_with_minuit();
	std::cout << " ----- " << std::endl;
	std::cout << x_inclined1[0] << " " << z_inclined1[0] << " " << errors_inclined1[0] << std::endl;
	std::cout << x_inclined1[1] << " " << z_inclined1[1] << " " << errors_inclined1[1] << std::endl;
	//z_x_a[1] = results.at(0);
	//z_x_b[1] = results.at(1);
	z_x_a[1] = (z_inclined1[0]-z_inclined1[1])/(x_inclined1[0]-x_inclined1[1]);
	z_x_b[1] = z_inclined1[0] - z_x_a[1]*x_inclined1[0];
	std::cout << z_x_a[1] << " " << z_x_b[1] << std::endl;

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
	yp = y_x_a[1]*xp + y_x_b[1][0];
	hit_plane_D[1] = -(hit_plane_A[1]*xp + hit_plane_B[1]*yp);

	xp = -z_x_b[2]*pow(z_x_a[2],-1);
	yp = y_x_a[2]*xp + y_x_b[2][0];
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
	double dc_height = 50;
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
	view->SetRange(x_range_min, y_range_min, z_range_min, x_range_max, y_range_max, z_range_max, 1);
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
	drift_chamber -> Draw();
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

	//yx_fcn_straight_w1->Draw();
	//yx_fcn_straight_w2->Draw();
	//yx_fcn_straight_w3->Draw();
	//yx_fcn_straight_w4->Draw();
	//yx_fcn_inclined1_w1->Draw();
	//yx_fcn_inclined1_w2->Draw();
	//yx_fcn_inclined2_w1->Draw();
	//yx_fcn_inclined2_w2->Draw();
	straight_hit_plane->Draw();
	inclined1_hit_plane->Draw();
	inclined1_hit_plane_center->Draw();
	inclined2_hit_plane->Draw();
	inclined2_hit_plane_center->Draw();

	test->Write();
	//test -> SaveAs(name, name);
	f3.Close();
}