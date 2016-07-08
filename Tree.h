#ifndef TREE_H
#define TREE_H
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TMinuit.h"
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TGaxis.h>
#include <TF1.h>
#include <Math/Factory.h>
#include <Math/Functor.h>
#include <numeric>
#include <boost/filesystem.hpp>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include "P349_data.h"
#include "Hist.h"
#include "Config.h" // only because of struct

class Tree
	: public Hist
{
public:
	Tree();
	Tree(int argc, char *argv[]);
	~Tree();
	void save_output_file();
	void create_rough_data_tree();

	long int get_no_of_events_to_analyse();
	int no_of_good_hits();

	void get_entry(int _entry);
	void get_good_hit(int _hit);

	void fill_rough_data_tree(start_hist_data _start_data);
	void fill_preselected_data_tree(start_hist_data _start_data);

	// get hits
	Double_t get_treal();
	Int_t get_det();
	Int_t get_layer();
	Int_t get_element();
	Int_t get_edge();

private:
	void create_output_directory();
	void create_output_file();
	void create_preselected_data_tree();
	void add_files_to_chain();
	void open_input_files(char *argv[]);

	// values from command line
	// <outputDirectoryName> <analysis stage> <no_of_events_to_process> <rough data tree> <preselected data tree> <path/data_file_1.root> ... <path/data_file_N.root> <path_to_tree>
	int no_of_args;
	TString output_file_name;
	std::string output_dir_name;
	int analysis_stage;
	int no_of_events_user;  // no of events selected by user. -1 -> all events in chain
	bool rough_tree;
	bool preselected_tree;
	TString path_to_tree;

	// chain of root files
	TChain *chain;
	long int all_entries; // all entries in chain
	long int number_to_analyse; // user or max in chain

	// output file
	TFile* output_file;

	// trees
	TTree *rough_data_tree;
	TTree *preselected_data_tree;

	// directories
	TDirectory *rough_hist;
	TDirectory *preselected_hist;

	// variables for reading/saving ---> change
	std::vector < int > trb;
	std::vector < int > tdc;
	std::vector < int > edge;  
	std::vector < int > chan;
	std::vector < int > global_chan;
	std::vector < int > time_raw_coarse;
	std::vector < int > time_raw_fine;
	std::vector < int > time_raw_epoch;
	int reftimes[14][4][3];
	int time_trigger[6];
	int hits_total;
	int hits_ref;
	int hits_trigger;
	int hits_target;
	int hits_channel[3640];
	int trigger_type;
	int hits_dirc;
	int hits_wire;
	int hits_hodo;
	int hits_scin;
	int hits_cherenkov;
	int hits_hodo_H;
	int hits_hodo_V;
	int hits_hodo_D;
	int hits_start_up;
	int error_flag;
	std::vector < double > *time_real;
	std::vector < double > *time_overthres;
	std::vector < double > *time_diff;
	std::vector < int > *gglobal_chan; // does not work 08.07
	int hits_good;
	double treal;
	double tover;
	double tdelta;
	double ttrigger;
	double tottrigger;
	double tottime_trigger;
	TClonesArray *ghitdata = new TClonesArray("P349_data");

	// variables to read data
	Int_t gh_trb;			// good hit trb
	Int_t gh_tdc;
	Int_t gh_chan;
	Double_t gh_treal;
	Double_t gh_tot;
	Int_t gh_det;
	Int_t gh_layer;
	Int_t gh_element;
	Int_t gh_edge;
};

#endif
