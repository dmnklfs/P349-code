#include "Tree.h"

Tree::Tree(int argc, char *argv[])
{
	// from command line
	no_of_args = argc - 1;
	output_dir_name = Form(TString("./results/")+argv[1]+TString("/"),0);
	output_file_name = Form(TString("./results/")+argv[1]+TString("/data_")+argv[1]+TString(".root"),0);
	no_of_events_user = std::atoi(argv[3]);
	rough_tree = false;
	if(1==std::atoi(argv[4])) rough_tree = true;
	preselected_tree = false;
	if(1==std::atoi(argv[5])) preselected_tree = true;
	path_to_tree = argv[no_of_args];

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
	output_file -> cd();
	rough_hist -> cd();
	save_rough_histos();

	output_file -> cd();
	preselected_hist -> cd();
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
	preselected_data_tree->Branch ("gglobal_chan", &gglobal_chan);
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
	rough_data_tree->Branch ("gglobal_chan", &gglobal_chan);
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
void Tree::fill_rough_data_tree(hist_data _data_for_hists)
{
	fill_start_histos_rough(_data_for_hists.start_data);
	fill_TOF_histos_rough(_data_for_hists.tof_data);
	fill_D1_histos_rough(_data_for_hists.d1_data);
	if (rough_tree)
	{
		rough_data_tree -> Fill();
	}
}

void Tree::fill_preselected_data_tree(hist_data _data_for_hists)
{
	fill_start_histos_preselected(_data_for_hists.start_data);
	fill_TOF_histos_preselected(_data_for_hists.tof_data);
	fill_D1_histos_preselected(_data_for_hists.d1_data);
	if (preselected_tree)
	{
		preselected_data_tree -> Fill();
	}
}

// =======================================================================================================
// =============================== INPUT  ================================================================
// =======================================================================================================
void Tree::open_input_files(char *argv[])
{
	std::cout << "* no of used root trees: " << no_of_args - 6 << std::endl;
	// create chain
	chain = new TChain(argv[no_of_args]);
	for (int i = 6; i < no_of_args; i++)
	{
		std::cout << "    " << i - 5 << ". file: " << argv[i] << " added to chain" << std::endl;
		chain->Add(argv[i]);
	}

	chain->SetBranchAddress("hits_total", &hits_total);
	chain->SetBranchAddress("hits_good", &hits_good);
	chain->SetBranchAddress("P349_hitdata",&ghitdata);
	chain->SetBranchAddress("time_real", &time_real);
	chain->SetBranchAddress("time_diff", &time_diff);
	chain->SetBranchAddress("time_overthres", &time_overthres);
	chain->SetBranchAddress("gglobal_chan", &gglobal_chan);

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

// ======================== FILLING =========================================================================
void Tree::fill_start_histos_rough(start_hist_data _start_data)
{
	Hist::START_Rough_Layer_Up_Multiplicity -> Fill(_start_data.rough_multiplicity_up);
	Hist::START_Rough_Layer_Down_Multiplicity -> Fill(_start_data.rough_multiplicity_down);
}

void Tree::fill_start_histos_preselected(start_hist_data _start_data)
{
	Hist::START_Preselected_Layer_Up_Multiplicity -> Fill(_start_data.preselected_multiplicity_up);
	Hist::START_Preselected_Layer_Down_Multiplicity -> Fill(_start_data.preselected_multiplicity_down);
}

void Tree::fill_TOF_histos_rough(TOF_hist_data _tof_data)
{
	Hist::TOF_Rough_Layer_Up_Multiplicity -> Fill(_tof_data.rough_multiplicity_up);
	Hist::TOF_Rough_Layer_Down_Multiplicity -> Fill(_tof_data.rough_multiplicity_down);
	for (unsigned int i = 0; i < _tof_data.rough_elements_up.size(); i++) Hist::TOF_Rough_Layer_Up_Elements -> Fill(_tof_data.rough_elements_up.at(i));
	for (unsigned int i = 0; i < _tof_data.rough_elements_down.size(); i++) Hist::TOF_Rough_Layer_Down_Element -> Fill(_tof_data.rough_elements_down.at(i));
}

void Tree::fill_TOF_histos_preselected(TOF_hist_data _tof_data)
{
	Hist::TOF_Preselected_Layer_Up_Multiplicity -> Fill(_tof_data.preselected_multiplicity_up);
	Hist::TOF_Preselected_Layer_Down_Multiplicity -> Fill(_tof_data.preselected_multiplicity_down);

	for (unsigned int i = 0; i < _tof_data.preselected_elements_up.size(); i++) Hist::TOF_Preselected_Layer_Up_Element -> Fill(_tof_data.preselected_elements_up.at(i));
	for (unsigned int i = 0; i < _tof_data.preselected_elements_down.size(); i++) Hist::TOF_Preselected_Layer_Down_Element -> Fill(_tof_data.preselected_elements_down.at(i));
}

void Tree::fill_D1_histos_rough(D1_hist_data _d1_data)
{
	// layer 1
	for (unsigned int i = 0; i < _d1_data.layer1_data.rough_elements.size(); i++) Hist::D1_Rough_Layer1_Elements -> Fill(_d1_data.layer1_data.rough_elements.at(i));
	Hist::D1_Rough_Layer1_Multiplicity -> Fill(_d1_data.layer1_data.rough_elements.size());
	// layer 2
	for (unsigned int i = 0; i < _d1_data.layer2_data.rough_elements.size(); i++) Hist::D1_Rough_Layer2_Elements -> Fill(_d1_data.layer2_data.rough_elements.at(i));
	Hist::D1_Rough_Layer2_Multiplicity -> Fill(_d1_data.layer2_data.rough_elements.size());
	// layer 7
	for (unsigned int i = 0; i < _d1_data.layer7_data.rough_elements.size(); i++) Hist::D1_Rough_Layer7_Elements -> Fill(_d1_data.layer7_data.rough_elements.at(i));
	Hist::D1_Rough_Layer7_Multiplicity -> Fill(_d1_data.layer7_data.rough_elements.size());
	// layer 8
	for (unsigned int i = 0; i < _d1_data.layer8_data.rough_elements.size(); i++) Hist::D1_Rough_Layer8_Elements -> Fill(_d1_data.layer8_data.rough_elements.at(i));
	Hist::D1_Rough_Layer8_Multiplicity -> Fill(_d1_data.layer8_data.rough_elements.size());
}

void Tree::fill_D1_histos_preselected(D1_hist_data _d1_data)
{
	// layer 1
	for (unsigned int i = 0; i < _d1_data.layer1_data.preselected_elements.size(); i++) Hist::D1_Preselected_Layer1_Elements -> Fill(_d1_data.layer1_data.preselected_elements.at(i));
	D1_Preselected_Layer1_Multiplicity -> Fill(_d1_data.layer1_data.preselected_elements.size());
	// layer 2
	for (unsigned int i = 0; i < _d1_data.layer2_data.preselected_elements.size(); i++) Hist::D1_Preselected_Layer2_Elements -> Fill(_d1_data.layer2_data.preselected_elements.at(i));
	Hist::D1_Preselected_Layer2_Multiplicity -> Fill(_d1_data.layer2_data.preselected_elements.size());
	// layer 7
	for (unsigned int i = 0; i < _d1_data.layer7_data.preselected_elements.size(); i++) Hist::D1_Preselected_Layer7_Elements -> Fill(_d1_data.layer7_data.preselected_elements.at(i));
	Hist::D1_Preselected_Layer7_Multiplicity -> Fill(_d1_data.layer7_data.preselected_elements.size());
	// layer 8
	for (unsigned int i = 0; i < _d1_data.layer8_data.preselected_elements.size(); i++) Hist::D1_Preselected_Layer8_Elements -> Fill(_d1_data.layer8_data.preselected_elements.at(i));
	Hist::D1_Preselected_Layer8_Multiplicity -> Fill(_d1_data.layer8_data.preselected_elements.size());
}

// ======================== SAVING +=========================================================================
void Tree::save_rough_histos()
{
	Hist::START_Rough_Layer_Up_Multiplicity -> Write();
	Hist::START_Rough_Layer_Down_Multiplicity -> Write();

	Hist::TOF_Rough_Layer_Up_Multiplicity -> Write();
	Hist::TOF_Rough_Layer_Down_Multiplicity -> Write();

	Hist::TOF_Rough_Layer_Up_Elements -> Write();
	Hist::TOF_Rough_Layer_Down_Element -> Write();

	Hist::D1_Rough_Layer1_Elements ->Write();
	Hist::D1_Rough_Layer1_Multiplicity -> Write();
	Hist::D1_Rough_Layer2_Elements -> Write();
	Hist::D1_Rough_Layer2_Multiplicity -> Write();
	Hist::D1_Rough_Layer7_Elements -> Write();
	Hist::D1_Rough_Layer7_Multiplicity -> Write();
	Hist::D1_Rough_Layer8_Elements -> Write();
	Hist::D1_Rough_Layer8_Multiplicity -> Write();
}
void Tree::save_preselected_histos()
{
	Hist::START_Preselected_Layer_Up_Multiplicity -> Write();
	Hist::START_Preselected_Layer_Down_Multiplicity -> Write();

	Hist::TOF_Preselected_Layer_Up_Multiplicity -> Write();
	Hist::TOF_Preselected_Layer_Down_Multiplicity -> Write();

	Hist::TOF_Preselected_Layer_Up_Element -> Write();
	Hist::TOF_Preselected_Layer_Down_Element -> Write();

	Hist::D1_Preselected_Layer1_Elements -> Write();
	Hist::D1_Preselected_Layer1_Multiplicity -> Write();
	Hist::D1_Preselected_Layer2_Elements -> Write();
	Hist::D1_Preselected_Layer2_Multiplicity -> Write();
	Hist::D1_Preselected_Layer7_Elements -> Write();
	Hist::D1_Preselected_Layer7_Multiplicity -> Write();
	Hist::D1_Preselected_Layer8_Elements -> Write();
	Hist::D1_Preselected_Layer8_Multiplicity -> Write();
}