#include "CalibrationLayer.h"

CalibrationLayer::CalibrationLayer()
{

}

CalibrationLayer::CalibrationLayer(int _layer_no, const std::vector<double> &_CalibTimes, const std::vector<double> &_CalibDistances)
{
	max_time_range = -1;
	no_of_corr_bins = -1;
	layer_no = _layer_no;
	// since now, Initial* should be kept just as a reference in order to plot the final result:)
	InitialDriftTimes = _CalibTimes;
	InitialDistances = _CalibDistances;
	DriftTimes = _CalibTimes;
	Distances = _CalibDistances;

	no_of_calib_bins = DriftTimes.size() - 1; // t1 bin1 t2 bin2 t3

	TString name;
	name = Form("layer%d #chi^{2}",layer_no);
	chi2 = new TH1F(name, name, 400, -1, 5);
	chi2->GetXaxis()->SetTitle("#chi^{2}");
	chi2->GetYaxis()->SetTitle("counts");
	chi2->SetLineWidth(2);
	chi2->SetLineColor(kBlue);

	name = Form("layer%d #chi^{2} cut", layer_no);
	chi2_cut = new TH1F(name, name, 400, -1, 5);
	chi2_cut->GetXaxis()->SetTitle("#chi^{2}");
	chi2_cut->GetYaxis()->SetTitle("counts");
	chi2_cut->SetLineColor(kRed);

	name = Form("layer%d #Delta", layer_no);
	delta = new TH2F(name, name, no_of_corr_bins, 0, 610, 300, -2.0, 2.0);
	delta->GetXaxis()->SetTitle("time [ns]");
	delta->GetYaxis()->SetTitle("delta [cm]");

	name = Form("layer%d #Delta cut", layer_no);
	delta_cut = new TH2F(name, name, no_of_corr_bins, 0, 610, 300, -2.0, 2.0);
	delta_cut->GetXaxis()->SetTitle("time [ns]");
	delta_cut->GetYaxis()->SetTitle("delta [cm]");
}

CalibrationLayer::~CalibrationLayer()
{

}

void CalibrationLayer::set_no_of_corr_bins(double _no_of_corr_bins)
{
	no_of_corr_bins = _no_of_corr_bins;
	if (-1!=max_time_range)
	{
		corr_bin_width = max_time_range/no_of_corr_bins;
	}
}

void CalibrationLayer::set_max_time_range(double _max_time_range)
{
	max_time_range = _max_time_range;
	if (-1!=no_of_corr_bins)
	{
		calib_bin_width = max_time_range/no_of_calib_bins;
		corr_bin_width = max_time_range/no_of_corr_bins;
	}
}

void CalibrationLayer::get_data(double _wire_pos_X, double _wire_pos_Z, double _drift_time, int _lr)
{
	D1_single_event_data data;
	data.wire_pos_X = _wire_pos_X;
	data.wire_pos_Z = _wire_pos_Z;
	data.drift_time = _drift_time;
	data.calib_bin = floor(data.drift_time/calib_bin_width);
	data.corr_bin = floor(data.drift_time/corr_bin_width);
	data.left_right = _lr;
	CalibrationData.push_back(data);
}

// in a loop when everything is already set (lf ambiguity especially!)
void CalibrationLayer::calculate_hit_position()
{
	double wirex, wirez, lr, drifttime;
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		wirex = CalibrationData.at(i).wire_pos_X;
		wirez = CalibrationData.at(i).wire_pos_Z;
		lr = CalibrationData.at(i).left_right;
		drifttime = CalibrationData.at(i).drift_time;
		CalibrationData.at(i).hit_pos_X = wirex+lr*drift_time_to_distance(drifttime);
		CalibrationData.at(i).hit_pos_Z = wirez;
	}
}

double CalibrationLayer::drift_time_to_distance(double drift_time)
{
	double distance;
	int calib_bin = floor(drift_time/calib_bin_width);
	double t1 = DriftTimes.at(calib_bin);
	double t2 = DriftTimes.at(calib_bin+1);
	double x1 = Distances.at(calib_bin);
	double x2 = Distances.at(calib_bin+1);
	// linear approximation between t1 and t2: t1   x  t2
	distance = Distances.at(calib_bin) + (x2 - x1)*(drift_time - t1)/(t2 - t1);
	return distance;
}

void CalibrationLayer::fit_delta_projections(const char* folder_name)
{
	ProjectionConstant.clear();
	ProjectionMean.clear();
	ProjectionSigma.clear();
	// create directory for results
	boost::filesystem::create_directories(folder_name);
	TString ProjectionName;
	TH1D *delta_projection;
	int no_of_entries_in_projection;
	TCanvas *c_delta_projection;
	TF1 *gaussian = new TF1("gaussian","gaus", -1.5, 1.5);
	double hist_center, hist_sigma;
	for (int i = 0; i < no_of_corr_bins; i++) // there was no_of_corr_bins + 1, removed 22.11.16
	{
		delta_projection = delta_cut -> ProjectionY("",i,i+1);
		no_of_entries_in_projection = delta_projection -> GetEntries();
		hist_center = delta_projection -> GetMean();
		hist_sigma = delta_projection -> GetRMS();

		ProjectionName = Form("projection_%d",i);
		c_delta_projection = new TCanvas(ProjectionName);
		gStyle->SetStatW(0.15);
		gStyle->SetStatH(0.1);
		gStyle->SetStatX(0.4);   
		gStyle->SetStatY(0.9);             
		ProjectionName = Form(folder_name + TString("projection_%d.png"),i);
		delta_projection -> Draw();
		if (no_of_entries_in_projection > 10)
		{
			gaussian -> SetParameters(delta_projection -> GetMaximum(), 0, 0.1);
			delta_projection->Fit("gaussian","","",hist_center-hist_sigma,hist_center+hist_sigma);
			ProjectionConstant.push_back(gaussian->GetParameter(0));
    		ProjectionMean.push_back(gaussian->GetParameter(1));
    		ProjectionSigma.push_back(0.5*gaussian->GetParameter(2));

    		gStyle->SetOptFit(1111);
			gPad->Modified();
		}
		else
		{
			ProjectionConstant.push_back(-1);
			ProjectionMean.push_back(-1);
			ProjectionSigma.push_back(-1);
		}
		c_delta_projection -> SaveAs(ProjectionName);
		delete c_delta_projection;
	}
	delete gaussian;
}

void CalibrationLayer::apply_corrections()
{
	//if (Distances.size()!=ProjectionMean.size()) std::cout << "ERROR in SimpleCalibration::apply_corrections(): incorrect sizes!!!" << std::endl;
	int calib_bin;
	for (unsigned int i = 0; i < Distances.size(); i++)
	{
		calib_bin = floor(DriftTimes.at(i)/corr_bin_width);
		if(-1!=ProjectionMean.at(calib_bin)) Distances.at(i) = Distances.at(i) + ProjectionMean.at(calib_bin);
		if (Distances.at(i) < 0) Distances.at(i) = 0;
	}
}

void CalibrationLayer::deletations()
{
	ProjectionConstant.clear();
	ProjectionSigma.clear();
	ProjectionMean.clear();
	chi2 -> Reset();
	chi2_cut -> Reset();
	delta -> Reset();
	delta_cut -> Reset();
}

void CalibrationLayer::recalculate_positions()
{
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		CalibrationData.at(i).hit_pos_X = CalibrationData.at(i).wire_pos_X+(CalibrationData.at(i).left_right)*drift_time_to_distance(CalibrationData.at(i).drift_time);
	}
}

void CalibrationLayer::fill_chi2(double _chi2_cut)
{
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		if (-1!=CalibrationData.at(i).chi2)
		{
			chi2 -> Fill(CalibrationData.at(i).chi2);
			if (CalibrationData.at(i).chi2 < _chi2_cut) chi2_cut -> Fill(CalibrationData.at(i).chi2);
		}
	}
}

void CalibrationLayer::fill_delta(double _chi2_cut)
{
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		if (-1!=CalibrationData.at(i).delta)
		{
			delta -> Fill(CalibrationData.at(i).drift_time, CalibrationData.at(i).delta);
			if (CalibrationData.at(i).chi2 < _chi2_cut) delta_cut -> Fill(CalibrationData.at(i).drift_time, CalibrationData.at(i).delta);
		}
	}
}

TCanvas* CalibrationLayer::plot_chi2()
{
	TString name;
	name = Form("c layer%d #chi^{2}",layer_no);
	TCanvas *c = new TCanvas(name,name);
	gStyle -> SetOptStat(1111111);
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	chi2 -> Draw();
	chi2_cut -> Draw("same");
	return c;
}

TCanvas* CalibrationLayer::plot_delta()
{
	TString name;
	name = Form("c layer%d #Delta",layer_no);
	gStyle->SetOptStat(0000000);		// tym mozna manipulowac przy rzutach (tylko tym?)
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	TCanvas *c = new TCanvas(name,name);
	gStyle -> SetOptStat(1111111);
	gPad -> SetLogz();
	delta -> Draw("colz");
	return c;
}

TCanvas* CalibrationLayer::plot_delta_cut()
{
	TString name;
	name = Form("c layer%d #Delta cut",layer_no);
	gStyle->SetOptStat(0000000);		// tym mozna manipulowac przy rzutach (tylko tym?)
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	TCanvas *c = new TCanvas(name,name);
	gStyle -> SetOptStat(1111111);
	gPad -> SetLogz();
	delta_cut -> Draw("colz");
	return c;
}

TCanvas* CalibrationLayer::plot_current_calibration()
{
	TString name;
	name = Form("c layer%d current calibration",layer_no);
	TGraph* current_calibration;
	TGraph* initial_calibration;
	current_calibration = new TGraph(DriftTimes.size(), &DriftTimes.at(0), &Distances.at(0));
	current_calibration -> SetLineColor(kRed);
	initial_calibration = new TGraph(InitialDriftTimes.size(), &InitialDriftTimes.at(0), &InitialDistances.at(0));
	initial_calibration -> SetLineColor(kBlue);
	TCanvas *c_current_calibration = new TCanvas(name,name);
	current_calibration -> Draw("AL");
   	current_calibration->SetMinimum(0);
   	current_calibration->SetMaximum(2.5);
   	initial_calibration -> Draw("same");
	return c_current_calibration;
}

void CalibrationLayer::calculate_deltas()
{
	double x, z, a, b, x_wire;
	double wire_track, wire_hit;
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		a = CalibrationData.at(i).track_a;
		b = CalibrationData.at(i).track_b;
		x = CalibrationData.at(i).hit_pos_X;
		z = CalibrationData.at(i).hit_pos_Z;
		x_wire = CalibrationData.at(i).wire_pos_X;
		wire_track = fabs((z - b)/a - x_wire);
		wire_hit = fabs( x - x_wire);
		if (fabs(wire_hit) < fabs(wire_track)) CalibrationData.at(i).delta = fabs(wire_track - wire_hit);
		if (fabs(wire_hit) > fabs(wire_track)) CalibrationData.at(i).delta = -fabs(wire_track - wire_hit);
	}
}
