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
#include "struct.h"

class Hist
{
public:
	Hist();
	~Hist();

	void fill_start_histos_rough(start_hist_data* _start_data);
	void fill_start_histos_preselected(start_hist_data* _start_data);

	void fill_TOF_histos_rough(TOF_hist_data* _tof_data);
	void fill_TOF_histos_preselected(TOF_hist_data* _tof_data);

	void fill_Intermediate_histos_rough(TOF_hist_data* _tof_data);
	void fill_Intermediate_histos_preselected(TOF_hist_data* _tof_data);

	void fill_D1_histos_rough(D1_hist_data* _d1_data);
	void fill_D1_histos_preselected(D1_hist_data* _d1_data);

	void fill_D2_histos_rough(D2_hist_data* _d2_data);
	void fill_D2_histos_preselected(D2_hist_data* _d2_data);

	void fill_HEX_histos_rough(HEX_hist_data* _hex_data);
	void fill_HEX_histos_preselected(HEX_hist_data* _hex_data);

	void fill_Fiber_histos_rough(Fiber_hist_data* _fiber_data);
	void fill_Fiber_histos_preselected(Fiber_hist_data* _fiber_data);

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

	// Intermediate
	TH1F *Intermediate_Rough_Layer_Up_Multiplicity;
	TH1F *Intermediate_Rough_Layer_Down_Multiplicity;
	TH1F *Intermediate_Preselected_Layer_Up_Multiplicity;
	TH1F *Intermediate_Preselected_Layer_Down_Multiplicity;

	TH1F *Intermediate_Rough_Layer_Up_Elements;
	TH1F *Intermediate_Rough_Layer_Down_Element;
	TH1F *Intermediate_Preselected_Layer_Up_Element;
	TH1F *Intermediate_Preselected_Layer_Down_Element;

	// D1
	TH1F *D1_Rough_Elements[8];
	TH1F *D1_Rough_Multiplicity[8];
	TH1F *D1_Rough_DriftTime[8];
	TH1F *D1_Preselected_Elements[8];
	TH1F *D1_Preselected_Multiplicity[8];
	TH1F *D1_Preselected_DriftTime[8];

	// D2
	TH1F *D2_Rough_Elements[6];
	TH1F *D2_Rough_Multiplicity[6];
	TH1F *D2_Rough_DriftTime[6];
	TH1F *D2_Preselected_Elements[6];
	TH1F *D2_Preselected_Multiplicity[6];
	TH1F *D2_Preselected_DriftTime[6];

	// HEX
	TH1F *HEX_Rough_Elements[7];
	TH1F *HEX_Rough_Multiplicity[7];
	TH1F *HEX_Rough_DriftTime[7];
	TH1F *HEX_Preselected_Elements[7];
	TH1F *HEX_Preselected_Multiplicity[7];
	TH1F *HEX_Preselected_DriftTime[7];

	// FIBER
	TH1F *Fiber_Rough_Multiplicity[3];
	TH1F *Fiber_Rough_Elements[3];
	TH1F *Fiber_Preselected_Multiplicity[3];
	TH1F *Fiber_Preselected_Elements[3];
};

#endif

