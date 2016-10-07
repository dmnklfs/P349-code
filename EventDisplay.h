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
	void ReverseXAxis (TMultiGraph *h);
	TCanvas *canv;
	TMultiGraph *AllHits;

	double range_x_min, range_x_max;
	double range_z_min, range_z_max;

	bool draw;

	// just test
	TGraph *D1_scheme;
	double D1_x[5], D1_z[5], D1_x_rotated[5], D1_z_rotated[5];
	double D1_x_offset, D1_z_offset;
	double D1_y_rotation_angle;
	 // Redraw the new axis
	
};

#endif