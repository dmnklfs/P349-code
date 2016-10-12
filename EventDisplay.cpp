#include "EventDisplay.h"

EventDisplay::EventDisplay() // instead of a class it can be just a function
{

}

EventDisplay::EventDisplay(int i, const Config &_config, event_to_display _event)
{
	// setting global range
	range_x_min = -110;
	range_x_max = 110;
	range_z_min = 80;
	range_z_max = 300;

	TString name = Form("event_%d",i);
	canv = new TCanvas(name,name,1500,1500);
	AllHits = new TMultiGraph();

	for (unsigned int i = 0; i < _event.HitsPlots.size(); i++)
	{
		AllHits -> Add(_event.HitsPlots.at(i));
	}

	for (unsigned int i = 0; i < _event.DetectorPlots.size(); i++)
	{
		_event.DetectorPlots.at(i) -> Draw("AL");
		_event.DetectorPlots.at(i)->GetXaxis()->SetLimits(range_x_min,range_x_max);
   		_event.DetectorPlots.at(i)->SetMinimum(range_z_min);
   		_event.DetectorPlots.at(i)->SetMaximum(range_z_max);
   		ReverseXAxis(_event.DetectorPlots.at(i));
	}
	AllHits-> Draw("P");
}

EventDisplay::~EventDisplay()
{

}

TCanvas* EventDisplay::get_canvas()
{
	return canv;
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

void EventDisplay::ReverseXAxis(TGraph *h)
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