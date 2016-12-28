#include "EventDisplay.h"

EventDisplay::EventDisplay() // instead of a class it can be just a function
{

}

EventDisplay::EventDisplay(int i, const Config &_config, event_to_display _event)
{
	// setting global range
	range_x_min = -110;
	range_x_max = 110;
	range_z_min = -190;
	range_z_max = 30;

	TString name = Form("event_%d",i);
	canv = new TCanvas(name,name,1000,1000);
	AllHits = new TMultiGraph();

	for (unsigned int i = 0; i < _event.DetectorPlots.size(); i++)//
	{
		_event.DetectorPlots.at(i)->GetXaxis()->SetLimits(range_x_min,range_x_max);
   		_event.DetectorPlots.at(i)->GetHistogram()->SetMinimum(range_z_min);
   		_event.DetectorPlots.at(i)->GetHistogram()->SetMaximum(range_z_max);
		if(0==i)
		{
			_event.DetectorPlots.at(i) -> Draw("AL");
			ReverseXAxis(_event.DetectorPlots.at(i));
		}
		else _event.DetectorPlots.at(i) -> Draw("L");
	}

	//std::cout << _event.HitsPlots.size() << std::endl;
	for (unsigned int i = 0; i < _event.HitsPlots.size(); i++)
	{
		_event.HitsPlots.at(i)->GetXaxis()->SetLimits(range_x_min,range_x_max);
   		_event.HitsPlots.at(i)->GetHistogram()->SetMinimum(range_z_min);
   		_event.HitsPlots.at(i)->GetHistogram()->SetMaximum(range_z_max);
   		_event.HitsPlots.at(i)-> Draw("P");
   		ReverseXAxis(_event.DetectorPlots.at(i));
	}

	_event.track->GetXaxis()->SetLimits(range_x_min,range_x_max);
   	_event.track->GetHistogram()->SetMinimum(range_z_min);
   	_event.track->GetHistogram()->SetMaximum(range_z_max);
   	_event.track-> Draw("L");
   	ReverseXAxis(_event.track);
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
	//newaxisY->SetLabelOffset(-0.03);
	//newaxisY->Draw();
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
                                range_z_min,
                                range_z_max,
                                510,"+");
	newaxisX->SetLabelOffset(-0.03);
	newaxisX->Draw();
	newaxisY->SetLabelOffset(-0.03);
	newaxisY->Draw();
}