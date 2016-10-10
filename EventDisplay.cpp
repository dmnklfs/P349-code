#include "EventDisplay.h"

EventDisplay::EventDisplay() // instead of a class it can be just a function
{

}

EventDisplay::EventDisplay(int i, const Config &_config, event_to_display _event)
{
	draw = false; // in the end -> some condition in main which provides drawing of these files

	// setting global range
	range_x_min = -110;
	range_x_max = 110;
	range_z_min = 80;
	range_z_max = 300;

	TString name = Form("event_%d.png",i);
	canv = new TCanvas("canva","canva",1500,1500);
	AllHits = new TMultiGraph();

	// reading the informations about the detector
	// D1 - edge points
	D1_x[0] =(-_config.D1_half_x_dim);
	D1_x[1] =( _config.D1_half_x_dim);
	D1_x[2] =( _config.D1_half_x_dim);
	D1_x[3] =(-_config.D1_half_x_dim);
	D1_x[4] =( D1_x[0]);
	D1_z[0] =(-_config.D1_half_z_dim);
	D1_z[1] =(-_config.D1_half_z_dim);
	D1_z[2] =( _config.D1_half_z_dim);
	D1_z[3] =( _config.D1_half_z_dim);
	D1_z[4] =( D1_z[0]);
	// D1 offsets
	D1_x_offset = _config.D1_x_offset;
	D1_z_offset = _config.D1_z_offset;
	// rotation angle
	D1_y_rotation_angle = _config.D1_y_rotation_angle;

	// rotation
	for (int i = 0; i < 5; i++)
	{
		D1_x_rotated[i] = -(D1_x_offset + get_x_after_rot_Y(D1_x[i], D1_z[i], D1_y_rotation_angle));
		D1_z_rotated[i] = D1_z_offset + get_z_after_rot_Y(D1_x[i], D1_z[i], D1_y_rotation_angle);
	}


	// graphs for the display
	D1_scheme = new TGraph(5,D1_x_rotated,D1_z_rotated);
	D1_scheme ->SetLineColor(4);
	D1_scheme ->SetLineWidth(4);
	D1_scheme ->SetFillStyle(0);
	AllHits -> Add(D1_scheme);

	if (_event.D1_event_to_display->XPositions.size() != 0)
	{
		D1_scheme = new TGraph(_event.D1_event_to_display->XPositions.size(), &_event.D1_event_to_display->XPositions.at(0), &_event.D1_event_to_display->ZPositions.at(0));
		D1_scheme->SetMarkerStyle(20);
	}


	// drawing of all detectors
	if (_event.D1_event_to_display->XPositions.size() != 0)
	{
		draw = true;
	}

	if (draw)
	{
		AllHits -> Draw("AL");
		
		AllHits->GetXaxis()->SetLimits(range_x_min,range_x_max);
   		AllHits->SetMinimum(range_z_min);
   		AllHits->SetMaximum(range_z_max);
   		ReverseXAxis(AllHits);

   		D1_scheme -> Draw("P");
   		
   		//canv->BuildLegend();
   		canv->Modified();
		canv->Update();

		canv -> SaveAs(name);
		delete canv;
	}
}

EventDisplay::~EventDisplay()
{

}

void EventDisplay::ReverseXAxis(TMultiGraph *h)
{
	// Remove the current axis
	h->GetXaxis()->SetLabelOffset(999);
	h->GetXaxis()->SetTickLength(0);
	h->GetYaxis()->SetLabelOffset(999);
	h->GetYaxis()->SetTickLength(0);
	// Redraw the new axis
	gPad->Update();
	TGaxis *newaxisX = new TGaxis(gPad->GetUxmax(),
	                             gPad->GetUymin(),
	                             gPad->GetUxmin(),
	                             gPad->GetUymin(),
	                             h->GetXaxis()->GetXmin(),
	                             h->GetXaxis()->GetXmax(),
	                             510,"-");
	TGaxis *newaxisY = new TGaxis(gPad->GetUxmin(),
                                gPad->GetUymin(),
                                gPad->GetUxmin(),
                                gPad->GetUymax(),
                                h->GetYaxis()->GetXmin(),
                                h->GetYaxis()->GetXmax(),
                                510,"+");
	newaxisX->SetLabelOffset(-0.03);
	newaxisX->Draw();
	newaxisY->SetLabelOffset(-0.03);
	newaxisY->Draw();
}