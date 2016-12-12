#include <iostream>
#include <fstream>
#include <TGraphErrors.h>

void layers () {

	fstream myfile;
	std::vector<double> xx1;
	std::vector<double> errxx1;
	std::vector<double> yy1;
	std::vector<double> erryy1;
	std::vector<double> xx2;
	std::vector<double> errxx2;
	std::vector<double> yy2;
	std::vector<double> erryy2;
	std::vector<double> xx3;
	std::vector<double> errxx3;
	std::vector<double> yy3;
	std::vector<double> erryy3;
	std::vector<double> xx4;
	std::vector<double> errxx4;
	std::vector<double> yy4;
	std::vector<double> erryy4;
	double x, y, errx, erry;
	ifstream myReadFile;
	myReadFile.open("/home/dominika/Pulpit/20161212/dat_linear/layer8_calibration_iteration_1.txt");
	if (myReadFile.is_open())
	{
		while (!myReadFile.eof())
		{
			myReadFile >> x >> y >> errx >> erry;
			xx1.push_back(x);
			yy1.push_back(y);
			errxx1.push_back(errx);
			erryy1.push_back(erry);
		}
	}
	myReadFile.close();
	myReadFile.open("/home/dominika/Pulpit/20161212/dat_garfield/layer8_calibration_iteration_1.txt");
	if (myReadFile.is_open())
	{
		while (!myReadFile.eof())
		{
			myReadFile >> x >> y >> errx >> erry;
			xx2.push_back(x);
			yy2.push_back(y);
			errxx2.push_back(errx);
			erryy2.push_back(erry);
		}
	}
	myReadFile.close();

	ifstream myReadFile;
	myReadFile.open("/home/dominika/Pulpit/20161212/dat_homogenous_irr/layer8_calibration_iteration_1.txt");
	if (myReadFile.is_open())
	{
		while (!myReadFile.eof())
		{
			myReadFile >> x >> y >> errx >> erry;
			xx3.push_back(x);
			yy3.push_back(y);
			errxx3.push_back(errx);
			erryy3.push_back(erry);
		}
	}

	TGraphErrors *ggraph1 = new TGraphErrors(xx1.size(), &xx1.at(0), &yy1.at(0), &errxx1.at(0), &erryy1.at(0));
	ggraph1 -> SetName("linear");
	ggraph1 -> SetTitle("linear");
	ggraph1 -> GetXaxis() -> SetTitle("drift time [ns]");
	ggraph1 -> GetYaxis() -> SetTitle("distance [cm]");
	ggraph1 -> SetLineColor(kRed);
	ggraph1 -> SetMarkerColor(kRed);
	ggraph1 -> SetMarkerStyle(7);
	TGraphErrors *ggraph2 = new TGraphErrors(xx2.size(), &xx2.at(0), &yy2.at(0), &errxx2.at(0), &erryy2.at(0));
	ggraph2 -> SetName("garfield");
	ggraph2 -> SetTitle("garfield");
	ggraph2 -> SetLineColor(kBlue);
	ggraph2 -> SetMarkerColor(kBlue);
	ggraph2 -> SetMarkerStyle(7);
	TGraphErrors *ggraph3 = new TGraphErrors(xx3.size(), &xx3.at(0), &yy3.at(0), &errxx3.at(0), &erryy3.at(0));
	ggraph3 -> SetName("h irr");
	ggraph3 -> SetTitle("h irr");
	ggraph3 -> SetLineColor(kGreen);
	ggraph3 -> SetMarkerColor(kGreen);
	ggraph3 -> SetMarkerStyle(7);

	gStyle->SetOptFit(1111111);
	ggraph1->Draw("AP");
	ggraph2->Draw("sameP");
	ggraph3->Draw("sameP");
	gPad -> BuildLegend();
}