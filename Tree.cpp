#include "Tree.h"

Tree::Tree(int argc, char *argv[])
{
	// from command line
	no_of_args = argc - 1;
	output_dir_name = Form(TString("./results/"),0);
	output_file_name = Form(TString("./results/data_")+argv[1]+TString(".root"),0);
	no_of_events_user = std::atoi(argv[3]);
	rough_tree = false;
	if(1==std::atoi(argv[4])) rough_tree = true;
	preselected_tree = false;
	if(1==std::atoi(argv[5])) preselected_tree = true;
	path_to_tree = argv[6];

	// variables to read / write data 
	hits_total = 1;
	hits_ref = -1;
	hits_trigger = -1;
	hits_target = -1;
	trigger_type = -1;
	hits_dirc = -1;
	hits_wire = -1;
	hits_hodo = -1;
	hits_scin = -1;
	hits_cherenkov = -1;
	hits_hodo_H = -1;
	hits_hodo_V = -1;
	hits_hodo_D = -1;
	hits_start_up = -1;
	error_flag = 0;
	hits_good = -1;

	create_output_directory();
	create_output_file();
	// creates required trees in the output root file
	rough_hist = output_file -> mkdir("Rough");
	preselected_hist = output_file -> mkdir("Preselected");
	if (rough_tree)
	{
		create_rough_data_tree();
	}
	if (preselected_tree)
	{
		create_preselected_data_tree();
	}
	// creates chain of input root trees
	open_input_files(argv);
	// sets no of events to analyse according to command line
	if (-1==no_of_events_user || no_of_events_user >= all_entries)
	{
		number_to_analyse = all_entries;
		std::cout << "* all events " << all_entries << " will be analysed" << std::endl;
	}
	else
	{
		number_to_analyse = no_of_events_user;
		std::cout << "* " << number_to_analyse << " events will be analysed" << std::endl;
	}
}

Tree::~Tree()
{ 

}

// =======================================================================================================
// =============================== OUTPUT ================================================================
// =======================================================================================================
void Tree::create_output_directory()
{
	boost::filesystem::create_directories(output_dir_name);
	std::cout << "* results will be saved in the directory: " << output_dir_name << std::endl;
}

void Tree::create_output_file()
{
	output_file = new TFile(output_file_name,"RECREATE","results");
	std::cout << "    root file: " << output_file_name << std::endl;
}

void Tree::save_output_file()
{
	save_rough_histos();
	save_preselected_histos();
	output_file -> Write();
}

void Tree::create_preselected_data_tree()
{
	preselected_data_tree = new TTree ("preselected", "preselected");
	// the structure of this tree should be the same as the one from the easyparser
	preselected_data_tree->Branch ("time_real", &time_real);
	preselected_data_tree->Branch ("time_diff", &time_diff);
	preselected_data_tree->Branch ("time_overthres", &time_overthres);
	preselected_data_tree->Branch ("global_chan", &gglobal_chan);
	preselected_data_tree->Branch ("hits_total", &hits_total);
	//preselected_data_tree->Branch ("hits_ref", &hits_ref);
	//preselected_data_tree->Branch ("hits_cherenkov", &hits_cherenkov);
	preselected_data_tree->Branch ("hits_good", &hits_good);
	//preselected_data_tree->Branch ("hits_channel", hits_channel, "hits_channel[2860]/I");
	//preselected_data_tree->Branch ("tottime_trigger", &tottime_trigger, "time_trigger/D");
	preselected_data_tree->Branch ("P349_hitdata",&ghitdata);
	std::cout << "        tree for preselected data was created" << std::endl;
}

void Tree::create_rough_data_tree()
{
	rough_data_tree = new TTree ("rough", "rough");
	// the structure of this tree should be the same as the one from the easyparser
	rough_data_tree->Branch ("time_real", &time_real);
	rough_data_tree->Branch ("time_diff", &time_diff);
	rough_data_tree->Branch ("time_overthres", &time_overthres);
	rough_data_tree->Branch ("global_chan", &gglobal_chan);
	rough_data_tree->Branch ("hits_total", &hits_total);
	//rough_data_tree->Branch ("hits_ref", &hits_ref);
	//rough_data_tree->Branch ("hits_cherenkov", &hits_cherenkov);
	rough_data_tree->Branch ("hits_good", &hits_good);
	//rough_data_tree->Branch ("hits_channel", hits_channel, "hits_channel[2860]/I");
	//rough_data_tree->Branch ("tottime_trigger", &tottime_trigger, "time_trigger/D");
	rough_data_tree->Branch ("P349_hitdata",&ghitdata);
	std::cout << "        tree for rough data was created" << std::endl;
}

// --- filling trees ---
void Tree::fill_rough_data_tree()
{
	if (rough_tree)
	{
		rough_data_tree -> Fill();
	}
}

void Tree::fill_rough_histos(hist_data _data_for_hists)
{
	Hist::fill_start_histos_rough(_data_for_hists.start_data);
	Hist::fill_TOF_histos_rough(_data_for_hists.tof_data);
	Hist::fill_D1_histos_rough(_data_for_hists.d1_data);
	Hist::fill_D2_histos_rough(_data_for_hists.d2_data);
	Hist::fill_HEX_histos_rough(_data_for_hists.hex_data);
	Hist::fill_Intermediate_histos_rough(_data_for_hists.intermediate_data);
	Hist::fill_Fiber_histos_rough(_data_for_hists.fiber_data);
}


void Tree::fill_preselected_data_tree()
{
	if (preselected_tree)
	{
		preselected_data_tree -> Fill();
	}
}

void Tree::fill_preselected_histos(hist_data _data_for_hists)
{
	Hist::fill_start_histos_preselected(_data_for_hists.start_data);
	Hist::fill_TOF_histos_preselected(_data_for_hists.tof_data);
	Hist::fill_D1_histos_preselected(_data_for_hists.d1_data);
	Hist::fill_D2_histos_preselected(_data_for_hists.d2_data);
	Hist::fill_HEX_histos_preselected(_data_for_hists.hex_data);
	Hist::fill_Intermediate_histos_preselected(_data_for_hists.intermediate_data);
	Hist::fill_Fiber_histos_preselected(_data_for_hists.fiber_data);
}

TFile* Tree::get_output_file()
{
	return output_file;
}

// =======================================================================================================
// =============================== INPUT  ================================================================
// =======================================================================================================
void Tree::open_input_files(char *argv[])
{
	std::cout << "* no of used root files: " << no_of_args - 6 << std::endl;
	// create chain
	chain = new TChain(argv[6]);
	for (int i = 7; i < no_of_args+1; i++)
	{
		std::cout << "    " << i - 6 << ". file: " << argv[i] << " added to chain" << std::endl;
		chain->Add(argv[i]);
	}
	std::cout << "    path to the input tree: " << argv[6] << std::endl;
	chain->SetBranchAddress("hits_total", &hits_total);
	chain->SetBranchAddress("hits_good", &hits_good);
	chain->SetBranchAddress("P349_hitdata",&ghitdata);
	chain->SetBranchAddress("time_real", &time_real);
	chain->SetBranchAddress("time_diff", &time_diff);
	chain->SetBranchAddress("time_overthres", &time_overthres);
	chain->SetBranchAddress("global_chan", &gglobal_chan);

	all_entries = chain->GetEntries();

	std::cout << "* total number of events in chain: " << all_entries << std::endl;
}

long int Tree::get_no_of_events_to_analyse()
{
	return number_to_analyse;
}

// =======================================================================================================
// =============================== ENTRIES & GOOD HITS====================================================
// =======================================================================================================
void Tree::get_entry(int _entry)
{
	ghitdata->Clear();
	time_real->clear();
	time_overthres->clear();
	time_diff->clear();
	gglobal_chan->clear();
	chain->GetEntry(_entry);
}

int Tree::no_of_good_hits()
{
	return hits_good;
}

void Tree::get_good_hit(int _hit)
{
	// trb? tdc? chan?
	P349_data *temp = (P349_data*)ghitdata->At(_hit);
	gh_treal = temp->GetRealtime();
	gh_det = temp->GetDetector();
	gh_layer = temp->GetDetectorlayer();
	gh_element = temp->GetLayerelement();
	gh_edge = temp->GetEdge();
}

// --- return values ---
Double_t Tree::get_treal()
{
	return gh_treal;
}

Int_t Tree::get_det()
{
	return gh_det;
}

Int_t Tree::get_layer()
{
	return gh_layer;
}

Int_t Tree::get_element()
{
	return gh_element;
}

Int_t Tree::get_edge()
{
	return gh_edge;
}

// ==========================================================================================================
// ======================== HISTOS FUNCTIONS ================================================================
// ==========================================================================================================
void Tree::save_rough_histos()
{
	if (Hist::start_histos_rough)
	{
		make_hist_dir("START",1);
		Hist::START_Rough_Layer_Up_Multiplicity -> Write();
		Hist::START_Rough_Layer_Down_Multiplicity -> Write();
		Hist::START_event_type_up -> Write();
		Hist::START_event_type_down -> Write();
		for (int i = 0; i < 7; i++)
		{
			START_time_diff[i] ->GetXaxis()->SetLabelSize(0.05);
			START_time_diff[i] ->GetXaxis()->SetTitleSize(0.05);
			START_time_diff[i] ->GetYaxis()->SetLabelSize(0.05);
			START_time_diff[i] ->GetYaxis()->SetTitleSize(0.05);
			START_time_diff[i] ->SetLineWidth(3);
			START_time_diff[i] -> Write();
		}
	}

	if (Hist::tof_histos_rough)
	{
		make_hist_dir("TOF",1);
		Hist::TOF_Rough_Layer_Up_Multiplicity -> Write();
		Hist::TOF_Rough_Layer_Down_Multiplicity -> Write();
		Hist::TOF_Rough_Layer_Up_Elements -> Write();
		Hist::TOF_Rough_Layer_Down_Element -> Write();
	}

	if (Hist::inter_histos_rough)
	{
		make_hist_dir("INTERMEDIATE",1);
		Hist::Intermediate_Rough_Layer_Up_Multiplicity -> Write();
		Hist::Intermediate_Rough_Layer_Down_Multiplicity -> Write();
		Hist::Intermediate_Rough_Layer_Up_Elements -> Write();
		Hist::Intermediate_Rough_Layer_Down_Element -> Write();
	}

	if (Hist::D1_histos_rough)
	{
		make_hist_dir("D1",1);
		for (int i = 0; i < 8; i++)
		{
			Hist::D1_Rough_Elements[i] -> Write();
			Hist::D1_Rough_Multiplicity[i] -> Write();
			Hist::D1_Rough_DriftTime[i] -> Write();
		}
	}

	if (Hist::D2_histos_rough)
	{
		make_hist_dir("D2",1);
		for (int i = 0; i < 6; i++)
		{
			Hist::D2_Rough_Elements[i] -> Write();
			Hist::D2_Rough_Multiplicity[i] -> Write();
			Hist::D2_Rough_DriftTime[i] -> Write();
		}
	}

	if (Hist::HEX_histos_rough)
	{
		make_hist_dir("HEX",1);
		for (int i = 0; i < 7; i++)
		{
			Hist::HEX_Rough_Elements[i] -> Write();
			Hist::HEX_Rough_Multiplicity[i] -> Write();
			Hist::HEX_Rough_DriftTime[i] -> Write();
		}
	}

	if (Hist::fiber_histos_rough)
	{
		make_hist_dir("FIBER",1);
		for (int i = 0; i < 3; i++)
		{
			Hist::Fiber_Rough_Elements[i] -> Write();
			Hist::Fiber_Rough_Multiplicity[i] -> Write();
		}
	}
}

void Tree::save_preselected_histos()
{
	if (Hist::start_histos_preselected)
	{
		make_hist_dir("START",2);
		Hist::START_Preselected_Layer_Up_Multiplicity -> Write();
		Hist::START_Preselected_Layer_Down_Multiplicity -> Write();
		Hist::START_Mean_Time -> Write();
		Hist::START_Time_Up -> Write();
		Hist::START_Time_Down -> Write();

	}

	if (Hist::tof_histos_preselected)
	{
		make_hist_dir("TOF",2);
		Hist::TOF_Preselected_Layer_Up_Multiplicity -> Write();
		Hist::TOF_Preselected_Layer_Down_Multiplicity -> Write();
		Hist::TOF_Preselected_Layer_Up_Element -> Write();
		Hist::TOF_Preselected_Layer_Down_Element -> Write();
		Hist::TOF_Mean_Time -> Write();
		Hist::TOF_Time_Up -> Write();
		Hist::TOF_Time_Down -> Write();

		Hist::TOF_Rough_Elements_When8_Up -> SetLineWidth(3);
		Hist::TOF_Rough_Elements_When8_Down -> SetLineWidth(3);
		Hist::TOF_Rough_Elements_When8_Up -> SetLineColor(kBlue);
		Hist::TOF_Rough_Elements_When8_Down -> SetLineColor(kRed);

		Hist::TOF_Rough_Elements_When8_Up->GetXaxis()->SetLabelSize(0.05);
		Hist::TOF_Rough_Elements_When8_Up->GetXaxis()->SetTitleSize(0.05);
		Hist::TOF_Rough_Elements_When8_Down->GetXaxis()->SetLabelSize(0.05);
		Hist::TOF_Rough_Elements_When8_Down->GetXaxis()->SetTitleSize(0.05);
		Hist::TOF_Rough_Elements_When8_Up->GetYaxis()->SetLabelSize(0.05);
		Hist::TOF_Rough_Elements_When8_Up->GetYaxis()->SetTitleSize(0.05);
		Hist::TOF_Rough_Elements_When8_Down->GetYaxis()->SetLabelSize(0.05);
		Hist::TOF_Rough_Elements_When8_Down->GetYaxis()->SetTitleSize(0.05);

		Hist::TOF_Rough_Elements_When8_Up -> Write();
		Hist::TOF_Rough_Elements_When8_Down -> Write();

		Hist::TOF_Rough_Multiplicity_When8_Up -> SetLineWidth(3);
		Hist::TOF_Rough_Multiplicity_When8_Down -> SetLineWidth(3);
		Hist::TOF_Rough_Multiplicity_When8_Up -> SetLineColor(kBlue);
		Hist::TOF_Rough_Multiplicity_When8_Down -> SetLineColor(kRed);

		Hist::TOF_Rough_Multiplicity_When8_Up ->GetXaxis()->SetLabelSize(0.05);
		Hist::TOF_Rough_Multiplicity_When8_Up ->GetXaxis()->SetTitleSize(0.05);
		Hist::TOF_Rough_Multiplicity_When8_Down ->GetXaxis()->SetLabelSize(0.05);
		Hist::TOF_Rough_Multiplicity_When8_Down ->GetXaxis()->SetTitleSize(0.05);
		Hist::TOF_Rough_Multiplicity_When8_Up ->GetYaxis()->SetLabelSize(0.05);
		Hist::TOF_Rough_Multiplicity_When8_Up ->GetYaxis()->SetTitleSize(0.05);
		Hist::TOF_Rough_Multiplicity_When8_Down ->GetYaxis()->SetLabelSize(0.05);
		Hist::TOF_Rough_Multiplicity_When8_Down ->GetYaxis()->SetTitleSize(0.05);

		Hist::TOF_Rough_Multiplicity_When8_Up -> Write();
		Hist::TOF_Rough_Multiplicity_When8_Down -> Write();

		TCanvas *e1 = new TCanvas("TOF_Rough_Elements_When8","TOF_Rough_Elements_When8");
		Hist::TOF_Rough_Elements_When8_Up -> Draw();
		Hist::TOF_Rough_Elements_When8_Down -> Draw("same");
		gPad -> BuildLegend();
		e1 -> Write();

		TCanvas *e2 = new TCanvas("TOF_Rough_Multiplicity_When8","TOF_Rough_Multiplicity_When8");
		Hist::TOF_Rough_Multiplicity_When8_Up -> Draw();
		Hist::TOF_Rough_Multiplicity_When8_Down -> Draw("same");
		gPad -> BuildLegend();
		e2 -> Write();
	}

	if (Hist::inter_histos_preselected)
	{
		make_hist_dir("INTERMEDIATE",2);
		Hist::Intermediate_Preselected_Layer_Up_Multiplicity -> Write();
		Hist::Intermediate_Preselected_Layer_Down_Multiplicity -> Write();
		Hist::Intermediate_Preselected_Layer_Up_Element -> Write();
		Hist::Intermediate_Preselected_Layer_Down_Element -> Write();
	}

	if (Hist::D1_histos_preselected)
	{
		make_hist_dir("D1",2);
		D1_no_of_planes -> Write();
		D1_no_of_cells -> Write();
		D1_no_planes_vs_cells -> Write();
		for (int i = 0; i < 8; i++)
		{
			Hist::D1_Preselected_Elements[i] -> Write();
			Hist::D1_Preselected_Multiplicity[i] -> Write();
			Hist::D1_Preselected_DriftTime[i] -> Write();
		}
		make_hist_dir("D1CorrWiresDriftTime",2);
		for (int i = 0; i < 42; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				D1_L1L2[i][j] -> Write();
				//D1_L1L2[i][j] -> ProjectionX("",0,-1)-> Write();
				//D1_L1L2[i][j] -> ProjectionY("",0,-1)-> Write();
			}
		}
		for (int i = 0; i < 42; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				D1_L7L8[i][j] -> Write();
				//D1_L7L8[i][j] -> ProjectionX("",0,-1)-> Write();
				//D1_L7L8[i][j] -> ProjectionY("",0,-1)-> Write();
			}
		}
		make_hist_dir("D1DriftTimes",2);
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 42; j++)
			{
				D1_wires_offsets[i][j] -> Write();
			}
		}
//		make_hist_dir("D1CorrToTDriftTime",2);
//		for (int i = 0; i < 42; i++)
//		{
//			D1_L1[i] -> Write();
//			D1_L2[i] -> Write();
//			D1_L7[i] -> Write();
//			D1_L8[i] -> Write();
//		}
//		make_hist_dir("D1ChannelMultiplicities",2);
//		for (int i = 0; i < 8; i++)
//		{
//			for (int j = 0; j < 42; j++) D1_channel_multiplicities[i][j] -> Write();
//		}
	}
		
	if (Hist::D2_histos_preselected)
	{
		make_hist_dir("D2",2);
		D2_no_of_planes -> Write();
		D2_no_of_cells -> Write();
		D2_no_planes_vs_cells -> Write();
		for (int i = 0; i < 6; i++)
		{
			Hist::D2_Preselected_Elements[i] -> Write();
			Hist::D2_Preselected_Multiplicity[i] -> Write();
			Hist::D2_Preselected_DriftTime[i] -> Write();
		}
		make_hist_dir("D2DriftTimes",2);
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 42; j++)
			{
				D2_wires_offsets[i][j] -> Write();
			}
		}
		make_hist_dir("D2CorrWiresDriftTime",2);
		for (int i = 0; i < 42; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				D2_L1L2[i][j] -> Write();
			}
		}
		for (int i = 0; i < 42; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				D2_L3L4[i][j] -> Write();
			}
		}
		for (int i = 0; i < 42; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				D2_L5L6[i][j] -> Write();
			}
		}
	}

	if (Hist::HEX_histos_preselected)
	{
		make_hist_dir("HEX",2);;
		for (int i = 0; i < 7; i++)
		{
			Hist::HEX_Preselected_Elements[i] -> Write();
			Hist::HEX_Preselected_Multiplicity[i] -> Write();
			Hist::HEX_Preselected_DriftTime[i] -> Write();
		}
		make_hist_dir("HEXDriftTimes",2);
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 80; j++)
			{
				HEX_wires_offsets[i][j] -> Write();
			}
		}
		make_hist_dir("HEXCorrWiresDriftTime",2);
		for (int i = 0; i < 80; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				HEX_L1L4[i][j] -> Write();
			}
		}
		for (int i = 0; i < 80; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				HEX_L2L3[i][j] -> Write();
			}
		}
		for (int i = 0; i < 80; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				HEX_L5L6[i][j] -> Write();
			}
		}
	}

	if (Hist::fiber_histos_preselected)
	{
		make_hist_dir("FIBER",2);
		for (int i = 0; i < 3; i++)
		{
			Hist::Fiber_Preselected_Elements[i] -> Write();
			Hist::Fiber_Preselected_Multiplicity[i] -> Write();
		}
		Hist::V_vs_H -> Write();
	}
	
}

void Tree::make_hist_dir(const char* name, const int dir)
{
	if (1==dir) output_hist = rough_hist -> mkdir(name);
	if (2==dir) output_hist = preselected_hist -> mkdir(name);
	output_hist -> cd();
}