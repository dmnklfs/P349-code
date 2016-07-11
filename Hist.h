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

	// --- CONTROL SPECTRA ----
	// START
	TH1F *START_Rough_Layer_Up_Multiplicity;
	TH1F *START_Rough_Layer_Down_Multiplicity;
	TH1F *START_Preselected_Layer_Up_Multiplicity;
	TH1F *START_Preselected_Layer_Down_Multiplicity;
	
	// TOF
	TH1F *TOF_Rough_Layer_Up_Multiplicity;
	TH1F *TOF_Rough_Layer_Down_Multiplicity;
	TH1F *TOF_Preselected_Layer_Up_Multiplicity;
	TH1F *TOF_Preselected_Layer_Down_Multiplicity;

	TH1F *TOF_Rough_Layer_Up_Elements;
	TH1F *TOF_Rough_Layer_Down_Element;
	TH1F *TOF_Preselected_Layer_Up_Element;
	TH1F *TOF_Preselected_Layer_Down_Element;

	// D1
	TH1F *D1_Rough_Elements[8];
	TH1F *D1_Rough_Multiplicity[8];
	TH1F *D1_Rough_DriftTime[8];
	TH1F *D1_Preselected_Elements[8];
	TH1F *D1_Preselected_Multiplicity[8];
	TH1F *D1_Preselected_DriftTime[8];

	
};

#endif

