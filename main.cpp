#include "frame.h"


int main(int argc, char *argv[])
{
	TCanvas *dummy = new TCanvas();
	delete dummy;
	TString name;
	// object with config data is created
	Config config = Config(); 
	if( false == check_input(argc, argv) ) return 0;
	// opening input file(s), creating output file
	Tree *in_out = new Tree(argc, argv);

	const int analysis_stage = std::atoi(argv[2]); // we read rough (1) or preselected (2) data 

	//-----------------------------------------------------------------------------------------------------
	TH1F *tof = new TH1F("tof","TOF=0.5*[(TOF_Up+TOF_Down)-(Start_Up+Start_Down)];TOF [ns]; counts", 40000, -800, 300);
  TH1F *START_Mean_Time = new TH1F("start_mean", "START mean time 0.5*(timeUp-timeDown)", 40000, -100, 1200);
  TH1F *TOF_Mean_Time = new TH1F("tof_mean", "TOF mean time 0.5*(timeUp-timeDown)", 40000, -400, 700);
  TH1F *D1_HEX_pos_diff = new TH1F("D1_HEX_pos_diff","D1_HEX_pos_diff", 150, 0, 45);
	//-----------------------------------------------------------------------------------------------------
	SingleEvent *single_event;
	//EventDisplay *event_to_display;
	//SimpleCalibration *simple_calibration = new SimpleCalibration(config);
  //Calibration3d *calibration = new Calibration3d(config);
  //Calibration3d_D2 *calibration_D2 = new Calibration3d_D2(config);
  //Calibration3d_HEX *calibration_HEX = new Calibration3d_HEX(config);
  //CalibrationD1D2 *calibrationd1d2 = new CalibrationD1D2(config);
  //TrackReconstruction *track_reco = new TrackReconstruction(config);
  //D1D2Reconstruction  *d1d2_reco = new D1D2Reconstruction(config);
  D1D23d *d1d2 = new D1D23d(config);
	std::cout << "* start of the loop over the events" << std::endl;
  int delme_iter = 0;
	for (long int entry = 0; entry < in_out -> Tree::get_no_of_events_to_analyse(); entry++)
  	{
  		//std::cout << entry << std::endl;
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

    //std::cout << "-------" << entry << std::endl;
		if (single_event -> SingleEvent::was_correct_event(analysis_stage))
  		{

        delme_iter++;
  			// filling control histos for preselected data
  			// checking if preselected tree = 1/0 and filling the tree or not
  			name = Form("Event_%ld", entry);
  			in_out -> Tree::fill_preselected_data_tree();
        in_out -> Tree::fill_preselected_histos(single_event -> SingleEvent::get_hist_data());
  			//tof -> Fill(single_event -> SingleEvent::getTOF());
        //START_Mean_Time  -> Fill(single_event -> SingleEvent::Start::getTime());
        //TOF_Mean_Time  -> Fill(single_event -> SingleEvent::TOF::getTime());
        //std::cout << "test_calculate_distances" << std::endl;
  			single_event -> SingleEvent::test_calculate_distances();

        //D1_HEX_pos_diff -> Fill(single_event -> SingleEvent::test_positions_histogram());
  			//event_to_display = new EventDisplay(entry, config, single_event -> get_event_to_display());
  			//event_to_display -> get_canvas() -> Write(name);
  			//name = Form("results/Event_%ld.png", entry);
  			//event_to_display -> get_canvas() -> SaveAs(name);

  			//data for the simple calibration
  			//simple_calibration -> SimpleCalibration::get_data(single_event -> SingleEvent::D1::get_data_for_simple_calibration());
  			//calibration -> get_data( single_event -> SingleEvent::D1::get_data_for_calibration() ); 
        //delete event_to_display;
        //std::cout << "ok1" << std::endl;
        //calibration_D2 -> get_data( single_event -> SingleEvent::D2::get_data_for_calibration() ); 
        //std::cout << "ok2" << std::endl;
        //std::cout << "ok1" << std::endl;
        //calibration_HEX -> get_data( single_event -> SingleEvent::HEX::get_data_for_calibration() ); 
        //track_reco -> get_data(single_event -> SingleEvent::get_data_for_track_reconstruction());
        //d1d2_reco -> get_data(single_event -> SingleEvent::get_data_for_track_reconstruction());
        d1d2 -> get_data(single_event -> SingleEvent::get_data_for_track_reconstruction());
        //std::cout << "ok0 " << std::endl;
        //calibrationd1d2 -> get_data(single_event -> SingleEvent::get_data_for_D1D2_calibration());
        //std::cout << "ok01" << std::endl;
  			
  		} // end if correct event

  		// filling control histos for rough data
  		// checking if rough tree = 1/0 and filling the tree or not
  		in_out -> Tree::fill_rough_data_tree();
      in_out -> Tree::fill_rough_histos(single_event -> SingleEvent::get_hist_data());
  		delete single_event;
  	} // end of loop over events
    in_out -> Tree::save_output_file();

    TFile test_file("results/res_file.root","UPDATE");

    std::cout << "iter " << delme_iter << std::endl;

    d1d2 -> tell_no_of_events();
    d1d2 -> calculate_init_params();
    d1d2 -> set_config_positions();
    //d1d2 -> rotateD1(90,0,0);
    d1d2 -> fit_in_3d();
    d1d2 -> fill_histos();
    d1d2 -> save_histos();

    

    // in D1D2Reconstruction offsets for y and for x/z work differently. y is set on hit functions, x/z are set on data
    // therefore - y there should be given an absolute value of shift (not a change)
//t    d1d2_reco -> tell_no_of_events();
//t    double offset[200], chisq[200], off, chi,first_offset, step;
//t    int no_of_iter;
//t    no_of_iter = 1;
//t    first_offset = 0.34323;
//t    step = 0.0;
//t    d1d2_reco -> set_x_offset(0);
//t    for (int i = 0; i < no_of_iter; i++)
//t    {
//t      std::cout << "offset determination... " << i + 1 << " out of " << no_of_iter << " done" << std::endl;
//t      if (i==0) off = first_offset;
//t      //else off = step; x/z
//t      else off += step;
//t      //d1d2_reco -> set_z_offset(off);
//t      d1d2_reco -> fit_in_3d_D1();
//t      d1d2_reco -> fit_in_3d_D2();
//t      d1d2_reco -> set_y_offset(off);
//t      d1d2_reco -> fit();
//t      d1d2_reco -> plot_D1_d2_phi_corr();
//t      d1d2_reco -> save_histos();
//t      d1d2_reco -> deletations();
//t      chi = d1d2_reco -> get_mean_chisq();
//t      offset[i] = first_offset+i*step;
//t      chisq[i] = chi;
//t    }
//t    TGraph *graph = new TGraph(no_of_iter,offset,chisq);
//t    //graph -> Draw("AP");
//t    graph->Write();

//    calibrationd1d2  -> tell_no_of_events();
//    calibrationd1d2 -> set_no_of_bin_in_event();
//
//    for (int i = 0; i < 6; i++)
//    {
//      calibrationd1d2 -> set_no_of_iteration(i);
//      calibrationd1d2 -> calculate_hit_position();
//      calibrationd1d2 -> fit_events();
//      calibrationd1d2 -> save_histograms();
//      calibrationd1d2 -> fit_delta_projections();
//      calibrationd1d2 -> set_pos_Xerr();
//      calibrationd1d2 -> apply_corrections();
//      calibrationd1d2 -> plot_current_calibration();
//      calibrationd1d2 -> deletations();
//    }

//    track_reco -> tell_no_of_events();
//    //!track_reco -> set_detectors_positions_on_points();
//    track_reco -> fit_in_3d_D1();
//    track_reco -> fit_in_3d_D2();
//    track_reco -> fit_in_3d_HEX();
//    track_reco -> plot_D1_d2_phi_corr();
//    track_reco -> set_detectors_positions_on_vectors();
//    track_reco -> reconstructed_D2_vs_expected_D1();
//    track_reco -> save_histos();

//    calibration_HEX -> tell_no_of_events();
//    calibration_HEX -> set_no_of_bin_in_event();
//
//    for (int i = 0; i < 3; i++)
//    {
//      calibration_HEX -> set_no_of_iteration(i);
//      calibration_HEX -> calculate_hit_position();
//      calibration_HEX -> fit_events();
//      calibration_HEX -> save_histograms();
//      calibration_HEX -> fit_delta_projections();
//      calibration_HEX -> set_pos_Xerr();
//      calibration_HEX -> apply_corrections();
//      calibration_HEX -> plot_current_calibration();
//      calibration_HEX -> deletations();
//    }
//    

    /*calibration_D2 -> tell_no_of_events();
    calibration_D2 -> set_no_of_bin_in_event();

    for (int i = 0; i < 6; i++)
    {
      calibration_D2 -> set_no_of_iteration(i);
      calibration_D2 -> calculate_hit_position();
      calibration_D2 -> fit_events();
      calibration_D2 -> save_histograms();
      calibration_D2 -> fit_delta_projections();
      calibration_D2 -> set_pos_Xerr();
      calibration_D2 -> apply_corrections();
      calibration_D2 -> plot_current_calibration();
      calibration_D2 -> deletations();
    }*/
    
  	//tof -> Write();
    //START_Mean_Time -> Write();
    //TOF_Mean_Time -> Write();

    test_file.Close();
    TCanvas *ctemp = new TCanvas("ctemp","ctemp");
    //D1_HEX_pos_diff -> Draw();
    //ctemp -> Print("unequal.png");
  	//in_out -> Tree::save_output_file();
  	std::cout << "\n" << std::endl;
}