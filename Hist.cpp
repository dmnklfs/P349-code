#include "Hist.h"

Hist::Hist()
{
	TString temp_name;

	// START 
	START_Rough_Layer_Up_Multiplicity = new TH1F("START rough data layer up multiplicity", "START Rough layer up multiplicity;multiplicity;counts", 10, -0.5, 9.5);
	START_Rough_Layer_Down_Multiplicity = new TH1F("START rough data layer down multiplicity", "START Rough layer down multiplicity;multiplicity;counts", 10, -0.5, 9.5);
	START_Preselected_Layer_Up_Multiplicity = new TH1F("START preselected data layer up multiplicity", "START preselected layer up multiplicity;multiplicity;counts", 10, -0.5, 9.5);
	START_Preselected_Layer_Down_Multiplicity = new TH1F("START preselected data layer down multiplicity", "START preselected layer down multiplicity;multiplicity;counts", 10, -0.5, 9.5);

	// TOF
	TOF_Rough_Layer_Up_Multiplicity = new TH1F("TOF rough data layer up multiplicity", "TOF rough layer up multiplicity;multiplicity;counts", 10, -0.5, 9.5);
	TOF_Rough_Layer_Down_Multiplicity = new TH1F("TOF rough data layer down multiplicity", "TOF rough layer down multiplicity;multiplicity;counts", 10, -0.5, 9.5);
	TOF_Preselected_Layer_Up_Multiplicity = new TH1F("TOF preselected data layer up multiplicity", "TOF preselected layer up multiplicity;multiplicity;counts", 10, -0.5, 9.5);
	TOF_Preselected_Layer_Down_Multiplicity = new TH1F("TOF preselected data layer down multiplicity", "TOF preselected layer down multiplicity;multiplicity;counts", 10, -0.5, 9.5);

	TOF_Rough_Layer_Up_Elements = new TH1F("TOF rough data layer up element", "TOF rough layer up element;element;counts", 12, -0.5, 11.5);
	TOF_Rough_Layer_Down_Element = new TH1F("TOF rough data layer down element", "TOF rough layer down element;element;counts", 12, -0.5, 11.5);
	TOF_Preselected_Layer_Up_Element = new TH1F("TOF preselected data layer up element", "TOF preselected layer up element;element;counts", 12, -0.5, 11.5);
	TOF_Preselected_Layer_Down_Element = new TH1F("TOF preselected data layer down element", "TOF preselected layer down element;element;counts", 12, -0.5, 11.5);

	// D1
	for (int i = 0; i < 8; i++)
	{
		// rough
		temp_name = Form("D1 rough data layer %d wires;wire;counts", i+1);
		D1_Rough_Elements[i] = new TH1F(temp_name, temp_name, 45, -0.5, 44.5);
		temp_name = Form("D1 rough layer %d multiplicity;multiplicity;counts", i+1);
		D1_Rough_Multiplicity[i] = new TH1F(temp_name, temp_name, 10, -0.5, 9.5);
		temp_name = Form("D1 rough layer %d drift time;drift time [ns];counts", i+1);
		D1_Rough_DriftTime[i] = new TH1F(temp_name, temp_name, 1000, -1500, 1500);
		// preselected
		temp_name = Form("D1 preselected data layer %d wires;wire;counts", i+1);
		D1_Preselected_Elements[i] = new TH1F(temp_name, temp_name, 45, -0.5, 44.5);
		temp_name = Form("D1 preselected layer %d multiplicity;multiplicity;counts", i+1);
		D1_Preselected_Multiplicity[i] = new TH1F(temp_name, temp_name, 10, -0.5, 9.5);
		temp_name = Form("D1 preselected layer %d drift time;drift time [ns];counts", i+1);
		D1_Preselected_DriftTime[i] = new TH1F(temp_name, temp_name, 1000, -1500, 1500);
	}

	// D2
	for (int i = 0; i < 6; i++)
	{
		// rough
		temp_name = Form("D2 rough data layer %d wires;wire;counts", i+1);
		D2_Rough_Elements[i] = new TH1F(temp_name, temp_name, 45, -0.5, 44.5);
		temp_name = Form("D2 rough layer %d multiplicity;multiplicity;counts", i+1);
		D2_Rough_Multiplicity[i] = new TH1F(temp_name, temp_name, 10, -0.5, 9.5);
		temp_name = Form("D2 rough layer %d drift time;drift time [ns];counts", i+1);
		D2_Rough_DriftTime[i] = new TH1F(temp_name, temp_name, 1000, -1500, 1500);
		// preselected
		temp_name = Form("D2 preselected data layer %d wires;wire;counts", i+1);
		D2_Preselected_Elements[i] = new TH1F(temp_name, temp_name, 45, -0.5, 44.5);
		temp_name = Form("D2 preselected layer %d multiplicity;multiplicity;counts", i+1);
		D2_Preselected_Multiplicity[i] = new TH1F(temp_name, temp_name, 10, -0.5, 9.5);
		temp_name = Form("D2 preselected layer %d drift time;drift time [ns];counts", i+1);
		D2_Preselected_DriftTime[i] = new TH1F(temp_name, temp_name, 1000, -1500, 1500);
	}
}

Hist::~Hist()
{
	
}