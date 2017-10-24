#include "DCLayer.h"

DCLayer::DCLayer()
{ }

DCLayer::DCLayer(int _layer_no, const std::vector<double> &_drift_time_offset, const std::vector<double> &_calib_time, const std::vector<double> &_calib_dist, const std::vector<double> &_calib_err, const double _min_drift_time, const double _max_drift_time, const int _min_no, const int _max_no)
{
	DriftTimeOffset = _drift_time_offset;
	CalibrationTimes = _calib_time;
	CalibrationDistances = _calib_dist;
	CalibationError = _calib_err;
	min_drift_time = _min_drift_time;
	max_drift_time = _max_drift_time;
	min_no = _min_no;
	max_no = _max_no;
	layer_no = _layer_no;
}

DCLayer::~DCLayer()
{

}

void DCLayer::fill_rough_data(single_gh_data _good_hit_data)
{
	RoughDriftTime.push_back(_good_hit_data.treal);
	RoughWire.push_back(_good_hit_data.element);
	RoughEdge.push_back(_good_hit_data.edge);
	//std::cout << RoughEdge.back() << std::endl;
}

bool DCLayer::was_correct_event()
{
	DCLayer::check_hits();
	return correct_event;
}

void DCLayer::check_hits()
{
	// here the correct signals are chosen, do not remove it
	choose_corr_leading();
	
	if (check_size(Wire.size()))
	{
		correct_event = true;
	}
	else correct_event = false;
}

void DCLayer::choose_corr_leading()
{
	//std::cout << "ok" << std::endl;
	double first_leading_tdriff = -1;
	int iterations = RoughEdge.size();
	were_2leading = false;
	bool same_wire = false;
	int temp_wire;
	noof_leading_edges = 0;
	//std::cout << "---------------" << std::endl;
	//if (RoughEdge.size()-1 < 0) iterations = 0;
	for (int i = 0; i < iterations; i++)
	{
		/*if (1==RoughEdge.at(i))
		{
			temp_wire = RoughWire.at(i);
			noof_leading_edges++;
			if (noof_leading_edges == 0)
			if (noof_leading_edges == 1) leading1 = RoughDriftTime.at(i);
			if (noof_leading_edges > 1)
			{
				were_2leading = true;
				//std::cout << noof_leading_edges << std::endl;
			}
		}*/
		if (1==RoughEdge.at(i))//&&0==RoughEdge.at(i+1)&&RoughWire.at(i)==RoughWire.at(i+1))//&&RoughWire.at(i)>=10&&RoughWire.at(i)<=26)
		{
			//std::cout << "Wire.size() edge check " << Wire.size() << std::endl;
			//if (check_time_range(RoughDriftTime.at(i) + DriftTimeOffset.at(-1+RoughWire.at(i))))
			//{	
				//std::cout << "range ok " << std::endl;
				//if (Wire.size()==0)
				//{
					//std::cout << RoughWire.at(i) << std::endl;
					DriftTime.push_back(RoughDriftTime.at(i));//+ DriftTimeOffset.at(-1+RoughWire.at(i)));
					Wire.push_back(RoughWire.at(i));
					//TOT.push_back(RoughDriftTime.at(i+1)-RoughDriftTime.at(i));
					//leading2 = RoughDriftTime.at(i);
					//std::cout << DriftTime.size() << " " << DriftTime.at(0) << std::endl;
					//break;
					//std::cout << "Wire.size() " << Wire.size() << std::endl;
				//}
//				else
//				{
//					//std::cout << "size is not zero" << std::endl;
//					if (Wire.at(0)==RoughWire.at(i))
//					{
//						//std::cout << "equal numbers" << std::endl;
//						DriftTime.push_back(RoughDriftTime.at(i)+ DriftTimeOffset.at(-1+RoughWire.at(i)));
//						Wire.push_back(RoughWire.at(i));
//						TOT.push_back(RoughDriftTime.at(i+1)-RoughDriftTime.at(i));
//						//std::cout << "Wire.size() " << Wire.size() << std::endl;
//						//leading2 = RoughDriftTime.at(i);
//						//std::cout << DriftTime.size() << " " << DriftTime.at(0) << std::endl;
//						//break;
//						
//					}
//				}

				
			//}
		}
	}
	//std::cout << "ok1" << std::endl;
}

/*void DCLayer::choose_corr_leading()
{
	double first_leading_tdriff = -1;
	int iterations = RoughEdge.size()-1;
	bool was_leading_trailing = false;
	if (RoughEdge.size()-1 < 0) iterations = 0;
	for (int i = 0; i < iterations; i++)
	{
		if (1==RoughEdge.at(i)&&0==RoughEdge.at(i+1)&&RoughWire.at(i)==RoughWire.at(i+1))//&&RoughWire.at(i)>=10&&RoughWire.at(i)<=26)
		{
			was_leading_trailing = true;
		}
	}
	if (was_leading_trailing)
	{
		for (int i = 0; i < iterations; i++)
		{
			if (1==RoughEdge.at(i))
			{
				if (check_time_range(RoughDriftTime.at(i) + DriftTimeOffset.at(-1+RoughWire.at(i))))
				{	
					DriftTime.push_back(RoughDriftTime.at(i)+ DriftTimeOffset.at(-1+RoughWire.at(i)));
					Wire.push_back(RoughWire.at(i));
					TOT.push_back(RoughDriftTime.at(i+1)-RoughDriftTime.at(i));
					break;
				}
			}
		}	
	}
	std::cout << DriftTime.size() << " " << DriftTime.at(0) << std::endl;
}*/

bool DCLayer::check_time_range(double drift_time)
{
	if (drift_time > min_drift_time && drift_time < max_drift_time) return true;
	else return false;
}

bool DCLayer::check_size(unsigned int preselected_data_size)
{
	if (-1==min_no || -1 == max_no) return true;
	if (preselected_data_size >= (unsigned int)min_no && preselected_data_size <= (unsigned int)max_no) return true;
	else return false;
}

DCLayer_hist_data* DCLayer::get_hist_data()
{
	//std::cout << HitsDistancesFromWires.size() << std::endl;
	DCLayer_hist_data *DCLayer_data = new DCLayer_hist_data(RoughWire, Wire, RoughDriftTime, DriftTime, TOT, HitsDistancesFromWires);
	DCLayer_data -> rough_multiplicity = RoughWire.size();
	DCLayer_data -> preselected_multiplicity = Wire.size();
	DCLayer_data -> were_2leading = were_2leading;
	DCLayer_data -> leading1 = leading1;
	DCLayer_data -> leading2 = leading2;
	DCLayer_data -> noof_leading_edges = noof_leading_edges;
	return DCLayer_data;
}

void DCLayer::apply_drift_time_offset()
{
	double time;
	for (unsigned int i = 0; i < DriftTime.size(); i++)
	{
		//std::cout << "apply_drift_time_offset" << std::endl;
		//std::cout << Wire.at(i) << std::endl;
		//std::cout << "apply_drift_time_offset" << std::endl;
		time = DriftTime.at(i) + DriftTimeOffset.at(Wire.at(i)-1);
		DriftTime.at(i) = time;
		//drift_time_in_layer -> Fill(time);
	}
}

//void DCLayer::calculate_distances_from_wires()
/*{
	//std::cout << "DCLayer::calculate_distances_from_wires()" << std::endl;

	for (unsigned int i = 0; i < DriftTime.size(); i++)
	{
		double time_bin_width = max_drift_time/(CalibrationTimes.size()-1);
		double dist_bin_width = 2/(CalibrationTimes.size()-1);
		//std::cout << "drift time: " << DriftTime.at(i) << std::endl;
		double bin_no = floor(DriftTime.at(i)/time_bin_width);
		//std::cout << "bin no: " << bin_no << std::endl;
		double distance = CalibrationDistances.at(bin_no) + dist_bin_width*(CalibrationDistances.at(bin_no+1) - CalibrationDistances.at(bin_no))/(CalibrationTimes.at(bin_no+1) - CalibrationTimes.at(bin_no));
		HitsDistancesFromWires.push_back(distance);
	}
}*/

void DCLayer::calculate_distances_from_wires()
{
	int calib_bin;
	double distance;
	double drift_time;
	double t1;
	double t2;
	double x1;
	double x2;
	int no_of_calib_bins = CalibrationTimes.size() - 1; 
	for (unsigned int i = 0; i < DriftTime.size(); i++)
	{
		drift_time = DriftTime.at(i);
		//std::cout << "drift_time " << drift_time << std::endl;
		for (int j = 0; j < no_of_calib_bins; j++)
		{
			if (drift_time >= CalibrationTimes.at(j) && drift_time < CalibrationTimes.at(j+1))
			{
				calib_bin = j;
				break;
			}
		}
		t1 = CalibrationTimes.at(calib_bin);
		t2 = CalibrationTimes.at(calib_bin+1);
		x1 = CalibrationDistances.at(calib_bin);
		x2 = CalibrationDistances.at(calib_bin+1);
		distance = x1 + (x2 - x1)*(drift_time - t1)/(t2 - t1);
		HitsDistancesFromWires.push_back(distance);
		HitPositionError.push_back(CalibationError.at(calib_bin));
	}
}
