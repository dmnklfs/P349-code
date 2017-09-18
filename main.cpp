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
  CalibrationD1D2 *calibrationd1d2 = new CalibrationD1D2(config);
  TrackReconstruction *track_reco = new TrackReconstruction(config);
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
        //std::cout << "ok0 " << std::endl;
        calibrationd1d2 -> get_data(single_event -> SingleEvent::get_data_for_D1D2_calibration());
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

    calibrationd1d2  -> tell_no_of_events();
    calibrationd1d2 -> set_no_of_bin_in_event();

    for (int i = 0; i < 2; i++)
    {
      calibrationd1d2 -> set_no_of_iteration(i);
      //std::cout << " ok0 " << std::endl;
      calibrationd1d2 -> calculate_hit_position();
      //std::cout << " ok1 " << std::endl;
      calibrationd1d2 -> fit_events();
      calibrationd1d2 -> save_histograms();
      calibrationd1d2 -> fit_delta_projections();
      calibrationd1d2 -> set_pos_Xerr();
      calibrationd1d2 -> apply_corrections();
      calibrationd1d2 -> plot_current_calibration();
      calibrationd1d2 -> deletations();
    }

//    track_reco -> tell_no_of_events();
//    //!track_reco -> set_detectors_positions_on_points();
//    track_reco -> fit_in_3d_D1();
//    track_reco -> fit_in_3d_D2();
//    //track_reco -> fit_in_3d_HEX();
//    track_reco -> plot_D1_d2_phi_corr();
//    track_reco -> set_detectors_positions_on_vectors();
//    track_reco -> reconstructed_D2_vs_expected_D1();
//    track_reco -> save_histos();

//    calibration_HEX -> tell_no_of_events();
//    calibration_HEX -> set_no_of_bin_in_event();
//
//    for (int i = 0; i < 2; i++)
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
    

    //CALIBRATION
    
    /*calibration -> tell_no_of_events();
    calibration -> set_no_of_bin_in_event();
    
    calibration -> set_no_of_iteration(0);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(1);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(2);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    // add: make a 3d track, make projections

    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(3);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    // add: make a 3d track, make projections

    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(4);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(5);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(6);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(7);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(8);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(9);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();*/

    /*calibration -> set_no_of_iteration(10);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(11);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(12);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(13);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(14);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(15);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(16);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(17);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(18);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(19);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();

    calibration -> set_no_of_iteration(20);
    calibration -> calculate_hit_position();
    calibration -> fit_events();
    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();*/

    /*calibration -> set_no_of_iteration(5);
    calibration -> calculate_hit_position();
    calibration -> fit_events_in_straight_layers_biased(100000);
    // add: make a 3d track, make projections

    calibration -> save_histograms();
    calibration -> fit_delta_projections();
    calibration -> set_pos_Xerr();
    calibration -> apply_corrections();
    calibration -> plot_current_calibration();
    calibration -> deletations();*/


    // SIMPLE CALIBRATION
    /*
    simple_calibration -> show_drift_times();
  	simple_calibration -> tell_no_of_events();
    //simple_calibration -> show_drift_times();
  	simple_calibration -> fit_events(2);
    //simple_calibration -> show_drift_times();
  	simple_calibration -> plot_chi2() -> Write(); //SaveAs("results/chi2.png");
    //simple_calibration -> show_drift_times();
  	simple_calibration -> plot_delta() -> Write(); //SaveAs("results/delta.png");
  	simple_calibration -> plot_delta_cut() -> Write(); //SaveAs("results/delta_cut.png");
  	simple_calibration -> fit_delta_projections("results/Fit_0/");
  	simple_calibration -> plot_current_calibration() -> Write(); //SaveAs("results/calib.png");
  	simple_calibration -> apply_corrections();
  	simple_calibration -> plot_current_calibration() -> Write(); //SaveAs("results/calib_corr.png");

  	simple_calibration -> deletations();

    std::cout << "1st it was ok " << std::endl;
  	simple_calibration -> recalculate_positions();
    std::cout << "1st it was ok " << std::endl;
  	simple_calibration -> fit_events(2);
  	simple_calibration -> plot_chi2() -> Write(); //SaveAs("results/chi2_1.png");
  	simple_calibration -> plot_delta() -> Write(); //SaveAs("results/delta_1.png");
  	simple_calibration -> plot_delta_cut() -> Write(); //SaveAs("results/delta_cut_1.png");
  	simple_calibration -> fit_delta_projections("results/Fit_1/");
  	//simple_calibration -> plot_current_calibration() -Write(); //> SaveAs("results/calib.png");
  	simple_calibration -> apply_corrections();
  	simple_calibration -> plot_current_calibration() -> Write(); //SaveAs("results/calib_corr_1.png");

  	simple_calibration -> deletations();

  	simple_calibration -> recalculate_positions();
  	simple_calibration -> fit_events(2);
  	simple_calibration -> plot_chi2() -> Write(); //SaveAs("results/chi2_2.png");
  	simple_calibration -> plot_delta() -> Write(); //SaveAs("results/delta_2.png");
  	simple_calibration -> plot_delta_cut() -> Write(); //SaveAs("results/delta_cut_2.png");
  	simple_calibration -> fit_delta_projections("results/Fit_2/");
  	//simple_calibration -> plot_current_calibration() -Write(); //> SaveAs("results/calib.png");
  	simple_calibration -> apply_corrections();
  	simple_calibration -> plot_current_calibration() -> Write(); //SaveAs("results/calib_corr_2.png");

  	simple_calibration -> deletations();

  	simple_calibration -> recalculate_positions();
  	simple_calibration -> fit_events(2);
  	simple_calibration -> plot_chi2() -> Write(); //SaveAs("results/chi2_3.png");
  	simple_calibration -> plot_delta() -> Write(); //SaveAs("results/delta_3.png");
  	simple_calibration -> plot_delta_cut() -> Write(); //SaveAs("results/delta_cut_3.png");
  	simple_calibration -> fit_delta_projections("results/Fit_3/");
  	//simple_calibration -> plot_current_calibration() -Write(); //> SaveAs("results/calib.png");
  	simple_calibration -> apply_corrections();
  	simple_calibration -> plot_current_calibration() -> Write(); //SaveAs("results/calib_corr_3.png");

  	simple_calibration -> deletations();

  	simple_calibration -> recalculate_positions();
  	simple_calibration -> fit_events(2);
  	simple_calibration -> plot_chi2() -> Write(); //SaveAs("results/chi2_4.png");
  	simple_calibration -> plot_delta() -> Write(); //SaveAs("results/delta_4.png");
  	simple_calibration -> plot_delta_cut() -> Write(); //SaveAs("results/delta_cut_4.png");
  	simple_calibration -> fit_delta_projections("results/Fit_4/");
  	//simple_calibration -> plot_current_calibration() -Write(); //> SaveAs("results/calib.png");
  	simple_calibration -> apply_corrections();
  	simple_calibration -> plot_current_calibration() -> Write(); //SaveAs("results/calib_corr_4.png");

  	simple_calibration -> deletations();

  	simple_calibration -> recalculate_positions();
  	simple_calibration -> fit_events(2);
  	simple_calibration -> plot_chi2() -> Write(); //SaveAs("results/chi2_5.png");
  	simple_calibration -> plot_delta() -> Write(); //SaveAs("results/delta_5.png");
  	simple_calibration -> plot_delta_cut() -> Write(); //SaveAs("results/delta_cut_5.png");
  	simple_calibration -> fit_delta_projections("results/Fit_5/");
  	//simple_calibration -> plot_current_calibration() -> Write(); //SaveAs("results/calib.png");
  	simple_calibration -> apply_corrections();
  	simple_calibration -> plot_current_calibration() -> Write(); //SaveAs("results/calib_corr_5.png");

  	simple_calibration -> deletations();

  	simple_calibration -> recalculate_positions();
  	simple_calibration -> fit_events(2);
  	simple_calibration -> plot_chi2() -> Write(); //SaveAs("results/chi2_6.png");
  	simple_calibration -> plot_delta() -> Write(); //SaveAs("results/delta_6.png");
  	simple_calibration -> plot_delta_cut() -> Write(); //SaveAs("results/delta_cut_6.png");
  	simple_calibration -> fit_delta_projections("results/Fit_6/");
  	//simple_calibration -> plot_current_calibration() -> Write(); //SaveAs("results/calib.png");
  	simple_calibration -> apply_corrections();
  	simple_calibration -> plot_current_calibration() -> Write(); //SaveAs("results/calib_corr_6.png");

  	simple_calibration -> deletations();

  	simple_calibration -> recalculate_positions();
  	simple_calibration -> fit_events(2);
  	simple_calibration -> plot_chi2() -> Write(); //SaveAs("results/chi2_7.png");
  	simple_calibration -> plot_delta() -> Write(); //SaveAs("results/delta_7.png");
  	simple_calibration -> plot_delta_cut() -> Write(); //SaveAs("results/delta_cut_7.png");
  	simple_calibration -> fit_delta_projections("results/Fit_7/");
  	//simple_calibration -> plot_current_calibration() -> Write(); //SaveAs("results/calib.png");
  	simple_calibration -> apply_corrections();
  	simple_calibration -> plot_current_calibration() -> Write(); //SaveAs("results/calib_corr_7.png");

  	simple_calibration -> deletations();

  	simple_calibration -> recalculate_positions();
  	simple_calibration -> fit_events(2);
  	simple_calibration -> plot_chi2() -> Write(); //SaveAs("results/chi2_8.png");
  	simple_calibration -> plot_delta() -> Write(); //SaveAs("results/delta_8.png");
  	simple_calibration -> plot_delta_cut() -> Write(); //SaveAs("results/delta_cut_8.png");
  	simple_calibration -> fit_delta_projections("results/Fit_8/");
  	//simple_calibration -> plot_current_calibration() -> Write(); //SaveAs("results/calib.png");
  	simple_calibration -> apply_corrections();
  	simple_calibration -> plot_current_calibration() -> Write(); //SaveAs("results/calib_corr_8.png");
  	//tof -> Write();
    //START_Mean_Time -> Write();
    //TOF_Mean_Time -> Write();
    */
    test_file.Close();
    TCanvas *ctemp = new TCanvas("ctemp","ctemp");
    //D1_HEX_pos_diff -> Draw();
    //ctemp -> Print("unequal.png");
  	//in_out -> Tree::save_output_file();
  	std::cout << "\n" << std::endl;
}