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

// --- output ---
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
	Hist::Rough_Layer_Up_Multiplicity -> Write();
	Hist::Rough_Layer_Down_Multiplicity -> Write();

	output_file -> cd();
	preselected_hist -> cd();
	Hist::Preselected_Layer_Up_Multiplicity -> Write();
	Hist::Preselected_Layer_Down_Multiplicity -> Write();
	
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

// --- input ---
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

// --- entries ---
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

// --- filling trees ---
void Tree::fill_rough_data_tree(start_hist_data _start_data)
{
	Hist::Rough_Layer_Up_Multiplicity -> Fill(_start_data.rough_multiplicity_up);
	Hist::Rough_Layer_Down_Multiplicity -> Fill(_start_data.rough_multiplicity_down);
	if (rough_tree)
	{
		rough_data_tree -> Fill();
	}
}

void Tree::fill_preselected_data_tree(start_hist_data _start_data)
{
	Hist::Preselected_Layer_Up_Multiplicity -> Fill(_start_data.preselected_multiplicity_up);
	Hist::Preselected_Layer_Down_Multiplicity -> Fill(_start_data.preselected_multiplicity_down);
	if (preselected_tree)
	{
		preselected_data_tree -> Fill();
	}
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

