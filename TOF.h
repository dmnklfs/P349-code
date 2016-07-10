#ifndef TOF_H
#define TOF_H
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

class TOF
	: public Config
{
public:
	TOF();
	~TOF();
	void fill_good_hits(const int _stage, single_gh_data _good_hit_data);
	bool was_correct_event();
	void check_hits();
	TOF_hist_data get_hist_data();

private:
	bool check_signal(std::vector<int> & Edge, std::vector<double > & Time);
	bool check_size_up();
	bool check_size_down();
	bool check_time_range(double treal);
	bool check_elements(std::vector<int> & _ElementDown, std::vector<int> & _ElementUp);
	bool check_elements_range(std::vector<int> & _Elements);
	void fill_data_if_correct();

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