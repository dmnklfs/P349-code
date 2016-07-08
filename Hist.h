#ifndef HIST_H
#define HIST_H
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

class Hist
{
public:
	Hist();
	~Hist();
	std::vector<TH1F> return_histos();

// private ??
	TH1F *Rough_Layer_Up_Multiplicity;
	TH1F *Rough_Layer_Down_Multiplicity;
	TH1F *Preselected_Layer_Up_Multiplicity;
	TH1F *Preselected_Layer_Down_Multiplicity;
	// some more?
	
};

#endif

