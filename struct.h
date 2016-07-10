#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>
#include <vector>

// in main, good hits loop
struct single_gh_data
{
	int layer, detector, element, edge;
	double treal;	
};

// structures used for detectors separately
struct start_hist_data
{
	unsigned int rough_multiplicity_up, rough_multiplicity_down; 
	unsigned int preselected_multiplicity_up, preselected_multiplicity_down; 
};

struct TOF_hist_data
{
	unsigned int rough_multiplicity_up, rough_multiplicity_down; 
	unsigned int preselected_multiplicity_up, preselected_multiplicity_down;
	std::vector<int> rough_elements_up;
	std::vector<int> rough_elements_down;
	std::vector<int> preselected_elements_up;
	std::vector<int> preselected_elements_down;
};

struct D1Layer_hist_data
{
	unsigned int rough_multiplicity; 
	unsigned int preselected_multiplicity;
	std::vector<int> rough_elements;
	std::vector<int> preselected_elements;
};

struct D1_hist_data
{
	D1Layer_hist_data layer1_data;
	D1Layer_hist_data layer2_data;
	D1Layer_hist_data layer7_data;
	D1Layer_hist_data layer8_data;
};

// structure required to fill histos by ... function
struct hist_data
{
	start_hist_data start_data;
	TOF_hist_data tof_data;
	D1_hist_data d1_data;
};

 #endif
