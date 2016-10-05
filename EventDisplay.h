#ifndef EVENTDISPLAY_H
#define EVENTDISPLAY_H
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
#include "P349_data.h"
#include "Config.h"
#include "struct.h"

class EventDisplay
{
public:
	EventDisplay();
	EventDisplay(int i, const Config&_config, event_to_display _event);
	~EventDisplay();

private:
	// just test
	double D1_x[5], D1_z[5], D1_x_rotated[5], D1_z_rotated[5];

	TCanvas *canv;
	TGraph *graph;
	TGraph *D1_scheme;
	
};

#endif