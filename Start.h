// tutaj moga byc zdefiniowane wektory z poprawnymi zdarzeniami dla danego detektora
// i wszystkie metody preselekcji
// i metody wyliczenia pozycji z detektora, jesli to mozliwe

// dla komor dryfowych: Hough transf. jako osobna klasa

#ifndef START_H
#define START_H
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

class Start
	: public Config
{
public:
	Start();
	~Start();
	void fill_good_hits(int _stage, int _layer, int _element, double _treal, int _edge);
	bool was_correct_event();
	void check_hits();
	start_hist_data get_hist_data();

private:
	bool check_signal(std::vector<int> & Edge, std::vector<double > & Time);
	bool check_size();
	bool check_time_range(double treal);
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