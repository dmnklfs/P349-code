#include "frame.h"


int main(int argc, char *argv[])
{
	TCanvas *dummy = new TCanvas();
	delete dummy;
	// object with config data is created
	Config config = Config(); 
	std::cout << "f" << std::endl;
	if( false == check_input(argc, argv) ) return 0;
	// opening input file(s), creating output file
	Tree *in_out = new Tree(argc, argv);

	const int analysis_stage = std::atoi(argv[2]); // we read rough (1) or preselected (2) data 

	//-----------------------------------------------------------------------------------------------------
	TH1F *tof = new TH1F("tof","TOF=0.5*[(TOF_Up+TOF_Down)-(Start_Up+Start_Down)];TOF [ns]; counts", 600, -800, 300);
	//-----------------------------------------------------------------------------------------------------
	SingleEvent *single_event;
	std::cout << "* start of the loop over the events" << std::endl;
	for (long int entry = 0; entry < in_out -> Tree::get_no_of_events_to_analyse(); entry++)
  	{
  		single_event = new SingleEvent(config);
  		if(0==entry%10000) std::cout << entry << std::endl;
  		in_out -> Tree::get_entry(entry);
  		// start of the loop over good hits in the single event
  		for (Int_t i = 0; i < in_out -> Tree::no_of_good_hits() ; i++)
	    {
	    	// reading data
		   	in_out -> Tree::get_good_hit(i);
		   	single_gh_data good_hit_data; // if more data needs to be read - modify single_gh_data struct
		   	good_hit_data.detector = in_out -> Tree::get_det();
		   	good_hit_data.layer = in_out -> Tree::get_layer();
			good_hit_data.element = in_out -> Tree::get_element();
			good_hit_data.edge = in_out -> Tree::get_edge();
			good_hit_data.treal = in_out -> Tree::get_treal();

			// filling detectors variables
		   	if (good_hit_data.detector == START) single_event -> Start::fill_good_hits(good_hit_data);
		   	if (good_hit_data.detector == NTOF) single_event -> TOF::fill_good_hits(good_hit_data);	
		   	if (good_hit_data.detector == ND1) single_event -> D1::fill_good_hits(good_hit_data);
		   	if (good_hit_data.detector == ND2) single_event -> D2::fill_good_hits(good_hit_data);
		   	if (good_hit_data.detector == NHEX) single_event -> HEX::fill_good_hits(good_hit_data);
		   	if (good_hit_data.detector == NINTER) single_event -> Intermediate::fill_good_hits(good_hit_data);
		   	if (good_hit_data.detector == NFIBER) single_event -> Fiber::fill_good_hits(good_hit_data);		
		} // end of loop over good hits

		if (single_event -> SingleEvent::was_correct_event(analysis_stage))
  		{
  			// filling control histos for preselected data
  			// checking if preselected tree = 1/0 and filling the tree or not
  			in_out -> Tree::fill_preselected_data_tree(single_event -> SingleEvent::get_hist_data());
  			tof -> Fill(single_event -> SingleEvent::getTOF());
  			single_event -> SingleEvent::test_calculate_distances();
  			
  		} // end if correct event

  		// filling control histos for rough data
  		// checking if rough tree = 1/0 and filling the tree or not
  		in_out -> Tree::fill_rough_data_tree(single_event -> SingleEvent::get_hist_data());
  		delete single_event;
  	} // end of loop over events

  	//tof -> Write();
  	in_out -> Tree::save_output_file();
	std::cout << "\n" << std::endl;
}