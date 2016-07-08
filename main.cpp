#include "frame.h"


int main(int argc, char *argv[])
{
	if( false == check_input(argc, argv) ) return 0; // add checks
	Tree *in_out = new Tree(argc, argv);  // input file(s) are opened, output file is created

	SingleEvent *single_event;
	int detector; // make it a struct
	int layer;
	int element;
	int edge;
	double treal;
	std::cout << "* start of the loop over the events" << std::endl;
	for (long int entry = 0; entry < in_out -> Tree::get_no_of_events_to_analyse(); entry++)
  	{
  		single_event = new SingleEvent();
  		if(0==entry%100000) std::cout << entry << std::endl;
  		in_out -> Tree::get_entry(entry);

  		//loop over good hits in the single event
  		for (Int_t i = 0; i < in_out -> Tree::no_of_good_hits() ; i++)
	    {
		   	in_out -> Tree::get_good_hit(i);  // make it a struct
		   	detector = in_out -> Tree::get_det();
		   	layer = in_out -> Tree::get_layer();
			element = in_out -> Tree::get_element();
			edge = in_out -> Tree::get_edge();
			treal = in_out -> Tree::get_treal();
		   	if (detector == START) single_event -> SingleEvent::fill_good_hits(std::atoi(argv[2]), layer, element, treal, edge);	
		}

		if (single_event -> SingleEvent::was_correct_event(std::atoi(argv[2])))
  		{
  			// if ok - change Start::get_hist_data() to SingleEvent::
  			in_out -> Tree::fill_preselected_data_tree(single_event -> Start::get_hist_data()); // checks if preselected tree = 1 and fills it or not
  			// part for analysis of the single event
  			// ...
  			
  		}

  		in_out -> Tree::fill_rough_data_tree(single_event -> Start::get_hist_data()); // checks if rough tree = 1 and fills it or not
  		delete single_event;
  	}

  	in_out -> Tree::save_output_file();
	std::cout << "\n" << std::endl;
}