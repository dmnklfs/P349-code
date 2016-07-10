#include "Hist.h"

Hist::Hist()
{
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
	// layer 1
	D1_Rough_Layer1_Elements = new TH1F("D1 Rough Layer1 Elements", "D1 Rough Layer1 Elements", 45, -0.5, 44.5);
	D1_Rough_Layer1_Multiplicity = new TH1F("D1 Rough Layer1 Multiplicity", "D1 Rough Layer1 Multiplicity", 10, -0.5, 9.5);
	D1_Preselected_Layer1_Elements = new TH1F("D1 Preselected Layer1 Elements", "D1 Preselected Layer1 Elements", 45, -0.5, 44.5);
	D1_Preselected_Layer1_Multiplicity = new TH1F("D1 Preselected Layer1 Multiplicity", "D1 Preselected Layer1 Multiplicity", 10, -0.5, 9.5);

	// layer 2
	D1_Rough_Layer2_Elements = new TH1F("D1 Rough Layer2 Elements", "D1 Rough Layer2 Elements", 45, -0.5, 44.5);
	D1_Rough_Layer2_Multiplicity = new TH1F("D1 Rough Layer2 Multiplicity", "D1 Rough Layer2 Multiplicity", 10, -0.5, 9.5);
	D1_Preselected_Layer2_Elements = new TH1F("D1 Preselected Layer2 Elements", "D1 Preselected Layer2 Elements", 45, -0.5, 44.5);
	D1_Preselected_Layer2_Multiplicity = new TH1F("D1 Preselected Layer2 Multiplicity", "D1 Preselected Layer2 Multiplicity", 10, -0.5, 9.5);

	// layer 7
	D1_Rough_Layer7_Elements = new TH1F("D1 Rough Layer7 Elements", "D1 Rough Layer7 Elements", 45, -0.5, 44.5);
	D1_Rough_Layer7_Multiplicity = new TH1F("D1 Rough Layer7 Multiplicity", "D1 Rough Layer7 Multiplicity", 10, -0.5, 9.5);
	D1_Preselected_Layer7_Elements = new TH1F("D1 Preselected Layer7 Elements", "D1 Preselected Layer7 Elements", 45, -0.5, 44.5);
	D1_Preselected_Layer7_Multiplicity = new TH1F("D1 Preselected Layer7 Multiplicity", "D1 Preselected Layer7 Multiplicity", 10, -0.5, 9.5);

	// layer 8
	D1_Rough_Layer8_Elements = new TH1F("D1 Rough Layer8 Elements", "D1 Rough Layer8 Elements", 45, -0.5, 44.5);
	D1_Rough_Layer8_Multiplicity = new TH1F("D1 Rough Layer8 Multiplicity", "D1 Rough Layer8 Multiplicity", 10, -0.5, 9.5);
	D1_Preselected_Layer8_Elements = new TH1F("D1 Preselected Layer8 Elements", "D1 Preselected Layer8 Elements", 45, -0.5, 44.5);
	D1_Preselected_Layer8_Multiplicity = new TH1F("D1 Preselected Layer8 Multiplicity", "D1 Preselected Layer8 Multiplicity", 10, -0.5, 9.5);
}

Hist::~Hist()
{
	
}