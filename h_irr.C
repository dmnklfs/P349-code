#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TChain.h" 
#include "TROOT.h" 
#include "TCanvas.h"
#include "TStopwatch.h" 
#include "TMath.h"
#include <cstdlib>
#include <iostream>
#include "TLine.h"

void h_irr()
{
	// open file
	TFile *f;
	f = (TFile*)gROOT->GetListOfFiles()->FindObject("results/data_calibration_attempt.root");
	if (!f) {
		f = new TFile("results/data_calibration_attempt.root");
	}

	TH1F* drift_hist[4][42];
	TH1F* sum[4];
	TCanvas* canvas[4];
	TString temp_name;
	double single_offset;

	int layer_no[4];
	layer_no[0] = 0;
	layer_no[1] = 1;
	layer_no[2] = 6;
	layer_no[3] = 7;

	TString name;
	for (int j = 0; j < 4; j++) // layers
	{
		name = Form("Layer_%d",j);
		sum[j] = new TH1F(name, name, 400, -400, 800);
		for (int i = 0; i < 42; i++) // wires
		{
			// input spectrum
			temp_name = Form("Preselected/D1DriftTimes/D1DriftTimeL%dW%d;1", layer_no[j]+1,i+1);
			drift_hist[j][i] = (TH1F*)f->Get(temp_name);
			sum[j] -> Add(drift_hist[j][i]);
   		} // endof wires
	} // endof layers


	double s_constant = 2;
	double c_constant;
	double step_width = 3.0; // ns
	double no_of_entries[250];
	double time[250];
	double distance[250];
	double bin_center;
	TGraph *calib[4];
	TCanvas *calib_c[4];
	ofstream calibdata;
	for (int i = 0; i < 4; i++)
	{
		// for results
		name = Form("results/layer%d_calibration.txt", i+1);
		calibdata.open(name);

		name = Form("Layer_%d",i);
		canvas[i] = new TCanvas(name, name);
		sum[i] -> Draw();
		name = Form("results/Layer_%d.png",i);
		canvas[i] -> SaveAs(name);

		// calibration
		c_constant = (sum[i] -> GetEntries())*pow(2,-1);
		for (int k = 0; k < 250; k++)
		{
			no_of_entries[k] = 0;
			time[k] = k*step_width;
			for (int j = 0; j < 400; j++)
			{
				bin_center = sum[i] -> GetBinCenter(j);
				if (bin_center < k*step_width)
				{
					no_of_entries[k] = no_of_entries[k] + sum[i] -> GetBinContent(j);
				}
			}
			//cout << no_of_entries[i] << endl;
			distance[k] = no_of_entries[k]*pow(c_constant,-1);
			if (time[k] <= 609)
			{
				calibdata << " " << distance[k] << ", ";
			}
		}
		calibdata.close();
		calib[i] = new TGraph(250, time, distance);
		calib[i] -> SetMarkerStyle(7);
		name = Form("c_Layer_%d.png",i);
		calib_c[i] = new TCanvas(name,name);
		calib[i] -> Draw("AP");
		name = Form("results/Layer_%d_calibration_c.png",i);
		calib_c[i] -> SaveAs(name);
	}
}



//TString name;
//	name = Form("results/layer%d_calibration_iteration_%d.txt", layer_no, no_of_iteration);
//	ofstream calibdata;
//	calibdata.open(name);
//	for (int i = 0; i < DriftTimes.size()-1; i++)
//	{
//		calibdata << DriftTimes.at(i) << " " << Distances.at(i) << " " << XErrors.at(i) << " " << ProjectionSigma.at(i) << std::endl;
//	}
//
//	calibdata.close();