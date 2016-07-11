#include "Hist.h"

Hist::Hist()
{
	TString temp_name;

	// START 
	START_Rough_Layer_Up_Multiplicity = new TH1F("START Rough data start layer up multiplicity", "START Rough start layer up multiplicity", 10, -0.5, 9.5);
	START_Rough_Layer_Down_Multiplicity = new TH1F("START Rough data start layer down multiplicity", "START Rough start layer down multiplicity", 10, -0.5, 9.5);
	START_Preselected_Layer_Up_Multiplicity = new TH1F("START Preselected data start layer up multiplicity", "START Preselected start layer up multiplicity", 10, -0.5, 9.5);
	START_Preselected_Layer_Down_Multiplicity = new TH1F("START Preselected data start layer down multiplicity", "START Preselected start layer down multiplicity", 10, -0.5, 9.5);

	// TOF
	TOF_Rough_Layer_Up_Multiplicity = new TH1F("TOF Rough data start layer up multiplicity", "TOF Rough start layer up multiplicity", 10, -0.5, 9.5);
	TOF_Rough_Layer_Down_Multiplicity = new TH1F("TOF Rough data start layer down multiplicity", "TOF Rough start layer down multiplicity", 10, -0.5, 9.5);
	TOF_Preselected_Layer_Up_Multiplicity = new TH1F("TOF Preselected data start layer up multiplicity", "TOF Preselected start layer up multiplicity", 10, -0.5, 9.5);
	TOF_Preselected_Layer_Down_Multiplicity = new TH1F("TOF Preselected data start layer down multiplicity", "TOF Preselected start layer down multiplicity", 10, -0.5, 9.5);

	TOF_Rough_Layer_Up_Elements = new TH1F("TOF Rough data start layer up element", "TOF Rough start layer up element", 12, -0.5, 11.5);
	TOF_Rough_Layer_Down_Element = new TH1F("TOF Rough data start layer down element", "TOF Rough start layer down element", 12, -0.5, 11.5);
	TOF_Preselected_Layer_Up_Element = new TH1F("TOF preselected data start layer up element", "TOF preselected start layer up element", 12, -0.5, 11.5);
	TOF_Preselected_Layer_Down_Element = new TH1F("TOF preselected data start layer down element", "TOF preselected start layer down element", 12, -0.5, 11.5);

	// D1
	for (int i = 0; i < 8; i++)
	{
		// rough
		temp_name = Form("D1 Rough Layer %d Elements", i+1);
		D1_Rough_Elements[i] = new TH1F(temp_name, temp_name, 45, -0.5, 44.5);
		temp_name = Form("D1 Rough Layer %d Multiplicity", i+1);
		D1_Rough_Multiplicity[i] = new TH1F(temp_name, temp_name, 10, -0.5, 9.5);
		temp_name = Form("D1 Rough Layer %d Drift Time", i+1);
		D1_Rough_DriftTime[i] = new TH1F(temp_name, temp_name, 1000, -1500, 1500);
		// preselected
		temp_name = Form("D1 Preselected Layer %d Elements", i+1);
		D1_Preselected_Elements[i] = new TH1F(temp_name, temp_name, 45, -0.5, 44.5);
		temp_name = Form("D1 Preselected Layer %d Multiplicity", i+1);
		D1_Preselected_Multiplicity[i] = new TH1F(temp_name, temp_name, 10, -0.5, 9.5);
		temp_name = Form("D1 Preselected Layer %d Drift Time", i+1);
		D1_Preselected_DriftTime[i] = new TH1F(temp_name, temp_name, 1000, -1500, 1500);
	}
}

Hist::~Hist()
{
	
}