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
		TString name;
		name = Form("layer%d #Delta", layer_no);
		delta = new TH2F(name, name, no_of_corr_bins, 0, max_time_range, 300, -2.0, 2.0);
		delta->GetXaxis()->SetTitle("time [ns]");
		delta->GetYaxis()->SetTitle("delta [cm]");

		name = Form("layer%d #Delta cut", layer_no);
		delta_cut = new TH2F(name, name, no_of_corr_bins, 0, max_time_range, 300, -2.0, 2.0);
		delta_cut->GetXaxis()->SetTitle("time [ns]");
		delta_cut->GetYaxis()->SetTitle("delta [cm]");
	}
}

void CalibrationLayer::set_max_time_range(double _max_time_range)
{
	max_time_range = _max_time_range;
	if (-1!=no_of_corr_bins)
	{
		calib_bin_width = max_time_range/no_of_calib_bins;
		corr_bin_width = max_time_range/no_of_corr_bins;
		TString name;
		name = Form("layer%d #Delta", layer_no);
		delta = new TH2F(name, name, no_of_corr_bins, 0, max_time_range, 300, -2.0, 2.0);
		delta->GetXaxis()->SetTitle("time [ns]");
		delta->GetYaxis()->SetTitle("delta [cm]");

		name = Form("layer%d #Delta cut", layer_no);
		delta_cut = new TH2F(name, name, no_of_corr_bins, 0, max_time_range, 300, -2.0, 2.0);
		delta_cut->GetXaxis()->SetTitle("time [ns]");
		delta_cut->GetYaxis()->SetTitle("delta [cm]");
	}
}

void CalibrationLayer::set_no_of_bin_in_event()
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

void CalibrationLayer::set_no_of_bin_in_calib()
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

void CalibrationLayer::set_no_of_iteration(double _no_of_iteration)
{
	no_of_iteration = _no_of_iteration;
}

void CalibrationLayer::get_data(double _wire_pos_X, double _wire_pos_Z, double _drift_time, int _lr)
{
	D1_single_event_data data;
	data.wire_pos_X = _wire_pos_X;
	data.wire_pos_Z = _wire_pos_Z;
	data.drift_time = _drift_time;
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
		CalibrationData.at(i).hit_pos_X = wirex+lr*drift_time_to_distance(CalibrationData.at(i).calib_bin, drifttime);
		CalibrationData.at(i).hit_pos_Z = wirez;
	}
}

double CalibrationLayer::drift_time_to_distance(int i, double drift_time) // i - calib bin
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
	double hist_center, hist_sigma, hist_max_bin;
	for (int i = 0; i < no_of_corr_bins+1; i++) // there was no_of_corr_bins + 1, removed 22.11.16
	{
		delta_projection = delta -> ProjectionY("",i,i+1);
		no_of_entries_in_projection = delta_projection -> GetEntries();
		hist_center = delta_projection -> GetMean();
		hist_sigma = delta_projection -> GetRMS();
		delta_projection->GetXaxis()->SetRangeUser(hist_center - 0.5*hist_sigma,hist_center + 0.5*hist_sigma);
		hist_max_bin = delta_projection -> GetBinCenter(delta_projection -> GetMaximumBin());
		hist_center = hist_max_bin;	
		delta_projection->GetXaxis()->SetRangeUser(-1.5,1.5);
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
		if (no_of_entries_in_projection > 10)
		{
			gaussian -> SetParameters(delta_projection -> GetMaximum(), hist_center, 0.1);
			delta_projection->Fit("gaussian","WWQEMI","",hist_center-0.15,hist_center+0.15);//hist_center-hist_sigma,hist_center+hist_sigma);
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
	int corr_bin;
	for (unsigned int i = 0; i < no_of_corr_bins; i++)
	{
		corr_bin = Bins.at(i);
		if(-1!=ProjectionMean.at(corr_bin)) Distances.at(i) = Distances.at(i) + ProjectionMean.at(corr_bin);
		if (Distances.at(i) < 0) Distances.at(i) = 0;
	}
}

void CalibrationLayer::deletations()
{
	ProjectionConstant.clear();
	ProjectionSigma.clear();
	ProjectionMean.clear();
	delta -> Reset();
	delta_cut -> Reset();
}

TCanvas* CalibrationLayer::plot_delta()
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
	return c;
}

TCanvas* CalibrationLayer::plot_delta_cut()
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

TCanvas* CalibrationLayer::plot_current_calibration()
{
	std::cout << "CALIBRATION" << std::endl;
	for (int i = 0; i < DriftTimes.size(); i++)
	{
		std::cout << DriftTimes.at(i) << " " << Distances.at(i) << std::endl;
	}

	TString name;
	name = Form("c layer%d current calibration iteration %d", layer_no, no_of_iteration);
	TGraph* current_calibration;
	TGraph* initial_calibration;
	current_calibration = new TGraph(DriftTimes.size(), &DriftTimes.at(0), &Distances.at(0));
	current_calibration -> SetLineColor(kRed);
	current_calibration -> SetMarkerColor(kRed);
	current_calibration -> SetMarkerStyle(7);
	current_calibration -> SetLineWidth(3);
	initial_calibration = new TGraph(InitialDriftTimes.size(), &InitialDriftTimes.at(0), &InitialDistances.at(0));
	initial_calibration -> SetLineColor(kBlue);
	TCanvas *c_current_calibration = new TCanvas(name,name);
	current_calibration -> Draw("AP");
   	current_calibration->SetMinimum(0);
   	current_calibration->SetMaximum(2.5);
   	initial_calibration -> Draw("same");
	return c_current_calibration;
}

void CalibrationLayer::calculate_deltas(int i)
{
	double x, z, a, b, x_wire;
	double wire_track, wire_hit;
	a = CalibrationData.at(i).track_a;
	b = CalibrationData.at(i).track_b;
	x = CalibrationData.at(i).hit_pos_X;
	z = CalibrationData.at(i).hit_pos_Z;
	x_wire = CalibrationData.at(i).wire_pos_X;
	wire_track = fabs((z - b)/a - x_wire);
	wire_hit = fabs( x - x_wire);
	double delta_val;
	if (fabs(wire_hit) < fabs(wire_track)) delta_val = fabs(wire_track - wire_hit);
	if (fabs(wire_hit) > fabs(wire_track)) delta_val = -fabs(wire_track - wire_hit);
	CalibrationData.at(i).delta = delta_val;

	if (CalibrationData.at(i).track_angle <= 89.5) // change
	{
		delta -> Fill(CalibrationData.at(i).drift_time, delta_val);
	}
}
