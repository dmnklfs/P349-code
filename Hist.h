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
	
	TH1F *START_Mean_Time;
	TH1F *START_Time_Up;
	TH1F *START_Time_Down;

	// TOF
	TH1F *TOF_Rough_Layer_Up_Multiplicity;
	TH1F *TOF_Rough_Layer_Down_Multiplicity;
	TH1F *TOF_Preselected_Layer_Up_Multiplicity;
	TH1F *TOF_Preselected_Layer_Down_Multiplicity;

	TH1F *TOF_Rough_Layer_Up_Elements;
	TH1F *TOF_Rough_Layer_Down_Element;
	TH1F *TOF_Preselected_Layer_Up_Element;
	TH1F *TOF_Preselected_Layer_Down_Element;

	TH1F *TOF_Mean_Time;
	TH1F *TOF_Time_Up;
	TH1F *TOF_Time_Down;

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
	TH2F *D1_L1L2[42][2]; // all wires, left - right
	TH2F *D1_L7L8[42][2];
	//TH2F *D1_L1[42];
	//TH2F *D1_L2[42];
	//TH2F *D1_L7[42];
	//TH2F *D1_L8[42];
	//TH1F *D1_channel_multiplicities[8][42];
	TH1F *D1_wires_offsets[8][42];
	TH1F *D1_no_of_planes;
	TH1F *D1_no_of_cells;
	TH2F *D1_no_planes_vs_cells;

	// D2
	TH1F *D2_Rough_Elements[6];
	TH1F *D2_Rough_Multiplicity[6];
	TH1F *D2_Rough_DriftTime[6];
	TH1F *D2_Preselected_Elements[6];
	TH1F *D2_Preselected_Multiplicity[6];
	TH1F *D2_Preselected_DriftTime[6];
	TH1F *D2_wires_offsets[6][42];

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
	TH2F *V_vs_H;

	bool start_histos_rough;
	bool start_histos_preselected;
	bool tof_histos_rough;
	bool tof_histos_preselected;
	bool D1_histos_rough;
	bool D1_histos_preselected;
	bool D2_histos_rough;
	bool D2_histos_preselected;
	bool HEX_histos_rough;
	bool HEX_histos_preselected;
	bool fiber_histos_rough;
	bool fiber_histos_preselected;
	bool inter_histos_rough;
	bool inter_histos_preselected;

private:
	void init_start_histos_rough();
	void init_start_histos_preselected();
	void init_tof_histos_rough();
	void init_tof_histos_preselected();
	void init_D1_histos_rough();
	void init_D1_histos_preselected();
	void init_D2_histos_rough();
	void init_D2_histos_preselected();
	void init_HEX_histos_rough();
	void init_HEX_histos_preselected();
	void init_fiber_histos_rough();
	void init_fiber_histos_preselected();
	void init_inter_histos_rough();
	void init_inter_histos_preselected();
};

#endif

