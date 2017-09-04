#include "CalibrationLayer3d_HEX.h"

CalibrationLayer3d_HEX::CalibrationLayer3d_HEX()
{

}

CalibrationLayer3d_HEX::CalibrationLayer3d_HEX(int _layer_no, const std::vector<double> &_CalibTimes, const std::vector<double> &_CalibDistances)
{
	max_time_range = -1;
	no_of_corr_bins = -1;
	layer_no = _layer_no;
	// since now, Initial* should be kept just as a reference in order to plot the final result:)
	InitialDriftTimes = _CalibTimes;
	InitialDistances = _CalibDistances;
	DriftTimes = _CalibTimes;
	Distances = _CalibDistances;

	TString name;
	name = Form("wire_hit_layer_%d", _layer_no); 
	wire_hit_test = new TH1F(name, name, 100, -0.3, 1.2);
	name = Form("wire_track_layer_%d", _layer_no); 
	wire_track_test = new TH1F(name, name, 100, -0.3, 1.2);

	no_of_calib_bins = DriftTimes.size() - 1; // t1 bin1 t2 bin2 t3
	// vector of x errors is just needed for the tgrapherrors plot.
	for (int i = 0; i < DriftTimes.size(); i++) XErrors.push_back(0);
}

CalibrationLayer3d_HEX::~CalibrationLayer3d_HEX()
{

}

void CalibrationLayer3d_HEX::set_no_of_corr_bins(double _no_of_corr_bins)
{
	no_of_corr_bins = _no_of_corr_bins;
	if (-1!=max_time_range)
	{
		corr_bin_width = max_time_range/no_of_corr_bins;
		TString name;
		name = Form("layer%d #Delta", layer_no);
		delta = new TH2F(name, name, no_of_corr_bins, 0, max_time_range, 150, -0.3, 0.3);///350, -0.4, 0.4);
		delta->GetXaxis()->SetTitle("time [ns]");
		delta->GetYaxis()->SetTitle("delta [cm]");

		name = Form("layer%d #Delta cut", layer_no);
		delta_cut = new TH2F(name, name, no_of_corr_bins, 0, max_time_range, 150, -0.3, 0.3);///350, -0.4, 0.4);
		delta_cut->GetXaxis()->SetTitle("time [ns]");
		delta_cut->GetYaxis()->SetTitle("delta [cm]");
	}
}

void CalibrationLayer3d_HEX::set_max_time_range(double _max_time_range)
{
	max_time_range = _max_time_range;
	if (-1!=no_of_corr_bins)
	{
		calib_bin_width = max_time_range/no_of_calib_bins;
		corr_bin_width = max_time_range/no_of_corr_bins;
		TString name;
		name = Form("layer%d #Delta", layer_no);
		delta = new TH2F(name, name, no_of_corr_bins, 0, max_time_range, 150, -0.3, 0.3);///350, -0.4, 0.4);
		delta->GetXaxis()->SetTitle("time [ns]");
		delta->GetYaxis()->SetTitle("delta [cm]");

		name = Form("layer%d #Delta cut", layer_no);
		delta_cut = new TH2F(name, name, no_of_corr_bins, 0, max_time_range, 150, -0.3, 0.3);///350, -0.4, 0.4);
		delta_cut->GetXaxis()->SetTitle("time [ns]");
		delta_cut->GetYaxis()->SetTitle("delta [cm]");
	}
}

void CalibrationLayer3d_HEX::set_no_of_bin_in_event()
{
	double dtime;
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		dtime = CalibrationData.at(i).drift_time;
		for (int j = 0; j < no_of_calib_bins; j++)
		{
			if (dtime >= DriftTimes.at(j) && dtime < DriftTimes.at(j+1))
			{
				CalibrationData.at(i).calib_bin = j;
				break;
			}
		}

		for (int j = 0; j < no_of_corr_bins; j++)
		{
			if (dtime >= j*corr_bin_width && dtime < (j+1)*corr_bin_width)
			{
				CalibrationData.at(i).corr_bin = j;
				break;
			}
		}
	}
}

void CalibrationLayer3d_HEX::set_no_of_bin_in_calib()
{
	double dtime;
	for (unsigned int i = 0; i < DriftTimes.size(); i++)
	{
		dtime = DriftTimes.at(i);
		for (int j = 0; j < no_of_corr_bins; j++)
		{
			if (dtime >= j*corr_bin_width && dtime < (j+1)*corr_bin_width)
			{
				Bins.push_back(j);
				break;
			}
		}
	}
}

void CalibrationLayer3d_HEX::set_no_of_iteration(double _no_of_iteration)
{
	no_of_iteration = _no_of_iteration;
}

void CalibrationLayer3d_HEX::get_data(double _wire_pos_X, double _wire_pos_Z, double _drift_time, int _lr)
{
	HEX_single_event_data3d data;
	data.wire_pos_X = _wire_pos_X;
	data.wire_pos_Z = _wire_pos_Z;
	data.drift_time = _drift_time;
	data.left_right = _lr;
	CalibrationData.push_back(data);
}

// in a loop when everything is already set (lf ambiguity especially!)
void CalibrationLayer3d_HEX::calculate_hit_position()
{
	double wirex, wirez, lr, drifttime;
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		wirex = CalibrationData.at(i).wire_pos_X;
		wirez = CalibrationData.at(i).wire_pos_Z;
		lr = CalibrationData.at(i).left_right;
		drifttime = CalibrationData.at(i).drift_time;
		// pos in the lab
		if (layer_no==1||layer_no==4) CalibrationData.at(i).hit_pos_X = wirex+lr*drift_time_to_distance(CalibrationData.at(i).calib_bin, drifttime);//*pow(TMath::Cos(31*TMath::DegToRad()),-1);
		if (layer_no==2||layer_no==3||layer_no==5||layer_no==6) CalibrationData.at(i).hit_pos_X = wirex+lr*drift_time_to_distance(CalibrationData.at(i).calib_bin, drifttime)*pow(TMath::Cos(10*TMath::DegToRad()),-1);
		// distance wire hit = odległosc prostopadla do drutu!!
		CalibrationData.at(i).distance_wire_hit = drift_time_to_distance(CalibrationData.at(i).calib_bin, drifttime);
		CalibrationData.at(i).hit_pos_Z = wirez;
		//std::cout << "layer_no: " << layer_no << " wire: " << wirex << " x: " << CalibrationData.at(i).hit_pos_X << std::endl;
	}
}

double CalibrationLayer3d_HEX::drift_time_to_distance(int i, double drift_time) // i - calib bin
{
	double distance;
	int calib_bin = i;
	double t1 = DriftTimes.at(calib_bin);
	double t2 = DriftTimes.at(calib_bin+1);
	double x1 = Distances.at(calib_bin);
	double x2 = Distances.at(calib_bin+1);
	// linear approximation between t1 and t2: t1   x  t2
	distance = x1 + (x2 - x1)*(drift_time - t1)/(t2 - t1);
	return distance;
}

double CalibrationLayer3d_HEX::set_pos_Xerr()
{
	int corr_bin;
	double error;
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		corr_bin = CalibrationData.at(i).corr_bin;
//		if (no_of_iteration == 0) error = 1;
//		else
//		{
			if (ProjectionSigma.at(corr_bin) == 0.0) error = 1;
			else error = ProjectionSigma.at(corr_bin);
//		}
		CalibrationData.at(i).hit_pos_Xerr = error;
	}
}

void CalibrationLayer3d_HEX::fit_delta_projections(const char* folder_name)
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
	double hist_center, hist_sigma, hist_max_bin;
	int counter;
	for (int i = 0; i < no_of_corr_bins+1; i++) // there was no_of_corr_bins + 1, removed 22.11.16
	{
		delta_projection = delta -> ProjectionY("",i,i+1);
		no_of_entries_in_projection = delta_projection -> GetEntries();
		hist_center = delta_projection -> GetMean();
		hist_sigma = delta_projection -> GetRMS();
		delta_projection->GetXaxis()->SetRangeUser(hist_center - 0.5*hist_sigma,hist_center + 0.5*hist_sigma);
		hist_max_bin = delta_projection -> GetBinCenter(delta_projection -> GetMaximumBin());
		hist_center = hist_max_bin;	
		delta_projection->GetXaxis()->SetRangeUser(-0.4, 0.4);
//		if ( hist_max_bin > (hist_center - hist_sigma) && hist_max_bin < (hist_center + hist_sigma) )
//		{
//			hist_center = hist_max_bin;			
//		}
		ProjectionName = Form("projection_%d",i);
		c_delta_projection = new TCanvas(ProjectionName);
		gStyle->SetStatX(0.4);   
		gStyle->SetStatY(0.9);
		gStyle->SetStatW(0.15);
		gStyle->SetStatH(0.2);           
		ProjectionName = Form(folder_name + TString("projection_%d.png"),i);
		delta_projection -> Draw();
		if (no_of_entries_in_projection > 39)
		{

			if ( (i < 6 && no_of_iteration == 0) || i <= 2 )
			{
				counter = 0;
				for (int j = 0; j < delta_projection -> GetNbinsX(); j++)
				{
					if (delta_projection -> GetBinContent(j)>0)
					{
						counter = j;
						break;
					}
				}
				gaussian -> SetParameters(delta_projection -> GetMaximum(), 0, 0.3);
				delta_projection->Fit("gaussian","QEMI","", 0,hist_center+0.15);
			}
			else
			{
				gaussian -> SetParameters(delta_projection -> GetMaximum(), hist_center, 0.1);
				delta_projection->Fit("gaussian","WWQEMI","",hist_center-0.15,hist_center+0.15);//hist_center-hist_sigma,hist_center+hist_sigma);
			}
			ProjectionConstant.push_back(gaussian->GetParameter(0));
    		ProjectionMean.push_back(gaussian->GetParameter(1));
    		ProjectionSigma.push_back(gaussian->GetParameter(2));

    		gStyle->SetOptFit(1111);
			gPad->Modified();
		}
		else
		{
			ProjectionConstant.push_back(-1);
			ProjectionMean.push_back(-1);
			ProjectionSigma.push_back(0.0);
		}
		//if (no_of_iteration == 5 || no_of_iteration == 6) c_delta_projection -> SaveAs(ProjectionName);
		delete c_delta_projection;
	}
	delete gaussian;
}

void CalibrationLayer3d_HEX::apply_corrections()
{
	int corr_bin;
	for (unsigned int i = 0; i < no_of_calib_bins; i++)
	{
		corr_bin = Bins.at(i);
		if(-1!=ProjectionMean.at(corr_bin))
		{
			if (no_of_iteration!=5 && no_of_iteration!=6) Distances.at(i) = Distances.at(i) + ProjectionMean.at(corr_bin);
			else Distances.at(i) = Distances.at(i);
			SigmaForCalibration.push_back(ProjectionSigma.at(corr_bin));
		}
		else SigmaForCalibration.push_back(0);
		if (Distances.at(i) < 0) Distances.at(i) = 0;
	}
	SigmaForCalibration.push_back(0);
}

void CalibrationLayer3d_HEX::deletations()
{
	ProjectionConstant.clear();
	ProjectionSigma.clear();
	ProjectionMean.clear();
	SigmaForCalibration.clear();
	delta -> Reset();
	delta_cut -> Reset();
	wire_track_test -> Reset();
	wire_hit_test -> Reset();
}

TCanvas* CalibrationLayer3d_HEX::plot_delta()
{
	TString name;
	name = Form("c layer%d #Delta iteration %d",layer_no, no_of_iteration);
	gStyle->SetOptStat(0000000);		// tym mozna manipulowac przy rzutach (tylko tym?)
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.1);
	gStyle->SetStatY(0.9);
	TCanvas *c = new TCanvas(name,name);
	gStyle -> SetOptStat(1111111);
	gPad -> SetLogz();
	delta -> Draw("colz");

	name = Form("c layer%d wire-track iteration %d",layer_no, no_of_iteration);
	TCanvas *c2 = new TCanvas(name,name);
	wire_track_test->Draw();
	name = Form("results/layer%d_wire-track_iteration_%d.png",layer_no, no_of_iteration);
	c2 -> SaveAs(name);

	name = Form("c layer%d wire-hit iteration %d",layer_no, no_of_iteration);
	TCanvas *c3 = new TCanvas(name,name);
	wire_hit_test->Draw();
	name = Form("results/layer%d_wire-hit_iteration_%d.png",layer_no, no_of_iteration);
	c3 -> SaveAs(name);
	
	return c;
}

TCanvas* CalibrationLayer3d_HEX::plot_delta_cut()
{
	TString name;
	name = Form("c layer%d #Delta cut iteration %d",layer_no, no_of_iteration);
	gStyle->SetOptStat(0000000);		// tym mozna manipulowac przy rzutach (tylko tym?)
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.1);
	gStyle->SetStatY(0.9);
	TCanvas *c = new TCanvas(name,name);
	gStyle -> SetOptStat(1111111);
	gPad -> SetLogz();
	delta_cut -> Draw("colz");
	return c;
}

TCanvas* CalibrationLayer3d_HEX::plot_current_calibration()
{
//	std::cout << "CALIBRATION" << std::endl;
//	for (int i = 0; i < DriftTimes.size(); i++)
//	{
//		std::cout << DriftTimes.at(i) << " " << Distances.at(i) << std::endl;
//	}

	TString name;
	// save calibration as a txt file. move to separate method
//	name = Form("results/layer%d_calibration_iteration_%d.txt", layer_no, no_of_iteration);
//	ofstream calibdata;
//	calibdata.open(name);
//	for (int i = 0; i < DriftTimes.size()-1; i++)
//	{
//		calibdata << DriftTimes.at(i) << " " << Distances.at(i) << " " << XErrors.at(i) << " " << SigmaForCalibration.at(i) << std::endl;
//	}
//
//	calibdata.close();

	name = Form("c layer%d current calibration iteration %d", layer_no, no_of_iteration);
	//TGraph* current_calibration;
	TGraphErrors* current_calibration;
	TGraph* initial_calibration;
	current_calibration = new TGraphErrors(DriftTimes.size(), &DriftTimes.at(0), &Distances.at(0), &XErrors.at(0), &SigmaForCalibration.at(0));
	name = Form("current-calib-layer-%d-iteration-%d", layer_no, no_of_iteration);
	current_calibration -> SetLineColor(kRed);
	current_calibration -> SetMarkerColor(kRed);
	current_calibration -> SetMarkerStyle(6);
	current_calibration -> SetLineWidth(1);
	initial_calibration = new TGraph(InitialDriftTimes.size(), &InitialDriftTimes.at(0), &InitialDistances.at(0));
	name = Form("init_calib-layer-%d-iteration-%d", layer_no, no_of_iteration);
	initial_calibration -> SetName(name);
	initial_calibration -> SetLineColor(kBlue);
	initial_calibration -> SetLineWidth(3);
	initial_calibration -> SetMinimum(0);
   	initial_calibration -> SetMaximum(2.5);
   	initial_calibration -> GetXaxis()->SetTitle("drift time [ns]");
	initial_calibration -> GetYaxis()->SetTitle("distance [cm]");
	TCanvas *c_current_calibration = new TCanvas(name,name);
	initial_calibration -> Draw("AL");
	current_calibration -> Draw("sameP");
	if (no_of_iteration==0)
	{
		gDirectory->pwd();
		initial_calibration -> Write();
	}
	if (no_of_iteration == 9)
	{
		gDirectory->pwd();
		c_current_calibration -> Write();
		current_calibration -> Write();

	}
	
	return c_current_calibration;
}

TCanvas* CalibrationLayer3d_HEX::plot_corrections()
{
	TString name;
	name = Form("c layer%d current corrections iteration %d", layer_no, no_of_iteration);
	TGraphErrors* corrections_plot;
	corrections_plot = new TGraphErrors(DriftTimes.size(), &DriftTimes.at(0), &ProjectionMean.at(0), &XErrors.at(0), &SigmaForCalibration.at(0));
	corrections_plot->SetMinimum(-0.12);
   	corrections_plot->SetMaximum(0.12);
   	corrections_plot->GetXaxis()->SetTitle("drift time [ns]");
	corrections_plot->GetYaxis()->SetTitle("positions [cm]");
	TCanvas *c_corrections_plot = new TCanvas(name,name);
	corrections_plot -> Draw("AP");
	return c_corrections_plot;
}

void CalibrationLayer3d_HEX::calculate_deltas(int i)
{
	double x_wire;
	double wire_track, wire_hit;

	x_wire = CalibrationData.at(i).wire_pos_X;
	wire_track = CalibrationData.at(i).distance_wire_track;
	//std::cout << "x_wire " << x_wire << std::endl;
	//std::cout << "wire_track " << wire_track << std::endl;
	wire_hit = CalibrationData.at(i).distance_wire_hit;
	double delta_val;
	//std::cout << CalibrationData.at(i).distance_wire_track << std::endl;
	//std::cout << CalibrationData.at(i).distance_wire_hit << std::endl;
	//std::cout << "wire_track: " << wire_track << " " << "wire_hit: " << wire_hit << std::endl;
	if (fabs(wire_hit) < fabs(wire_track)) delta_val = fabs(wire_track - wire_hit);
	if (fabs(wire_hit) > fabs(wire_track)) delta_val = -fabs(wire_track - wire_hit);
	wire_hit_test -> Fill(wire_hit);
	wire_track_test -> Fill(wire_track);
	CalibrationData.at(i).delta = delta_val;

	if (1) // change
	{
		delta -> Fill(CalibrationData.at(i).drift_time, delta_val);
	}
}

/*void CalibrationLayer3d_HEX::save_in_root_file(TH2F *_c)
{
	TFile f3("results/calibration_results.root","UPDATE");
	TH2F *c = new TH2F();
	c = _c;
	c -> Draw();
	f3.Close();
}

void CalibrationLayer3d_HEX::save_in_root_file(TGraph *_c)
{
	TFile f3("results/calibration_results.root","UPDATE");
	TGraph *c = new TGraph();
	c = _c;
	c -> Draw();
	f3.Close();
}

void CalibrationLayer3d_HEX::save_in_root_file(TH1F *_c)
{
	TFile f3("results/calibration_results.root","UPDATE");
	TH1F *c = new TH1F();
	c = _c;
	c -> Draw();
	f3.Close();
}*/

