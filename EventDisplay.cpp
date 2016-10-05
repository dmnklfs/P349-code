#include "EventDisplay.h"

EventDisplay::EventDisplay() // instead of a class it can be just a function
{

}

EventDisplay::EventDisplay(int i, const Config &_config, event_to_display _event)
{
	// just test
	TString name = Form("event_%d.png",i);
	canv = new TCanvas("canva");
	// scheme of the detector(s)
	// D1 - edge points
	D1_x[0] =-_config.D1_x_det_center;
	D1_x[1] = _config.D1_x_det_center;
	D1_x[2] = _config.D1_x_det_center;
	D1_x[3] =-_config.D1_x_det_center;
	D1_x[4] = D1_x[0];
	D1_z[0] =-_config.D1_z_det_center;
	D1_z[1] =-_config.D1_z_det_center;
	D1_z[2] = _config.D1_z_det_center;
	D1_z[3] = _config.D1_z_det_center;
	D1_z[4] = D1_z[0];
	//-sin(y_rotation_angle)*(Layer[0] -> RelativeXPosition.back()) + cos(y_rotation_angle)*(Layer[0] -> RelativeZPosition);;
	for (int i = 0; i < 5; i++)
	{
		D1_x_rotated[i] = _config.D1_x_offset + cos(_config.D1_y_rotation_angle)*D1_x[i] + sin(_config.D1_y_rotation_angle)*D1_z[i];
		D1_z_rotated[i] = _config.D1_z_offset - sin(_config.D1_y_rotation_angle)*D1_x[i] + cos(_config.D1_y_rotation_angle)*D1_z[i];;
	}

	if (_event.D1_event_to_display->XPositions.size() != 0)
	{
		D1_scheme = new TGraph(5,D1_x_rotated,D1_z_rotated);
		D1_scheme -> Draw("AL");
		graph = new TGraph(_event.D1_event_to_display->XPositions.size(), &_event.D1_event_to_display->XPositions.at(0), &_event.D1_event_to_display->ZPositions.at(0));
		graph -> Draw("same*");
		canv -> SaveAs(name);
		delete graph;
	}
	delete canv;
}

EventDisplay::~EventDisplay()
{

}


