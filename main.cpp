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
  //*D1D23d *d1d2 = new D1D23d(config);
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
	   	if (good_hit_data.detector == START)   single_event -> Start::fill_good_hits(good_hit_data);
	   	if (good_hit_data.detector == NTOF)    single_event -> TOF::fill_good_hits(good_hit_data);	
	   	if (good_hit_data.detector == ND1)     single_event -> D1::fill_good_hits(good_hit_data);
	   	if (good_hit_data.detector == ND2)     single_event -> D2::fill_good_hits(good_hit_data);
	   	if (good_hit_data.detector == NHEX)    single_event -> HEX::fill_good_hits(good_hit_data);
	   	if (good_hit_data.detector == NINTER)  single_event -> Intermediate::fill_good_hits(good_hit_data);
	   	if (good_hit_data.detector == NFIBER)  single_event -> Fiber::fill_good_hits(good_hit_data);		
		} // end of loop over good hits

    //std::cout << "-------" << entry << std::endl;
    //std::cout << " ok " << std::endl;
		if (single_event -> SingleEvent::was_correct_event(analysis_stage))// && entry > 50000 && entry < 60000
 		{
      //std::cout << " ok2 " << std::endl;
      delme_iter++;
 			// filling control histos for preselected data
 			// checking if preselected tree = 1/0 and filling the tree or not
 			name = Form("Event_%ld", entry);

      //single_event -> SingleEvent::test_calculate_distances();
 			in_out -> Tree::fill_preselected_data_tree();
      in_out -> Tree::fill_preselected_histos(single_event -> SingleEvent::get_hist_data());
 			//tof -> Fill(single_event -> SingleEvent::getTOF());
       //START_Mean_Time  -> Fill(single_event -> SingleEvent::Start::getTime());
       //TOF_Mean_Time  -> Fill(single_event -> SingleEvent::TOF::getTime());
       //std::cout << "test_calculate_distances" << std::endl;
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
       //std::cout << "ok3" << std::endl;
       //std::cout << "ok1" << std::endl;
       //calibration_HEX -> get_data( single_event -> SingleEvent::HEX::get_data_for_calibration() ); 
       //track_reco -> get_data(single_event -> SingleEvent::get_data_for_track_reconstruction());
       //d1d2_reco -> get_data(single_event -> SingleEvent::get_data_for_track_reconstruction());
       //*d1d2 -> get_data(single_event -> SingleEvent::get_data_for_track_reconstruction());
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
//
//    std::cout << "iter " << delme_iter << std::endl;

//    track_reco -> tell_no_of_events();
//    //!track_reco -> set_detectors_positions_on_points();
//    track_reco -> fit_in_3d_D1();
//    track_reco -> fit_in_3d_D2();
//    track_reco -> fit_in_3d_HEX();
//    track_reco -> plot_D1_d2_phi_corr();
//    track_reco -> set_detectors_positions_on_vectors();
//    track_reco -> reconstructed_D2_vs_expected_D1();
//    track_reco -> save_histos();

//*    d1d2 -> tell_no_of_events();
    //std::cout << "1" << std::endl;
//*    d1d2 -> calculate_init_params();
    //std::cout << "2" << std::endl;
//*    d1d2 -> set_config_positions();
    //std::cout << "3" << std::endl;

    //d1d2 -> rotateD1(0, 0, 45);
    //d1d2 -> rotateD2(0, 45, 0);
//*    d1d2 -> shiftD2(0.0409,0,0,1);
//*    d1d2 -> shiftD2(0,0,2.42,1);
//*    d1d2 -> shiftD2(0,-0.37,0,1);
//*    d1d2 -> shiftD2(0,0,0.01,1);
//*    d1d2 -> rotateD2(0, -0.004, 0);
//*    d1d2 -> rotateD2(0.112,0 , 0);
//*    d1d2 -> fit_in_3d();

    //chisq[j] = d1d2 -> get_mean_chisq();
//*    d1d2->fill_histos();
//*    d1d2->save_histos();
    // 2d shift/rotations determination
//    double first_offset1, first_offset2, step1, step2;
//    int no_of_iter1, no_of_iter2;
//
//    // z
//    first_offset1 = -3.5;
//    step1 = 0.01;
//    no_of_iter1 = 100;
//
//    // x
//    first_offset2 = -0.05;
//    step2 = 0.01;
//    no_of_iter2 = 10;
//
//    const int npoints2d = no_of_iter1*no_of_iter2;
//    double var1[npoints2d], var2[npoints2d], off1, off2, chi[npoints2d];

//
//    //std::cout << "offset determination... " << i + 1 << " out of " << no_of_iter << " done" << std::endl;
//    for (int j = 0; j < no_of_iter1; j++)
//    {
//      if (j==0) off1 = first_offset1;
//      else off1 = step1;
//      d1d2 -> shiftD2(0,0,off1,1);
//      if (j!=0) d1d2 -> shiftD2(-(no_of_iter2-1)*step2,0,0,1);
//      //d1d2 -> rotateD2(0,0,0);
//      for (int k = 0; k < no_of_iter2; k++)
//      {
//        //std::cout << j*no_of_iter2+k << std::endl;
//        if ((j*no_of_iter2+k)%10 == 0) std::cout << j*no_of_iter2+k << " out of " << no_of_iter1*no_of_iter2 << " done " << std::endl;
//        if (k==0)
//        {
//          if(j==0) off2 = first_offset2;
//          else off2 = 0;
//        }
//        else off2 = step2;
//        d1d2 -> shiftD2(off2,0,0,1);
//        d1d2 -> fit_in_3d();
//        chi[j*no_of_iter2+k] = d1d2 -> get_mean_chisq();
//        var1[j*no_of_iter2+k] = first_offset1 + j*step1;
//        var2[j*no_of_iter2+k] = first_offset2 + k*step2;
//      }
//    }
////    gDirectory->pwd();
//    TGraph2D *graph = new TGraph2D(npoints2d,var1,var2,chi);
//    graph->GetXaxis()->SetTitle("z shift");
//    graph->GetYaxis()->SetTitle("x shift");
//    graph->Write();

  // one dimensional shifts/rotations
//    first_offset1 = 0;
//    step1 = 0;
//    no_of_iter1 = 1;
//
//    const int npoints = no_of_iter1;
//    double var[npoints], chisq[npoints];
//
//
//    //d1d2 -> fit_in_3d();
//    //std::cout << "ok1" << std::endl;
//    //d1d2 -> get_mean_chisq();
//    //std::cout << "ok1" << std::endl;
//
//    d1d2 -> shiftD2(0.0409,0,0,1);
//    d1d2 -> shiftD2(0,0,2.42,1);
//    d1d2 -> shiftD2(0,-0.37,0,1);
//    d1d2 -> shiftD2(0,0,0.01,1);
//    d1d2 -> rotateD2(0, -0.004, 0);
//    d1d2 -> rotateD2(0.112,0 , 0);
//    //d1d2 -> rotateD2(0 ,0 , 0.013);
//
//
//    for (int j = 0; j < no_of_iter1; j++)
//    {
//      if (j%10 == 0) { std::cout << j << " out of " << no_of_iter1 << " done " << std::endl; }
//      if (j==0) off1 = first_offset1;
//      else off1 = step1;
//      //d1d2 -> shiftD2(0,0,off1,1);
//      //d1d2 -> rotateD2(off1, 0, 0);
//      d1d2 -> fit_in_3d();
//      chisq[j] = d1d2 -> get_mean_chisq();
//      var1[j] = first_offset1 + j*step1;
//
//    }

//    TCanvas *fitcanvas = new TCanvas("#chi^{2}","#chi^{2}",500,500);
//    TGraph *graph1d = new TGraph(npoints,var1,chisq);
//    TF1 *parabola = new TF1("parabola","[0]*x*x+[1]*x+[2]", first_offset1, first_offset1 + no_of_iter1*step1);
//    parabola->SetParName(0,"a");
//    parabola->SetParName(1,"b");
//    parabola->SetParName(2,"c");
//    double a, b, shift;
//    graph1d->SetMarkerStyle(20);
//    graph1d->Fit("parabola");
//    a = parabola->GetParameter(0);
//    b = parabola->GetParameter(1);
//    shift = -b/(2*a);
//    std::cout << shift << std::endl;
//    graph1d->Draw();
//    fitcanvas->Write(argv[1]);

//    d1d2 -> draw_chambers(0);
//    d1d2 -> calibrate_wires_HEX();
//    d1d2->fill_histos();
//    d1d2->save_histos();


//    // in D1D2Reconstruction offsets for y and for x/z work differently. y is set on hit functions, x/z are set on data
//    // therefore - y there should be given an absolute value of shift (not a change)
//    d1d2_reco -> tell_no_of_events();
//    double offset[20], chisq[20], off, chi,first_offset, step;
//    int no_of_iter;
//    no_of_iter = 20;
//    first_offset = -1;
//    step = 0.1;
//    d1d2_reco -> set_x_offset(0);
//    for (int i = 0; i < no_of_iter; i++)
//    {
//      std::cout << "offset determination... " << i + 1 << " out of " << no_of_iter << " done" << std::endl;
//      if (i==0) off = first_offset;
//      else off = step;
//      //else off += step;
//      d1d2_reco -> set_z_offset(off);
//      //d1d2_reco -> fit_in_3d_D1();
//      //d1d2_reco -> fit_in_3d_D2();
//      //d1d2_reco -> set_y_offset(off);
//      d1d2_reco -> fit();
//      //d1d2_reco -> plot_D1_d2_phi_corr();
//      //d1d2_reco -> save_histos();
//      d1d2_reco -> deletations();
//      chi = d1d2_reco -> get_mean_chisq();
//      offset[i] = first_offset+i*step;
//      chisq[i] = chi;
//    }
//    TGraph *graph = new TGraph(no_of_iter,offset,chisq);
//    //graph -> Draw("AP");
//    graph->Write();

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

//    calibration_HEX -> tell_no_of_events();
//    calibration_HEX -> set_no_of_bin_in_event();
//
//    for (int i = 0; i < 10; i++)
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