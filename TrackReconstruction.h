#ifndef TRACKRECONSTRUCTION_H
#define TRACKRECONSTRUCTION_H

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TMinuit.h"
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TGaxis.h>
#include <TF1.h>
#include <Math/Factory.h>
#include <Math/Functor.h>
#include <numeric>
#include <boost/filesystem.hpp>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "struct.h"
#include "Config.h"
#include "MinuitFit.h"
#include "Fit3d_HEX.h"
#include "Fit3d_D2.h"
#include "Fit3d.h"
//#include "TrackReconstructionLayer.h"
#include <TMath.h>

struct track_reco_data
{
	double x_hit_pos_D1[8];
	double x_err_hit_pos_D1[8];
	double z_hit_pos_D1[8];
	double chi2_D1;
	bool errflag_D1;

	double x_hit_pos_D2[6];
	double x_err_hit_pos_D2[6];
	double z_hit_pos_D2[6];
	double chi2_D2;
	bool errflag_D2;

	double x_hit_pos_HEX[7];
	double x_err_hit_pos_HEX[7];
	double z_hit_pos_HEX[7];
	double chi2_HEX;
	bool errflag_HEX;

	track_reco_data() // make correct init for errflags
	{
		chi2_D1 = -1;
		chi2_D2 = -1;
		chi2_HEX = -1;
	}
};

class TrackReconstruction
{
public:

	TrackReconstruction();
	TrackReconstruction(const Config &_config);
	~TrackReconstruction();

	void get_data(data_for_track_reconstruction _single_event_data);
	void tell_no_of_events();
	void fit_events_in_D1();
	void fit_in_3d_D1();
	void fit_events_in_D2();
	void fit_in_3d_D2();
	void fit_events_in_HEX();
	void fit_in_3d_HEX();
	void deletations();

	double calculate_phi_xz();
	double calculate_theta_y();

private:
	// ReconstructionLayer_D1 *Layer[8];
	// ReconstructionLayer_D2 *Layer[6];
	// ReconstructionLayer_HEX *Layer[7];

	std::vector<track_reco_data> TrackRecoData;

	TVector3 track3d_fit_point_D1, track3d_fit_vector_D1;
	TVector3 track3d_fit_point_D2, track3d_fit_vector_D2;
	TVector3 track3d_fit_point_HEX, track3d_fit_vector_HEX;

	std::vector<double> chisq_D1; // remove? 05.09.2017
	std::vector<double> chisq_D2;
	std::vector<double> chisq_HEX;


	double half_x_dim_D1;
	double half_x_dim_D2;
	double half_x_dim_HEX;
	double half_z_dim_D1;
	double half_z_dim_D2;
	double half_z_dim_HEX;
	double x_lab_position_D1;
	double x_lab_position_D2;
	double x_lab_position_HEX;
	double z_lab_position_D1;
	double z_lab_position_D2;
	double z_lab_position_HEX;
};

#endif

// ;>