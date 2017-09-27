#ifndef FITTOLINES_H
#define FITTOLINES_H 

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TMinuit.h"
#include <TGraph.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <TGaxis.h>
#include <TF1.h>
#include "TVector3.h"
#include <Math/Factory.h>
#include <Math/Functor.h>
#include "P349_data.h"
#include <numeric>
#include <boost/filesystem.hpp>
#include <cmath>
#include <math.h> 
#include <fstream>
#include <string>
#include <sstream>
#include <TMath.h>
#include <TMarker3DBox.h>
#include <TPolyLine3D.h>
#include "MinuitFit.h"
#include "LineFitD1D2.h"
#include "UncorrelatedOpt.h"
#include "TView3D.h"
#include "TView.h"
#include "TAxis3D.h"
#include <TPolyMarker3D.h>
//#include "GSLError.h"

class FitToLines
{
public:
	FitToLines();
	FitToLines(int _event_no);
	~FitToLines();
	void set_values(double *_x, double *_y, double *_errors, double *_x_wires);
	void set_z_reference(double z);
	void fit_straight_layer();
	void fit_inclined_layers();
	void calculate_xy_functions();
	void calculate_wires_xy_functions();
	void set_hit_planes_vectors();
	void calculate_normal_to_hit_planes();
	void calculate_hit_planes_eq();
	void calculate_intersection_vectors();
	void calculate_intersection_points();
	void calculate_3d_track_parameters();void calculate_projections_on_hit_planes_calculations();
	void calculate_projections_on_hit_planes_fit();
	bool err_flag();

	void draw_event();

	// from 3d fitting (not calculation)
	TVector3 return_track_point();
	TVector3 return_track_vector();
	double get_chisq();
	double calculate_phi_xz();
	double calculate_theta_y();
	void set_no_of_iteration(int _no_of_iteration);

private:
	double z_reference;
	int event_no;
	bool unbiased_fit;
	// data for fit
	double x_straight_wires[6];
	double x_straight[6],  z_straight[6],  errors_straight[6];

	double x_inclined1_wires[4], x_inclined2_wires[4];
	double x_inclined1[4], z_inclined1[4], errors_inclined1[4];
	double x_inclined2[4], z_inclined2[4], errors_inclined2[4];
	
	// results of the fit in the zx plane
	double z_x_a[3], z_x_b[3]; // 0 - straight, 1 - inclined \, 2 - inclined /
	double y_x_a[3], y_x_b[3][4];

	// 0 - straight, 1 - inclined1 \, 2 - inclined2 /
	double y_x_a_wire[3], y_x_b_wire[3][4];

	// vectors in the xz plane
	TVector3 xz_straight;
	TVector3 xz_inclined1;
	TVector3 xz_inclined2;

	// vectors in the xy plane
	TVector3 xy_straight;
	TVector3 xy_inclined1;
	TVector3 xy_inclined2;

	// vectors normal to the planes
	TVector3 normal_straight, normal_inclined1, normal_inclined2;	

	// planes equations
	double hit_plane_A[3], hit_plane_B[3], hit_plane_C[3], hit_plane_D[3];

	// intersections of planes
	//    vectors
	TVector3 inter_si1, inter_si2, inter_i1i2;
	//    points at z=0
	TVector3 inter_point_si1, inter_point_si2, inter_point_i1i2;

	// 3d track parameters
	//    vector
	TVector3 calculated_track3d_vector;
	//    point
	TVector3 calculated_track3d_point;

	// projections of the track on the planes
	//   vertors (directions)
	TVector3 projection_straight, projection_inclined1, projection_inclined2;
	TVector3 projection_straight_fit, projection_inclined1_fit, projection_inclined2_fit;
	//   lines equations (z_x in all planes)
	double proj_z_x_a[3];
	double proj_z_x_b[3];

	// for plotting - only? 27.09.17
	double half_x_dim;
	double half_z_dim;
	double x_lab_position;
	double z_lab_position;
	double distance_to_1st_layer;
	bool errflag;

	int no_of_iteration;

};


#endif