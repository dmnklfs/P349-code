#include "SimpleCalibration.h"

SimpleCalibration::SimpleCalibration()
{  }

SimpleCalibration::SimpleCalibration(const Config &_config)
{

}


SimpleCalibration::~SimpleCalibration()
{  }

void SimpleCalibration::get_data(data_for_D1_simple_calibration _single_event_data)
{
	single_event_data data;
	for (int i = 0; i < 4; i++)
	{
		data.positionsX[i] 	= _single_event_data.positionsX[i];
		data.positionsZ[i] 	= _single_event_data.positionsZ[i];
		data.drift_times[i] 	= _single_event_data.drift_times[i];
	}
	if (_single_event_data.positionsX[0] > _single_event_data.positionsX[1])
	{
		data.left_right[0] 	= -1;
		data.left_right[1] 	= +1;
	}
	if (_single_event_data.positionsX[2] > _single_event_data.positionsX[3])
	{
		data.left_right[2] 	= -1;
		data.left_right[3] 	= +1;
	}
	data.track_a = -1;
	data.track_b = -1;
	
	CalibrationData.push_back(data);
}

void SimpleCalibration::tell_no_of_events()
{
	std::cout << CalibrationData.size() << std::endl;
}