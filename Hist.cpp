#include "Hist.h"

Hist::Hist()
{ 
	Rough_Layer_Up_Multiplicity = new TH1F("Rough data start layer up multiplicity", "Rough start layer up multiplicity", 10, -0.5, 9.5);
	Rough_Layer_Down_Multiplicity = new TH1F("Rough data start layer down multiplicity", "Rough start layer down multiplicity", 10, -0.5, 9.5);
	Preselected_Layer_Up_Multiplicity = new TH1F("Preselected data start layer up multiplicity", "Preselected start layer up multiplicity", 10, -0.5, 9.5);
	Preselected_Layer_Down_Multiplicity = new TH1F("Preselected data start layer down multiplicity", "Preselected start layer down multiplicity", 10, -0.5, 9.5);
}

Hist::~Hist()
{
	
}