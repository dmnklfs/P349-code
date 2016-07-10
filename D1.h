#ifndef D1_H
#define D1_H
#include "D1Layer.h"

#define NL1  8
#define NL2  7
#define NL3  6
#define NL4  5
#define NL5  4 
#define NL6  3
#define NL7  2
#define NL8  1

class D1
{
public:
	D1();
	~D1();
	void fill_good_hits(const int _stage, single_gh_data _good_hit_data);
	D1_hist_data get_hist_data();
	bool was_correct_event();

private:
	D1Layer *Layer1;
	D1Layer *Layer2;
	D1Layer *Layer7;
	D1Layer *Layer8;
	bool correct_event;
	// after preselection
	//std::vector<double> DriftTimeLayer1;
	//std::vector<double> DriftTimeLayer2;
	//std::vector<double> DriftTimeLayer3;
	//std::vector<double> DriftTimeLayer4;
	//std::vector<double> DriftTimeLayer5;
	//std::vector<double> DriftTimeLayer6;
	//std::vector<double> DriftTimeLayer7;
	//std::vector<double> DriftTimeLayer8;
	//std::vector<int> WireLayer1;
	//std::vector<int> WireLayer2;
	//std::vector<int> WireLayer3;
	//std::vector<int> WireLayer4;
	//std::vector<int> WireLayer5;
	//std::vector<int> WireLayer6;
	//std::vector<int> WireLayer7;
	//std::vector<int> WireLayer8;
	
};


#endif
