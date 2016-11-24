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

	init_start_histos_rough();
	init_tof_histos_rough();
	init_D1_histos_rough();
	//init_D2_histos_rough();
	//init_HEX_histos_rough();
	//init_fiber_histos_rough();
	//init_inter_histos_rough();

	init_start_histos_preselected();
	init_tof_histos_preselected();
	init_D1_histos_preselected();
	//init_D2_histos_preselected();
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
	// D2
	for (int i = 0; i < 6; i++)
	{
		// preselected
		temp_name = Form("D2 preselected data layer %d wires;wire;counts", i+1);
		D2_Preselected_Elements[i] = new TH1F(temp_name, temp_name, 60, -0.5, 59.5);
		temp_name = Form("D2 preselected layer %d multiplicity;multiplicity (hits: leading+trailing);counts", i+1);
		D2_Preselected_Multiplicity[i] = new TH1F(temp_name, temp_name, 15, -0.5, 14.5);
		temp_name = Form("D2 preselected layer %d drift time;drift time [ns];counts", i+1);
		D2_Preselected_DriftTime[i] = new TH1F(temp_name, temp_name, 1000, -1500, 1500);
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
		for (unsigned int i = 0; i < _tof_data->rough_elements_up.size(); i++) Hist::TOF_Rough_Layer_Up_Elements -> Fill(_tof_data->rough_elements_up.at(i));
		for (unsigned int i = 0; i < _tof_data->rough_elements_down.size(); i++) Hist::TOF_Rough_Layer_Down_Element -> Fill(_tof_data->rough_elements_down.at(i));
	}
}

void Hist::fill_TOF_histos_preselected(TOF_hist_data* _tof_data)
{
	if (tof_histos_preselected)
	{
		Hist::TOF_Preselected_Layer_Up_Multiplicity -> Fill(_tof_data->preselected_multiplicity_up);
		Hist::TOF_Preselected_Layer_Down_Multiplicity -> Fill(_tof_data->preselected_multiplicity_down);
		Hist::TOF_Mean_Time -> Fill(0.5*(_tof_data -> preselected_time_up.at(0)+_tof_data -> preselected_time_down.at(0)));
		Hist::TOF_Time_Up -> Fill(_tof_data -> preselected_time_up.at(0));
		Hist::TOF_Time_Down -> Fill(_tof_data -> preselected_time_down.at(0));
		for (unsigned int i = 0; i < _tof_data->preselected_elements_up.size(); i++) Hist::TOF_Preselected_Layer_Up_Element -> Fill(_tof_data->preselected_elements_up.at(i));
		for (unsigned int i = 0; i < _tof_data->preselected_elements_down.size(); i++) Hist::TOF_Preselected_Layer_Down_Element -> Fill(_tof_data->preselected_elements_down.at(i));
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
//			}
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
	if (D2_histos_preselected)
	{
		for (int j = 0; j < 6; j++)
		{
			for (unsigned int i = 0; i < _d2_data->layer_data[j]->preselected_elements.size(); i++)
			{
				Hist::D2_Preselected_Elements[j] -> Fill(_d2_data->layer_data[j]->preselected_elements.at(i));
				Hist::D2_Preselected_DriftTime[j] -> Fill(_d2_data->layer_data[j]->preselected_times.at(i));
			}
			Hist::D2_Preselected_Multiplicity[j] -> Fill(_d2_data->layer_data[j]->preselected_elements.size());
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
		for (int j = 0; j < 7; j++)
		{
			for (unsigned int i = 0; i < _hex_data->layer_data[j]->preselected_elements.size(); i++)
			{
				Hist::HEX_Preselected_Elements[j] -> Fill(_hex_data->layer_data[j]->preselected_elements.at(i));
				Hist::HEX_Preselected_DriftTime[j] -> Fill(_hex_data->layer_data[j]->preselected_times.at(i));
			}
			Hist::HEX_Preselected_Multiplicity[j] -> Fill(_hex_data->layer_data[j]->preselected_elements.size());
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