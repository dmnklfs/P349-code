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
	// layer 1
	TH1F *D1_Rough_Layer1_Elements;
	TH1F *D1_Rough_Layer1_Multiplicity;
	TH1F *D1_Preselected_Layer1_Elements;
	TH1F *D1_Preselected_Layer1_Multiplicity;

	// layer 2
	TH1F *D1_Rough_Layer2_Elements;
	TH1F *D1_Rough_Layer2_Multiplicity;
	TH1F *D1_Preselected_Layer2_Elements;
	TH1F *D1_Preselected_Layer2_Multiplicity;

	// layer 7
	TH1F *D1_Rough_Layer7_Elements;
	TH1F *D1_Rough_Layer7_Multiplicity;
	TH1F *D1_Preselected_Layer7_Elements;
	TH1F *D1_Preselected_Layer7_Multiplicity;

	// layer 8
	TH1F *D1_Rough_Layer8_Elements;
	TH1F *D1_Rough_Layer8_Multiplicity;
	TH1F *D1_Preselected_Layer8_Elements;
	TH1F *D1_Preselected_Layer8_Multiplicity;

	
};

#endif

