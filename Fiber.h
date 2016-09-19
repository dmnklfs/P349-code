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
{
public:
	Fiber();
	Fiber(const Config &_config);
	~Fiber();
	void fill_good_hits(single_gh_data _good_hit_data);
	bool was_correct_event();
	void check_hits();
	Fiber_hist_data* get_hist_data();

private:
	void choose_corr_leading_V();
	void choose_corr_leading_H();
	void choose_corr_leading_D();
	bool check_elements_range_V(int element);
	bool check_elements_range_H(int element);
	bool check_elements_range_D(int element);
	bool check_size_V();
	bool check_size_H();
	bool check_size_D();

	// config
	double element_V_min;
	double element_V_max;
	double element_H_min;
	double element_H_max;
	double element_D_min;
	double element_D_max;
	double hit_V_min;
	double hit_V_max;
	double hit_H_min;
	double hit_H_max;
	double hit_D_min;
	double hit_D_max;

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