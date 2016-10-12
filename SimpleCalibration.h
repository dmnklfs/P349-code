#ifndef SIMPLECALIBRATION_H
#define SIMPLECALIBRATION_H

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

struct single_event_data
{
	double positionsX[4]; // from wires
	double positionsZ[4];
	double drift_times[4];
	int left_right[4]; // left - right information
	double track_a;
	double track_b;
	double chi2;
	double bin;

	single_event_data()
	{
		bin = 1;
		chi2 = 1;
	}
	
};

class SimpleCalibration
{
public:
	SimpleCalibration();
	SimpleCalibration(const Config &_config);
	~SimpleCalibration();

	void get_data(data_for_D1_simple_calibration _single_event_data);
	void tell_no_of_events();


private:
	std::vector<single_event_data> CalibrationData; // all data in one vector

	
};

#endif

// ;>