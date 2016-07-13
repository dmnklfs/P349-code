#ifndef FIBER_H
#define FIBER_H
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

class Fiber
	: public Config
{
public:
	Fiber();
	~Fiber();
	void fill_good_hits(const int _stage, single_gh_data _good_hit_data);
	bool was_correct_event();
	void check_hits();
	Fiber_hist_data* get_hist_data();

private:
	bool check_size_V();	// ? -> check signals
	bool check_size_H();
	bool check_size_D();
	bool check_elements_range_V();
	bool check_elements_range_H();
	bool check_elements_range_D();
	void fill_data_if_correct();

	// after preselection
	std::vector<int> Fibers_V;
	std::vector<int> Fibers_H;
	std::vector<int> Fibers_D;

	// rough
	std::vector<int> Rough_Fibers_V;
	std::vector<int> Rough_Fibers_H;
	std::vector<int> Rough_Fibers_D;

	std::vector<int> Edge_V;
	std::vector<int> Edge_H;
	std::vector<int> Edge_D;

	bool correct_event;  // was event correct?	

};

#endif