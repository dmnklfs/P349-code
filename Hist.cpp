#include "Hist.h"

Hist::Hist()
{
	start_histos_rough = false;
	start_histos_preselected = false;
	tof_histos_rough = false;
	tof_histos_preselected = false;
	D1_histos_rough = false;
	D1_histos_preselected = false;
	D2_histos_rough = false;
	D2_histos_preselected = false;
	HEX_histos_rough = false;
	HEX_histos_preselected = false;
	fiber_histos_rough = false;
	fiber_histos_preselected = false;
	inter_histos_rough = false;
	inter_histos_preselected = false;

	//init_start_histos_rough();
	//init_tof_histos_rough();
	//init_D1_histos_rough();
	//init_D2_histos_rough();
	//init_HEX_histos_rough();
	//init_fiber_histos_rough();
	//init_inter_histos_rough();

	init_start_histos_preselected();
	init_tof_histos_preselected();
	init_D1_histos_preselected();
	init_D2_histos_preselected();
	//init_HEX_histos_preselected();
	//init_fiber_histos_preselected();
	//init_inter_histos_preselected();
}

Hist::~Hist()
{
	
}

// ======================== INIT ============================================================================
void Hist::init_start_histos_rough()
{
	start_histos_rough = true;
	TString temp_name;
	START_Rough_Layer_Up_Multiplicity = new TH1F("START rough data layer up multiplicity", "START Rough layer up multiplicity;multiplicity (hits: leading+trailing);counts", 10, -0.5, 9.5);
	START_Rough_Layer_Down_Multiplicity = new TH1F("START rough data layer down multiplicity", "START Rough layer down multiplicity;multiplicity (hits: leading+trailing);counts", 10, -0.5, 9.5);
	START_event_type_up = new TH1F("START_event_type_up", "Event type in START up", 11, -0.5, 10.5);
	START_event_type_down = new TH1F("START_event_type_down", "Event type in START down", 11, -0.5, 10.5);

	// all for upper part
	// 11
	START_time_diff[0] = new TH1F("time difference_type_2", "time difference (type 3: 11);time difference;counts", 2500, 0, 500);
	// 10
	START_time_diff[1] = new TH1F("time difference_type_3", "time difference (type 2: 10);time difference;counts", 200, -20, 20);
	// 110 diff between 1(10)
	START_time_diff[2] = new TH1F("time difference_type_4_1", "time difference (type 4: 1[10]);time difference;counts", 1000, -500, 20);
	// 110 diff between 1(10)
	START_time_diff[3] = new TH1F("time difference_type_4_2", "time difference (type 4: [1]1[0]);time difference;counts", 1000, -500, 20);
	// 110 diff between (1)1(0)
	START_time_diff[4] = new TH1F("time difference_type_4_3", "time difference (type 4: [11]0);time difference;counts",  2500, 0, 500);
	// 110 diff between (10)sth
	START_time_diff[5] = new TH1F("time difference_type_5", "time difference (type 5: [10]antyhing);time difference;counts", 1000, -500, 20);
	// 110 diff between 1(10)sth
	START_time_diff[6] = new TH1F("time difference_type_6", "time difference (type 6: [1]1[0]anything);time difference;counts", 1000, -500, 20);
	// 110 diff between 1(10)sth
	START_time_diff[7] = new TH1F("time difference_type_6", "time difference (type 6: 1[10]anything);time difference;counts", 1000, -500, 20);
	// 110 diff between 1(10)sth
	//START_time_diff[6] = new TH1F("time difference_type_6", "time difference (type 6: [1]1[0]anything);time difference;counts", 1000, -500, 20);
	
}

void Hist::init_start_histos_preselected()
{
	start_histos_preselected = true;
	TString temp_name;
	START_Preselected_Layer_Up_Multiplicity = new TH1F("START preselected data layer up multiplicity", "START preselected layer up multiplicity;multiplicity (hits: leading+trailing);counts", 10, -0.5, 9.5);
	START_Preselected_Layer_Down_Multiplicity = new TH1F("START preselected data layer down multiplicity", "START preselected layer down multiplicity;multiplicity (hits: leading+trailing);counts", 10, -0.5, 9.5);
	START_Mean_Time = new TH1F("start_mean", "START mean time 0.5*(timeUp-timeDown)", 20000, -100, 1200);
	START_Time_Up 	= new TH1F("start_time_up", "START time timeUp)", 20000, -100, 1200);
	START_Time_Down = new TH1F("start_time_down", "START time timeDown)", 20000, -100, 1200);
}

void Hist::init_tof_histos_rough()
{
	tof_histos_rough = true;
	TString temp_name;
	TOF_Rough_Layer_Up_Multiplicity = new TH1F("TOF rough data layer up multiplicity", "TOF rough layer up multiplicity;multiplicity (hits: leading+trailing);counts", 12, -0.5, 11.5);
	TOF_Rough_Layer_Down_Multiplicity = new TH1F("TOF rough data layer down multiplicity", "TOF rough layer down multiplicity;multiplicity (hits: leading+trailing);counts", 12, -0.5, 11.5);
	TOF_Rough_Layer_Up_Elements = new TH1F("TOF rough data layer up element", "TOF rough layer up element;element;counts", 15, -0.5, 14.5);
	TOF_Rough_Layer_Down_Element = new TH1F("TOF rough data layer down element", "TOF rough layer down element;element;counts", 15, -0.5, 14.5);
}

void Hist::init_tof_histos_preselected()
{
	tof_histos_preselected = true;
	TString temp_name;
	TOF_Preselected_Layer_Up_Multiplicity = new TH1F("TOF preselected data layer up multiplicity", "TOF preselected layer up multiplicity;multiplicity (hits: leading+trailing);counts", 12, -0.5, 11.5);
	TOF_Preselected_Layer_Down_Multiplicity = new TH1F("TOF preselected data layer down multiplicity", "TOF preselected layer down multiplicity;multiplicity (hits: leading+trailing);counts", 12, -0.5, 11.5);
	TOF_Preselected_Layer_Up_Element = new TH1F("TOF preselected data layer up element", "TOF preselected layer up element;element;counts", 15, -0.5, 14.5);
	TOF_Preselected_Layer_Down_Element = new TH1F("TOF preselected data layer down element", "TOF preselected layer down element;element;counts", 15, -0.5, 14.5);
	TOF_Mean_Time 	= new TH1F("tof_mean", "TOF mean time 0.5*(timeUp-timeDown)", 20000, -400, 700);
	TOF_Time_Up 	= new TH1F("tof_time_up", "TOF time timeUp)", 20000, -400, 700);
	TOF_Time_Down 	= new TH1F("tof_time_down", "TOF time timeDown)", 20000, -400, 700);
	TOF_Rough_Elements_When8_Up = new TH1F("TOF_elements_up", "TOF up elements;element no. type;counts", 15, -0.5, 14.5);
	TOF_Rough_Elements_When8_Down = new TH1F("TOF_elements_down", "TOF down elements;element no. type;counts", 15, -0.5, 14.5);
	TOF_Rough_Multiplicity_When8_Up = new TH1F("TOF_multiplicity_up", "TOF up multiplicity;multiplicity;counts", 20, -0.5, 19.5);
	TOF_Rough_Multiplicity_When8_Down = new TH1F("TOF_elmultiplicity_down", "TOF down elmultiplicity;multiplicity;counts", 20, -0.5, 19.5);
}

void Hist::init_D1_histos_rough()
{
	D1_histos_rough = true;
	TString temp_name;
	// D1
	for (int i = 0; i < 8; i++)
	{
		// rough
		temp_name = Form("D1 rough data layer %d wires;wire;counts", i+1);
		D1_Rough_Elements[i] = new TH1F(temp_name, temp_name, 60, -0.5, 59.5);
		temp_name = Form("D1 rough layer %d multiplicity;multiplicity (hits: leading+trailing);counts", i+1);
		D1_Rough_Multiplicity[i] = new TH1F(temp_name, temp_name, 15, -0.5, 14.5);
		temp_name = Form("D1 rough layer %d drift time;drift time [ns];counts", i+1);
		D1_Rough_DriftTime[i] = new TH1F(temp_name, temp_name, 1000, -1500, 1500);
	}
}

void Hist::init_D1_histos_preselected()
{
	D1_histos_preselected = true;
	TString temp_name;
	temp_name = Form("D1 #mu_{planes};counts;#mu_{planes}",0);
	D1_no_of_planes = new TH1F(temp_name, temp_name, 10, -0.5, 9.5);
	temp_name = Form("D1 #mu_{cells};counts;#mu_{cells}",0);
	D1_no_of_cells = new TH1F(temp_name, temp_name, 36, -0.5, 35.5);
	temp_name = Form("D1 #mu_{cells} vs. #mu_{planes};#mu_{cells};#mu_{planes}",0);
	D1_no_planes_vs_cells = new TH2F(temp_name, temp_name, 36, -0.5, 35.5, 10, -0.5, 9.5);
	// D1
	for (int i = 0; i < 8; i++)
	{
		// preselected
		temp_name = Form("D1 preselected data layer %d wires;wire;counts", i+1);
		D1_Preselected_Elements[i] = new TH1F(temp_name, temp_name, 60, -0.5, 59.5);
		temp_name = Form("D1 preselected layer %d multiplicity;multiplicity (hits: leading+trailing);counts", i+1);
		D1_Preselected_Multiplicity[i] = new TH1F(temp_name, temp_name, 15, -0.5, 14.5);
		temp_name = Form("D1 preselected layer %d drift time;drift time [ns];counts", i+1);
		D1_Preselected_DriftTime[i] = new TH1F(temp_name, temp_name, 1000, -1500, 1500);

		for (int j = 0; j < 42; j++)
		{
		//	temp_name = Form("D1ChannelMultiplicityL%dW%d", i,j);
		//	D1_channel_multiplicities[i][j] = new TH1F(temp_name, temp_name, 11, -0.5, 10.5);
			temp_name = Form("D1DriftTimeL%dW%d", i+1,j+1);
			D1_wires_offsets[i][j] = new TH1F(temp_name,temp_name,400,-400,800);
		}

		if (0==i) // correlations - now - only for layes 1-2 and 7-8
		{
			for (int j = 0; j < 42; j++) // wires from layer 1/7
			{
				for (int k = 0; k < 2; k++) // left/right in 2/8
				{
					temp_name = Form("D1L%dW%dL%dW%d", i+1, j+1, i+2, j+k+1);
					D1_L1L2[j][k] = new TH2F(temp_name, temp_name, 100, -400, 800, 100, -400, 800);
				}
				// all layers initialized here
				//temp_name = Form("D1L%dW%d", i+1, j);
				//D1_L1[j] = new TH2F(temp_name, temp_name, 100,-400,800,100,0,300);
				//temp_name = Form("D1L%dW%d", i+2, j);
				//D1_L2[j] = new TH2F(temp_name, temp_name, 100,-400,800,100,0,300);
				//temp_name = Form("D1L%dW%d", i+7, j);
				//D1_L7[j] = new TH2F(temp_name, temp_name, 100,-400,800,100,0,300);
				//temp_name = Form("D1L%dW%d", i+8, j);
				//D1_L8[j] = new TH2F(temp_name, temp_name, 100,-400,800,100,0,300);
			}
		}
		if (6==i)
		{
			for (int j = 0; j < 42; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					temp_name = Form("D1L%dW%dL%dW%d", i+1, j+1, i+2, j+k+1);
					D1_L7L8[j][k] = new TH2F(temp_name, temp_name, 100, -400, 800, 100, -400, 800);
				}
			}
		}
	}

}

void Hist::init_D2_histos_rough()
{
	D2_histos_rough = true;
	TString temp_name;
	// D2
	for (int i = 0; i < 6; i++)
	{
		// rough
		temp_name = Form("D2 rough data layer %d wires;wire;counts", i+1);
		D2_Rough_Elements[i] = new TH1F(temp_name, temp_name, 60, -0.5, 59.5);
		temp_name = Form("D2 rough layer %d multiplicity;multiplicity (hits: leading+trailing);counts", i+1);
		D2_Rough_Multiplicity[i] = new TH1F(temp_name, temp_name, 15, -0.5, 14.5);
		temp_name = Form("D2 rough layer %d drift time;drift time [ns];counts", i+1);
		D2_Rough_DriftTime[i] = new TH1F(temp_name, temp_name, 1000, -1500, 1500);
	}

}

void Hist::init_D2_histos_preselected()
{
	D2_histos_preselected = true;
	TString temp_name;
	temp_name = Form("D2 #mu_{planes};counts;#mu_{planes}",0);
	D2_no_of_planes = new TH1F(temp_name, temp_name, 10, -0.5, 9.5);
	temp_name = Form("D2 #mu_{cells};counts;#mu_{cells}",0);
	D2_no_of_cells = new TH1F(temp_name, temp_name, 36, -0.5, 35.5);
	temp_name = Form("D2 #mu_{cells} vs. #mu_{planes};#mu_{cells};#mu_{planes}",0);
	D2_no_planes_vs_cells = new TH2F(temp_name, temp_name, 36, -0.5, 35.5, 10, -0.5, 9.5);
	// ---LAYERS---
	for (int i = 0; i < 6; i++)
	{
		// wire distribution
		temp_name = Form("D2 preselected data layer %d wires;wire;counts", i+1);
		D2_Preselected_Elements[i] = new TH1F(temp_name, temp_name, 60, -0.5, 59.5);
		// multiplicity distribution
		temp_name = Form("D2 preselected layer %d multiplicity;multiplicity (hits: leading+trailing);counts", i+1);
		D2_Preselected_Multiplicity[i] = new TH1F(temp_name, temp_name, 15, -0.5, 14.5);
		// drift time distribution
		temp_name = Form("D2 preselected layer %d drift time;drift time [ns];counts", i+1);
		D2_Preselected_DriftTime[i] = new TH1F(temp_name, temp_name, 1000, -1500, 1500);
		// ---WIRES---
		for (int j = 0; j < 42; j++)
		{
			temp_name = Form("D2DriftTimeL%dW%d", i+1,j+1);
			D2_wires_offsets[i][j] = new TH1F(temp_name,temp_name,400,-400,800);
		}
		// correlations between wires
		if (0==i) // l1l2 - inclined
		{
			for (int j = 0; j < 42; j++) // in fact: 35 wires... 42 - max no of wires in d2 detection planes
			{
				for (int k = 0; k < 2; k++) // left/right
				{
					temp_name = Form("D2L%dW%dL%dW%d", i+1, j+1, i+2, j+k+1);
					D2_L1L2[j][k] = new TH2F(temp_name, temp_name, 100, -400, 800, 100, -400, 800);
				}
			}
		}
		if (2==i) // l3l4 - inclined
		{
			for (int j = 0; j < 42; j++) 
			{
				for (int k = 0; k < 2; k++) // left/right
				{
					temp_name = Form("D2L%dW%dL%dW%d", i+1, j+1, i+2, j+k+1);
					D2_L3L4[j][k] = new TH2F(temp_name, temp_name, 100, -400, 800, 100, -400, 800);
				}
			}
		}
		if (4==i) // l5l6 - inclined
		{
			for (int j = 0; j < 42; j++) 
			{
				for (int k = 0; k < 2; k++) // left/right
				{
					temp_name = Form("D2L%dW%dL%dW%d", i+1, j+1, i+2, j+k+1);
					D2_L5L6[j][k] = new TH2F(temp_name, temp_name, 100, -400, 800, 100, -400, 800);
				}
			}
		}
	}
}

void Hist::init_HEX_histos_rough()
{
	HEX_histos_rough = true;
	TString temp_name;
	// HEX
	for (int i = 0; i < 7; i++)
	{
		// rough
		temp_name = Form("HEX rough data layer %d wires;wire;counts", i+1);
		HEX_Rough_Elements[i] = new TH1F(temp_name, temp_name, 60, -0.5, 59.5);
		temp_name = Form("HEX rough layer %d multiplicity;multiplicity (hits: leading+trailing);counts", i+1);
		HEX_Rough_Multiplicity[i] = new TH1F(temp_name, temp_name, 15, -0.5, 14.5);
		temp_name = Form("HEX rough layer %d drift time;drift time [ns];counts", i+1);
		HEX_Rough_DriftTime[i] = new TH1F(temp_name, temp_name, 1000, -1500, 1500);
	}

}

void Hist::init_HEX_histos_preselected()
{
	HEX_histos_preselected = true;
	TString temp_name;
	temp_name = Form("HEX #mu_{planes};counts;#mu_{planes}",0);
	HEX_no_of_planes = new TH1F(temp_name, temp_name, 10, -0.5, 9.5);
	temp_name = Form("HEX #mu_{cells};counts;#mu_{cells}",0);
	HEX_no_of_cells = new TH1F(temp_name, temp_name, 36, -0.5, 35.5);
	temp_name = Form("HEX #mu_{cells} vs. #mu_{planes};#mu_{cells};#mu_{planes}",0);
	HEX_no_planes_vs_cells = new TH2F(temp_name, temp_name, 36, -0.5, 35.5, 10, -0.5, 9.5);
	// HEX
	for (int i = 0; i < 7; i++)
	{
		// preselected
		temp_name = Form("HEX preselected data layer %d wires;wire;counts", i+1);
		HEX_Preselected_Elements[i] = new TH1F(temp_name, temp_name, 60, -0.5, 59.5);
		temp_name = Form("HEX preselected layer %d multiplicity;multiplicity (hits: leading+trailing);counts", i+1);
		HEX_Preselected_Multiplicity[i] = new TH1F(temp_name, temp_name, 15, -0.5, 14.5);
		temp_name = Form("HEX preselected layer %d drift time;drift time [ns];counts", i+1);
		HEX_Preselected_DriftTime[i] = new TH1F(temp_name, temp_name, 1000, -1500, 1500);
		// ---WIRES---
		for (int j = 0; j < 80; j++)
		{
			temp_name = Form("HEXriftTimeL%dW%d", i+1,j+1);
			HEX_wires_offsets[i][j] = new TH1F(temp_name,temp_name,400,-400,800);
		}
		// correlations between wires
		if (0==i) // l1l4 - straight
		{
			for (int j = 0; j < 50; j++) // in fact: 35 wires... 42 - max no of wires in d2 detection planes
			{
				for (int k = 0; k < 2; k++) // left/right
				{
					temp_name = Form("HEXL%dW%dL%dW%d", i+1, j+1, i+4, j+k+1);
					HEX_L1L4[j][k] = new TH2F(temp_name, temp_name, 100, -400, 800, 100, -400, 800);
				}
			}
		}
		if (1==i) // l2l3 - inclined
		{
			for (int j = 0; j < 50; j++) 
			{
				for (int k = 0; k < 2; k++) // left/right
				{
					temp_name = Form("HEXL%dW%dL%dW%d", i+1, j+1, i+2, j+k+1);
					HEX_L2L3[j][k] = new TH2F(temp_name, temp_name, 100, -400, 800, 100, -400, 800);
				}
			}
		}
		if (4==i) // l5l6 - inclined
		{
			for (int j = 0; j < 50; j++) 
			{
				for (int k = 0; k < 2; k++) // left/right
				{
					temp_name = Form("HEXL%dW%dL%dW%d", i+1, j+1, i+2, j+k+1);
					HEX_L5L6[j][k] = new TH2F(temp_name, temp_name, 100, -400, 800, 100, -400, 800);
				}
			}
		}
	}
}

void Hist::init_fiber_histos_rough()
{
	fiber_histos_rough = true;
	TString temp_name;
	// FIBER HODOSCOPE
	TString hodo_layer[3];
	hodo_layer[0] = "V";
	hodo_layer[1] = "H";
	hodo_layer[2] = "D";
	for (int i = 0; i < 3; i++)
	{
		// rough
		temp_name = Form("Fiber rough data layer " + hodo_layer[i] +" fiber;wire;counts", i);
		Fiber_Rough_Elements[i] = new TH1F(temp_name,temp_name,100, -0.5, 99.5);
		temp_name = Form("Fiber rough data layer " + hodo_layer[i] +" multiplicity;multiplicity (hits: leading+trailing);counts", i+1);
		Fiber_Rough_Multiplicity[i] = new TH1F(temp_name,temp_name,30,-0.5,29.5);	
	}
}

void Hist::init_fiber_histos_preselected()
{
	fiber_histos_preselected = true;
	TString temp_name;
	// FIBER HODOSCOPE
	TString hodo_layer[3];
	hodo_layer[0] = "V";
	hodo_layer[1] = "H";
	hodo_layer[2] = "D";
	for (int i = 0; i < 3; i++)
	{

		temp_name = Form("Fiber preselected data layer " + hodo_layer[i] +" fiber;wire;counts", i);
		Fiber_Preselected_Elements[i] = new TH1F(temp_name,temp_name,100, -0.5, 99.5);
		temp_name = Form("Fiber preselected data layer " + hodo_layer[i] +" multiplicity;multiplicity (hits: leading+trailing);counts", i+1);
		Fiber_Preselected_Multiplicity[i] = new TH1F(temp_name,temp_name,30,-0.5,29.5);	
	}

	V_vs_H = new TH2F("V vs H","V vs H;fiber no. layer V;fiber no. layer H",100,-0.5,99.5,100,-0.5,99.5);

}

void Hist::init_inter_histos_rough()
{
	inter_histos_rough = true;
	TString temp_name;
	Intermediate_Rough_Layer_Up_Multiplicity = new TH1F("Intermediate rough data layer up multiplicity", "Intermediate rough layer up multiplicity;multiplicity (hits: leading+trailing);counts", 18, -0.5, 17.5);
	Intermediate_Rough_Layer_Down_Multiplicity = new TH1F("Intermediate rough data layer down multiplicity", "Intermediate rough layer down multiplicity;multiplicity (hits: leading+trailing);counts", 18, -0.5, 17.5);
	Intermediate_Rough_Layer_Up_Elements = new TH1F("Intermediate rough data layer up element", "Intermediate rough layer up element;element;counts", 18, -0.5, 17.5);
	Intermediate_Rough_Layer_Down_Element = new TH1F("Intermediate rough data layer down element", "Intermediate rough layer down element;element;counts", 18, -0.5, 17.5);
	
}

void Hist::init_inter_histos_preselected()
{
	inter_histos_preselected = true;
	TString temp_name;
	Intermediate_Preselected_Layer_Up_Multiplicity = new TH1F("Intermediate preselected data layer up multiplicity", "Intermediate preselected layer up multiplicity;multiplicity (hits: leading+trailing);counts", 18, -0.5, 17.5);
	Intermediate_Preselected_Layer_Down_Multiplicity = new TH1F("Intermediate preselected data layer down multiplicity", "Intermediate preselected layer down multiplicity;multiplicity (hits: leading+trailing);counts", 18, -0.5, 17.5);
	Intermediate_Preselected_Layer_Up_Element = new TH1F("Intermediate preselected data layer up element", "Intermediate preselected layer up element;element;counts", 18, -0.5, 17.5);
	Intermediate_Preselected_Layer_Down_Element = new TH1F("Intermediate preselected data layer down element", "Intermediate preselected layer down element;element;counts", 18, -0.5, 17.5);
}

// ======================== FILLING =========================================================================
void Hist::fill_start_histos_rough(start_hist_data* _start_data)
{
	if (start_histos_rough)
	{
		Hist::START_Rough_Layer_Up_Multiplicity -> Fill(_start_data -> rough_multiplicity_up);
		Hist::START_Rough_Layer_Down_Multiplicity -> Fill(_start_data -> rough_multiplicity_down);
		/*std::cout << _start_data -> rough_elements_up.size() << std::endl;
		for (int i = 0; i < _start_data -> rough_elements_up.size(); i++)
		{
			std::cout << " " << _start_data -> rough_elements_up.at(i) << std::endl;
		}*/
		if (_start_data -> rough_elements_up.size() == 1)
		{
			if (_start_data -> rough_elements_up.at(0)==1) START_event_type_up -> Fill(1);
			if (_start_data -> rough_elements_up.at(0)==0) START_event_type_up -> Fill(0);

		}
		if (_start_data -> rough_elements_up.size() == 2)
		{
			// 10 - type 2
			if (_start_data -> rough_elements_up.at(0)==1&&_start_data -> rough_elements_up.at(1)==0)
			{
				START_event_type_up -> Fill(2);
				START_time_diff[1] -> Fill(_start_data -> rough_time_up.at(1) - _start_data -> rough_time_up.at(0));
			}
			// 11 - type 3
			if (_start_data -> rough_elements_up.at(0)==1&&_start_data -> rough_elements_up.at(1)==1)
			{
				START_event_type_up -> Fill(3);
				START_time_diff[0] -> Fill(_start_data -> rough_time_up.at(1) - _start_data -> rough_time_up.at(0));
			}
		}
		if (_start_data -> rough_elements_up.size() == 3)
		{
			if (_start_data -> rough_elements_up.at(0)==1&&_start_data -> rough_elements_up.at(1)==1&&_start_data -> rough_elements_up.at(2)==0)
			{
				START_event_type_up -> Fill(4);
				START_time_diff[2] -> Fill(_start_data -> rough_time_up.at(2) - _start_data -> rough_time_up.at(1));
				START_time_diff[3] -> Fill(_start_data -> rough_time_up.at(2) - _start_data -> rough_time_up.at(0));
				START_time_diff[4] -> Fill(_start_data -> rough_time_up.at(1) - _start_data -> rough_time_up.at(0));
			}
		}
		if (_start_data -> rough_elements_up.size() > 2)
		{
			if (_start_data -> rough_elements_up.at(0)==1&&_start_data -> rough_elements_up.at(1)==0)
			{
				START_event_type_up -> Fill(5);
				START_time_diff[5] -> Fill(_start_data -> rough_time_up.at(1) - _start_data -> rough_time_up.at(0));
			}
		}
		if (_start_data -> rough_elements_up.size() > 3)
		{
			if (_start_data -> rough_elements_up.at(0)==1&&_start_data -> rough_elements_up.at(1)==1&&_start_data -> rough_elements_up.at(2)==0)
			{
				START_event_type_up -> Fill(6);
				START_time_diff[6] -> Fill(_start_data -> rough_time_up.at(2) - _start_data -> rough_time_up.at(0));
			}
		}
		if (_start_data -> rough_elements_up.size() > 3) START_event_type_up -> Fill(7);
		// ---------------------------------------------------------------------------------
		if (_start_data -> rough_elements_down.size() == 1)
		{
			if (_start_data -> rough_elements_down.at(0)==1) START_event_type_down -> Fill(1);
			if (_start_data -> rough_elements_down.at(0)==0) START_event_type_down -> Fill(0);

		}
		if (_start_data -> rough_elements_down.size() == 2)
		{
			if (_start_data -> rough_elements_down.at(0)==1&&_start_data -> rough_elements_down.at(1)==0) START_event_type_down -> Fill(2);
			if (_start_data -> rough_elements_down.at(0)==1&&_start_data -> rough_elements_down.at(1)==1) START_event_type_down -> Fill(3);
		}
		if (_start_data -> rough_elements_down.size() == 3)
		{
			if (_start_data -> rough_elements_down.at(0)==1&&_start_data -> rough_elements_down.at(1)==1&&_start_data -> rough_elements_down.at(2)==0) START_event_type_down -> Fill(4);
		}
		if (_start_data -> rough_elements_down.size() > 2)
		{
			if (_start_data -> rough_elements_down.at(0)==1&&_start_data -> rough_elements_down.at(1)==0) START_event_type_down -> Fill(5);
		}
		if (_start_data -> rough_elements_down.size() > 3)
		{
			if (_start_data -> rough_elements_down.at(0)==1&&_start_data -> rough_elements_down.at(1)==1&&_start_data -> rough_elements_down.at(2)==0) START_event_type_down -> Fill(6);
		}
		if (_start_data -> rough_elements_down.size() > 3) START_event_type_down -> Fill(7);
	}
}

void Hist::fill_start_histos_preselected(start_hist_data* _start_data)
{
	if (start_histos_preselected)
	{
		Hist::START_Preselected_Layer_Up_Multiplicity -> Fill(_start_data -> preselected_multiplicity_up);
		Hist::START_Preselected_Layer_Down_Multiplicity -> Fill(_start_data -> preselected_multiplicity_down);
		Hist::START_Mean_Time -> Fill(0.5*(_start_data -> preselected_time_up.at(0)+_start_data -> preselected_time_down.at(0)));
		Hist::START_Time_Up -> Fill(_start_data -> preselected_time_up.at(0));
		Hist::START_Time_Down -> Fill(_start_data -> preselected_time_down.at(0));
	}
}

void Hist::fill_TOF_histos_rough(TOF_hist_data* _tof_data)
{
	if (tof_histos_rough)
	{
		Hist::TOF_Rough_Layer_Up_Multiplicity -> Fill(_tof_data->rough_multiplicity_up);
		Hist::TOF_Rough_Layer_Down_Multiplicity -> Fill(_tof_data->rough_multiplicity_down);
		for (unsigned int i = 0; i < _tof_data->rough_elements_up.size(); i++)
		{
			Hist::TOF_Rough_Layer_Up_Elements -> Fill(_tof_data->rough_elements_up.at(i));
		}
		for (unsigned int i = 0; i < _tof_data->rough_elements_down.size(); i++)
		{
			Hist::TOF_Rough_Layer_Down_Element -> Fill(_tof_data->rough_elements_down.at(i));
		}
	}
}

void Hist::fill_TOF_histos_preselected(TOF_hist_data* _tof_data)
{

	int el_no = 8;
	bool was_el_up, was_el_down;
	was_el_up = false;
	was_el_down = false;
	if (tof_histos_preselected)
	{
		Hist::TOF_Preselected_Layer_Up_Multiplicity -> Fill(_tof_data->preselected_multiplicity_up);
		Hist::TOF_Preselected_Layer_Down_Multiplicity -> Fill(_tof_data->preselected_multiplicity_down);
		//Hist::TOF_Mean_Time -> Fill(0.5*(_tof_data -> preselected_time_up.at(0)+_tof_data -> preselected_time_down.at(0)));
		//Hist::TOF_Time_Up -> Fill(_tof_data -> preselected_time_up.at(0));
		//Hist::TOF_Time_Down -> Fill(_tof_data -> preselected_time_down.at(0));
		for (unsigned int i = 0; i < _tof_data->preselected_elements_up.size(); i++)
		{
			Hist::TOF_Preselected_Layer_Up_Element -> Fill(_tof_data->preselected_elements_up.at(i));
			if (_tof_data->preselected_elements_up.at(i) == el_no) was_el_up = true;
		} 
		for (unsigned int i = 0; i < _tof_data->preselected_elements_down.size(); i++)
		{
			Hist::TOF_Preselected_Layer_Down_Element -> Fill(_tof_data->preselected_elements_down.at(i));
			if (_tof_data->preselected_elements_down.at(i) == el_no) was_el_down = true;
		} 
		//if (_tof_data->preselected_elements_up.size() > 0) Hist::TOF_Preselected_Layer_Up_Element -> Fill(_tof_data->preselected_elements_up.at(0));
		//if (_tof_data->preselected_elements_down.size() > 0) Hist::TOF_Preselected_Layer_Down_Element -> Fill(_tof_data->preselected_elements_down.at(0));
	
		// delme
		if (was_el_up)
		{
			was_el_up = false;
			TOF_Rough_Multiplicity_When8_Up -> Fill(_tof_data->preselected_multiplicity_up);
			for (unsigned int i = 0; i < _tof_data->preselected_elements_up.size(); i++)
			{
				if (_tof_data->preselected_elements_up.at(i) == el_no && was_el_up == false) was_el_up = true;
				if (_tof_data->preselected_elements_up.at(i) == el_no && was_el_up == true) TOF_Rough_Elements_When8_Up -> Fill(_tof_data->preselected_elements_up.at(i));
				if (_tof_data->preselected_elements_up.at(i) != el_no) TOF_Rough_Elements_When8_Up -> Fill(_tof_data->preselected_elements_up.at(i));
			}	
		}
		if (was_el_down)
		{
			TOF_Rough_Multiplicity_When8_Down -> Fill(_tof_data->preselected_multiplicity_down);
			was_el_down = false;
			for (unsigned int i = 0; i < _tof_data->preselected_elements_down.size(); i++)
			{
				if (_tof_data->preselected_elements_down.at(i) == el_no && was_el_down == false) was_el_down = true;
				if (_tof_data->preselected_elements_down.at(i) == el_no && was_el_down == true) TOF_Rough_Elements_When8_Down -> Fill(_tof_data->preselected_elements_down.at(i));
				if (_tof_data->preselected_elements_down.at(i) != el_no) TOF_Rough_Elements_When8_Down -> Fill(_tof_data->preselected_elements_down.at(i));
			}	
		}
	}
}

void Hist::fill_Intermediate_histos_rough(TOF_hist_data* _intermediate_data)
{
	if (inter_histos_rough)
	{
		Hist::Intermediate_Rough_Layer_Up_Multiplicity -> Fill(_intermediate_data->rough_multiplicity_up);
		Hist::Intermediate_Rough_Layer_Down_Multiplicity -> Fill(_intermediate_data->rough_multiplicity_down);
		for (unsigned int i = 0; i < _intermediate_data->rough_elements_up.size(); i++) Hist::Intermediate_Rough_Layer_Up_Elements -> Fill(_intermediate_data->rough_elements_up.at(i));
		for (unsigned int i = 0; i < _intermediate_data->rough_elements_down.size(); i++) Hist::Intermediate_Rough_Layer_Down_Element -> Fill(_intermediate_data->rough_elements_down.at(i));
	}
}

void Hist::fill_Intermediate_histos_preselected(TOF_hist_data* _intermediate_data)
{
	if (inter_histos_preselected)
	{
		Hist::Intermediate_Preselected_Layer_Up_Multiplicity -> Fill(_intermediate_data->preselected_multiplicity_up);
		Hist::Intermediate_Preselected_Layer_Down_Multiplicity -> Fill(_intermediate_data->preselected_multiplicity_down);
		for (unsigned int i = 0; i < _intermediate_data->preselected_elements_up.size(); i++) Hist::Intermediate_Preselected_Layer_Up_Element -> Fill(_intermediate_data->preselected_elements_up.at(i));
		for (unsigned int i = 0; i < _intermediate_data->preselected_elements_down.size(); i++) Hist::Intermediate_Preselected_Layer_Down_Element -> Fill(_intermediate_data->preselected_elements_down.at(i));
	}
}

void Hist::fill_D1_histos_rough(D1_hist_data* _d1_data)
{
	if (D1_histos_rough)
	{
		for (int j = 0; j < 8; j++)
		{
			for (unsigned int i = 0; i < _d1_data->layer_data[j]->rough_elements.size(); i++)
			{
				Hist::D1_Rough_Elements[j] -> Fill(_d1_data->layer_data[j]->rough_elements.at(i));
				Hist::D1_Rough_DriftTime[j] -> Fill(_d1_data->layer_data[j]->rough_times.at(i));
			}
			Hist::D1_Rough_Multiplicity[j] -> Fill(_d1_data->layer_data[j]->rough_elements.size());
		}
	}
}

void Hist::fill_D1_histos_preselected(D1_hist_data* _d1_data)
{
	if (D1_histos_preselected)
	{
		int wire1, wire2;
		Float_t time1, time2, tot;
		double multiplicities[42];
		D1_no_of_planes -> Fill(_d1_data->D1_no_of_planes_with_hits);
		D1_no_of_cells -> Fill(_d1_data->D1_no_of_cells_with_hits);
		D1_no_planes_vs_cells -> Fill(_d1_data->D1_no_of_cells_with_hits,_d1_data->D1_no_of_planes_with_hits);
		for (int j = 0; j < 8; j++)
		{
			for (unsigned int i = 0; i < _d1_data->layer_data[j]->preselected_elements.size(); i++)
			{
				Hist::D1_Preselected_Elements[j] -> Fill(_d1_data->layer_data[j]->preselected_elements.at(i));
				Hist::D1_Preselected_DriftTime[j] -> Fill(_d1_data->layer_data[j]->preselected_times.at(i));

				wire1 = _d1_data->layer_data[j]->preselected_elements.at(i)-1;
				time1 = _d1_data->layer_data[j]->preselected_times.at(i);
				D1_wires_offsets[j][wire1] -> Fill(time1);
			}
			Hist::D1_Preselected_Multiplicity[j] -> Fill(_d1_data->layer_data[j]->preselected_elements.size());

//			for (int i = 0; i < 42; i++) multiplicities[i] = 0;
//	
//			for (int i = 0; i < _d1_data->layer_data[j]->preselected_elements.size(); i++)
//			{
//				wire1 = _d1_data->layer_data[j] -> preselected_elements.at(i)-1;
//				multiplicities[wire1]++;
//			}
//	
//			for (int i = 0; i < 42; i++) D1_channel_multiplicities[j][i] -> Fill(multiplicities[i]);

			// correlation histograms are filled in
			if (0==j)
			{
				for (unsigned int i = 0; i < _d1_data->layer_data[j]->preselected_elements.size(); i++)
				{
					wire1 = _d1_data->layer_data[j]->preselected_elements.at(i)-1;
					time1 = _d1_data->layer_data[j]->preselected_times.at(i);
					//tot = _d1_data->layer_data[j]->tot.at(i);
					//D1_L1[wire1] -> Fill(time1, tot);				
					for (unsigned int k = 0; k < _d1_data->layer_data[j+1]->preselected_elements.size(); k++)
					{
						wire2 = _d1_data->layer_data[j+1]->preselected_elements.at(k)-1;
						time2 = _d1_data->layer_data[j+1]->preselected_times.at(k);	
						if (wire1>=0&&wire1<42)
						{
							if (wire2 == wire1)
							{
								Hist::D1_L1L2[wire1][0] -> Fill(time1, time2);
							}
							if (wire2 == wire1+1)
							{
								Hist::D1_L1L2[wire1][1] -> Fill(time1, time2);
							}
						}
					}
				}
			}
//			if (1==j)
//			{
//				for (unsigned int i = 0; i < _d1_data->layer_data[j]->preselected_elements.size(); i++)
//				{
//					wire1 = _d1_data->layer_data[j]->preselected_elements.at(i)-1;
//					time1 = _d1_data->layer_data[j]->preselected_times.at(i);
//					tot = _d1_data->layer_data[j]->tot.at(i);
//					D1_L2[wire1] -> Fill(time1, tot);				
//				}
//			}
			if (6==j)
			{
				//std::cout << "poczatek" << std::endl;
				for (unsigned int i = 0; i < _d1_data->layer_data[j]->preselected_elements.size(); i++)
				{
					wire1 = _d1_data->layer_data[j]->preselected_elements.at(i)-1;
					time1 = _d1_data->layer_data[j]->preselected_times.at(i);
					//tot = _d1_data->layer_data[j]->tot.at(i);
					//D1_L7[wire1] -> Fill(time1, tot);
					for (unsigned int k = 0; k < _d1_data->layer_data[j+1]->preselected_elements.size(); k++)
					{
						time2 = _d1_data->layer_data[j+1]->preselected_times.at(k);
						wire2 = _d1_data->layer_data[j+1]->preselected_elements.at(k)-1;					
						if (wire1>=0&&wire1<42)
						{
							if (wire2 == wire1)
							{
								Hist::D1_L7L8[wire1][0] -> Fill(time1, time2);
							}
							if (wire2 == wire1+1)
							{
								Hist::D1_L7L8[wire1][1] -> Fill(time1, time2);
							}
						}
					}
				}
			}
//			if (7==j)
//			{
//				for (unsigned int i = 0; i < _d1_data->layer_data[j]->preselected_elements.size(); i++)
//				{
//					wire1 = _d1_data->layer_data[j]->preselected_elements.at(i)-1;
//					time1 = _d1_data->layer_data[j]->preselected_times.at(i);
//					tot = _d1_data->layer_data[j]->tot.at(i);
//					D1_L8[wire1] -> Fill(time1, tot);				
//				}
//			} //-------------------------------
		}
	}
}

void Hist::fill_D2_histos_rough(D2_hist_data* _d2_data)
{
	if (D2_histos_rough)
	{
		for (int j = 0; j < 6; j++)
		{
			for (unsigned int i = 0; i < _d2_data->layer_data[j]->rough_elements.size(); i++)
			{
				Hist::D2_Rough_Elements[j] -> Fill(_d2_data->layer_data[j]->rough_elements.at(i));
				Hist::D2_Rough_DriftTime[j] -> Fill(_d2_data->layer_data[j]->rough_times.at(i));
			}
			Hist::D2_Rough_Multiplicity[j] -> Fill(_d2_data->layer_data[j]->rough_elements.size());
		}
	}
}

void Hist::fill_D2_histos_preselected(D2_hist_data* _d2_data)
{
	int wire1, wire2;
	Float_t time1, time2, tot;
	if (D2_histos_preselected)
	{
		D2_no_of_planes -> Fill(_d2_data->D2_no_of_planes_with_hits);
		D2_no_of_cells -> Fill(_d2_data->D2_no_of_cells_with_hits);
		D2_no_planes_vs_cells -> Fill(_d2_data->D2_no_of_cells_with_hits,_d2_data->D2_no_of_planes_with_hits);
		for (int j = 0; j < 6; j++)
		{
			for (unsigned int i = 0; i < _d2_data->layer_data[j]->preselected_elements.size(); i++)
			{
				Hist::D2_Preselected_Elements[j] -> Fill(_d2_data->layer_data[j]->preselected_elements.at(i));
				Hist::D2_Preselected_DriftTime[j] -> Fill(_d2_data->layer_data[j]->preselected_times.at(i));
				wire1 = _d2_data->layer_data[j]->preselected_elements.at(i)-1;
				time1 = _d2_data->layer_data[j]->preselected_times.at(i);
				D2_wires_offsets[j][wire1] -> Fill(time1);
			}
			Hist::D2_Preselected_Multiplicity[j] -> Fill(_d2_data->layer_data[j]->preselected_elements.size());
						// correlation histograms are filled in
			if (0==j)
			{
				for (unsigned int i = 0; i < _d2_data->layer_data[j]->preselected_elements.size(); i++)
				{
					wire1 = _d2_data->layer_data[j]->preselected_elements.at(i)-1;
					time1 = _d2_data->layer_data[j]->preselected_times.at(i);
					//tot = _d2_data->layer_data[j]->tot.at(i);
					//D1_L1[wire1] -> Fill(time1, tot);				
					for (unsigned int k = 0; k < _d2_data->layer_data[j+1]->preselected_elements.size(); k++)
					{
						wire2 = _d2_data->layer_data[j+1]->preselected_elements.at(k)-1;
						time2 = _d2_data->layer_data[j+1]->preselected_times.at(k);	
						if (wire1>=0&&wire1<42)
						{
							if (wire2 == wire1)
							{
								Hist::D2_L1L2[wire1][0] -> Fill(time1, time2);
							}
							if (wire2 == wire1+1)
							{
								Hist::D2_L1L2[wire1][1] -> Fill(time1, time2);
							}
						}
					}
				}
			}
			if (2==j)
			{
				for (unsigned int i = 0; i < _d2_data->layer_data[j]->preselected_elements.size(); i++)
				{
					wire1 = _d2_data->layer_data[j]->preselected_elements.at(i)-1;
					time1 = _d2_data->layer_data[j]->preselected_times.at(i);
					//tot = _d2_data->layer_data[j]->tot.at(i);
					//D1_L1[wire1] -> Fill(time1, tot);				
					for (unsigned int k = 0; k < _d2_data->layer_data[j+1]->preselected_elements.size(); k++)
					{
						wire2 = _d2_data->layer_data[j+1]->preselected_elements.at(k)-1;
						time2 = _d2_data->layer_data[j+1]->preselected_times.at(k);	
						if (wire1>=0&&wire1<42)
						{
							if (wire2 == wire1)
							{
								Hist::D2_L3L4[wire1][0] -> Fill(time1, time2);
							}
							if (wire2 == wire1+1)
							{
								Hist::D2_L3L4[wire1][1] -> Fill(time1, time2);
							}
						}
					}
				}
			}
			if (4==j)
			{
				for (unsigned int i = 0; i < _d2_data->layer_data[j]->preselected_elements.size(); i++)
				{
					wire1 = _d2_data->layer_data[j]->preselected_elements.at(i)-1;
					time1 = _d2_data->layer_data[j]->preselected_times.at(i);
					//tot = _d2_data->layer_data[j]->tot.at(i);
					//D1_L1[wire1] -> Fill(time1, tot);				
					for (unsigned int k = 0; k < _d2_data->layer_data[j+1]->preselected_elements.size(); k++)
					{
						wire2 = _d2_data->layer_data[j+1]->preselected_elements.at(k)-1;
						time2 = _d2_data->layer_data[j+1]->preselected_times.at(k);	
						if (wire1>=0&&wire1<42)
						{
							if (wire2 == wire1)
							{
								Hist::D2_L5L6[wire1][0] -> Fill(time1, time2);
							}
							if (wire2 == wire1+1)
							{
								Hist::D2_L5L6[wire1][1] -> Fill(time1, time2);
							}
						}
					}
				}
			}
		}
	}

}

void Hist::fill_HEX_histos_rough(HEX_hist_data* _hex_data)
{
	if (HEX_histos_rough)
	{
		for (int j = 0; j < 7; j++)
		{
			for (unsigned int i = 0; i < _hex_data->layer_data[j]->rough_elements.size(); i++)
			{
				Hist::HEX_Rough_Elements[j] -> Fill(_hex_data->layer_data[j]->rough_elements.at(i));
				Hist::HEX_Rough_DriftTime[j] -> Fill(_hex_data->layer_data[j]->rough_times.at(i));
			}
			Hist::HEX_Rough_Multiplicity[j] -> Fill(_hex_data->layer_data[j]->rough_elements.size());
		}
	}
}

void Hist::fill_HEX_histos_preselected(HEX_hist_data* _hex_data)
{
	if (HEX_histos_preselected)
	{
		int wire1, wire2;
		Float_t time1, time2, tot;
		for (int j = 0; j < 7; j++)
		{
			for (unsigned int i = 0; i < _hex_data->layer_data[j]->preselected_elements.size(); i++)
			{
				Hist::HEX_Preselected_Elements[j] -> Fill(_hex_data->layer_data[j]->preselected_elements.at(i));
				Hist::HEX_Preselected_DriftTime[j] -> Fill(_hex_data->layer_data[j]->preselected_times.at(i));
				wire1 = _hex_data->layer_data[j]->preselected_elements.at(i)-1;
				time1 = _hex_data->layer_data[j]->preselected_times.at(i);
				Hist::HEX_wires_offsets[j][wire1] -> Fill(time1);
			}
			Hist::HEX_Preselected_Multiplicity[j] -> Fill(_hex_data->layer_data[j]->preselected_elements.size());
			if (0==j) // straight 1 & 4
			{
				for (unsigned int i = 0; i < _hex_data->layer_data[j]->preselected_elements.size(); i++)
				{
					wire1 = _hex_data->layer_data[j]->preselected_elements.at(i)-1;
					time1 = _hex_data->layer_data[j]->preselected_times.at(i);		
					for (unsigned int k = 0; k < _hex_data->layer_data[j+3]->preselected_elements.size(); k++)
					{
						wire2 = _hex_data->layer_data[j+3]->preselected_elements.at(k)-1;
						time2 = _hex_data->layer_data[j+3]->preselected_times.at(k);	
						if (wire1>=0&&wire1<80)
						{
							if (wire2 == wire1)
							{
								Hist::HEX_L1L4[wire1][0] -> Fill(time1, time2);
							}
							if (wire2+1 == wire1)
							{
								Hist::HEX_L1L4[wire1][1] -> Fill(time1, time2);
							}
						}
					}
				}
			}
			if (1==j) //  
			{
				for (unsigned int i = 0; i < _hex_data->layer_data[j]->preselected_elements.size(); i++)
				{
					wire1 = _hex_data->layer_data[j]->preselected_elements.at(i)-1;
					time1 = _hex_data->layer_data[j]->preselected_times.at(i);
					//tot = _hex_data->layer_data[j]->tot.at(i);
					//D1_L1[wire1] -> Fill(time1, tot);				
					for (unsigned int k = 0; k < _hex_data->layer_data[j+1]->preselected_elements.size(); k++)
					{
						wire2 = _hex_data->layer_data[j+1]->preselected_elements.at(k)-1;
						time2 = _hex_data->layer_data[j+1]->preselected_times.at(k);	
						if (wire1>=0&&wire1<80)
						{
							if (wire2 == wire1)
							{
								Hist::HEX_L2L3[wire1][0] -> Fill(time1, time2);
							}
							if (wire2 == wire1+1)
							{
								Hist::HEX_L2L3[wire1][1] -> Fill(time1, time2);
							}
						}
					}
				}
			}
			if (4==j)
			{
				for (unsigned int i = 0; i < _hex_data->layer_data[j]->preselected_elements.size(); i++)
				{
					wire1 = _hex_data->layer_data[j]->preselected_elements.at(i)-1;
					time1 = _hex_data->layer_data[j]->preselected_times.at(i);
					//tot = _hex_data->layer_data[j]->tot.at(i);
					//D1_L1[wire1] -> Fill(time1, tot);				
					for (unsigned int k = 0; k < _hex_data->layer_data[j+1]->preselected_elements.size(); k++)
					{
						wire2 = _hex_data->layer_data[j+1]->preselected_elements.at(k)-1;
						time2 = _hex_data->layer_data[j+1]->preselected_times.at(k);	
						if (wire1>=0&&wire1<80)
						{
							if (wire2 == wire1)
							{
								Hist::HEX_L5L6[wire1][0] -> Fill(time1, time2);
							}
							if (wire2 == wire1-1)
							{
								Hist::HEX_L5L6[wire1][1] -> Fill(time1, time2);
							}
						}
					}
				}
			}
		}
	}
}

void Hist::fill_Fiber_histos_rough(Fiber_hist_data* _fiber_data)
{
	if (fiber_histos_rough)
	{
		for (unsigned int i = 0; i < _fiber_data->rough_fibers_V.size(); i++) Fiber_Rough_Elements[0] -> Fill(_fiber_data->rough_fibers_V.at(i));
		for (unsigned int i = 0; i < _fiber_data->rough_fibers_H.size(); i++) Fiber_Rough_Elements[1] -> Fill(_fiber_data->rough_fibers_H.at(i));
		for (unsigned int i = 0; i < _fiber_data->rough_fibers_D.size(); i++) Fiber_Rough_Elements[2] -> Fill(_fiber_data->rough_fibers_D.at(i));
		Fiber_Rough_Multiplicity[0] -> Fill(_fiber_data->rough_fibers_V.size());
		Fiber_Rough_Multiplicity[1] -> Fill(_fiber_data->rough_fibers_H.size());
		Fiber_Rough_Multiplicity[2] -> Fill(_fiber_data->rough_fibers_D.size());
	}
}

void Hist::fill_Fiber_histos_preselected(Fiber_hist_data* _fiber_data)
{
	if (fiber_histos_preselected)
	{
		for (unsigned int i = 0; i < _fiber_data->fibers_V.size(); i++) Fiber_Preselected_Elements[0] -> Fill(_fiber_data->fibers_V.at(i));
		for (unsigned int i = 0; i < _fiber_data->fibers_H.size(); i++) Fiber_Preselected_Elements[1] -> Fill(_fiber_data->fibers_H.at(i));
		for (unsigned int i = 0; i < _fiber_data->fibers_D.size(); i++) Fiber_Preselected_Elements[2] -> Fill(_fiber_data->fibers_D.at(i));
		Fiber_Preselected_Multiplicity[0] -> Fill(_fiber_data->fibers_V.size());
		Fiber_Preselected_Multiplicity[1] -> Fill(_fiber_data->fibers_H.size());
		Fiber_Preselected_Multiplicity[2] -> Fill(_fiber_data->fibers_D.size());
	
		for (unsigned int j = 0; j < _fiber_data->fibers_H.size(); j++)
		{
			for (unsigned int i = 0; i < _fiber_data->fibers_V.size(); i++)
			{
				V_vs_H -> Fill(_fiber_data->fibers_V.at(i), _fiber_data->fibers_H.at(j));
			}
		}
	}
}