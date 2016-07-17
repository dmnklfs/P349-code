#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H
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
#include "P349_data.h"
#include <numeric>
#include <boost/filesystem.hpp>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include "Config.h"
#include "struct.h"

class Intermediate
	: public Config
{
public:
	Intermediate();
	~Intermediate();
	void fill_good_hits(single_gh_data _good_hit_data);
	bool was_correct_event();
	void check_hits();
	TOF_hist_data* get_hist_data();

private:
	void choose_corr_leading_up();
	void choose_corr_leading_down();
	bool check_size_up();
	bool check_size_down();
	bool check_time_range(double treal);
	bool check_elements_range(int element);
	bool check_coincidence();

	// after preselection
	std::vector<double> TrealUp;
	std::vector<double> TrealDown;
	std::vector<int> ElementUp;
	std::vector<int> ElementDown;

	// rough data: before preselection
	std::vector<double> RoughTrealUp;
	std::vector<double> RoughTrealDown;
	std::vector<int> RoughElementUp;
	std::vector<int> RoughElementDown;
	std::vector<int> RoughEdgeUp;
	std::vector<int> RoughEdgeDown;

	bool correct_event;  // was event correct?	

};

#endif