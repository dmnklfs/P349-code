#ifndef DCLayer_H
#define DCLayer_H

#include "Config.h"
#include "struct.h"

class DCLayer
{
public:
	DCLayer();
	DCLayer(int _layer_no, const std::vector<double> &_drift_time_offset, const std::vector<double> &_calib_time, const std::vector<double> &_calib_dist, const double _min_drift_time, const double _max_drift_time, const int _min_no, const int _max_no);
	~DCLayer();
	void fill_rough_data(single_gh_data _good_hit_data);
	DCLayer_hist_data* get_hist_data();
	bool was_correct_event();
	void calculate_distances_from_wires();

	// calibration -> niepotrzebne? potrzebne - 04.10.16
	std::vector<double> CalibrationTimes;
	std::vector<double> CalibrationDistances;

	// vector of drift times offsets
	std::vector<double> DriftTimeOffset;
	
	// after preselection
	std::vector<double> DriftTime;
	std::vector<int> Wire;
	std::vector<double> TOT;
	// vectors of distances from wire
	std::vector<double> HitsDistancesFromWires;
	// relative hits positions
	std::vector<double> RelativeXPosition;
	double RelativeZPosition;
	// absolute hits positions
	std::vector<double> AbsoluteXPosition;
	std::vector<double> AbsoluteZPosition;

	// only for the simple calibration
	std::vector<int> LeftRight;
	
	private:
	// rough data: before preselection
	std::vector<double> RoughDriftTime;
	std::vector<int> RoughWire;
	std::vector<int> RoughEdge;

	void check_hits();
	void choose_corr_leading();
	bool check_time_range(double drift_time);
	bool check_size(unsigned int preselected_data_size);

	void apply_drift_time_offset();

	void set_layer_number();

	bool correct_event;

	double min_drift_time, max_drift_time;
	int min_no, max_no;

	int layer_no;

};

#endif