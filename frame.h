#ifndef FRAME_H
#define FRAME_H

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TMinuit.h"
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TGaxis.h>
#include <TF1.h>
#include <Math/Factory.h>
#include <Math/Functor.h>
#include <numeric>
#include <boost/filesystem.hpp>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "struct.h"
#include "Tree.h"
#include "SingleEvent.h" 

#define START 1
#define NTOF 10
#define ND1 6
#define ND2 5

bool check_input(int argc, char *argv[])
{
	if (argc < 8 || atoi(argv[2]) > 2 || atoi(argv[2]) < 0 || atoi(argv[3]) < -1 || atoi(argv[4]) < 0 || atoi(argv[4]) > 1 || atoi(argv[5]) < 0 || atoi(argv[5]) > 1 )
	{
		std::cout << "\n" << std::endl;
		std::cout << "Wrong input!!!" << std::endl;
		std::cout << "Minimal info: " << argv[0] << " <OutputFileName> <analysis stage> <no_of_events_to_process> <rough data tree> <preselected data tree> <path/data_file_1.root> ... <path/data_file_N.root> <path_to_tree>" << std::endl;
		std::cout << "* analysis stage defines the moment from wchich the data set is read and analysed:"<< std::endl;
		std::cout << "    1 - read data and make preselection (test conditions from CONFIG)"<< std::endl;
		std::cout << "    2 - read preselected data (without testing conditions from CONFIG)"<< std::endl;
		std::cout << "* if you want to process all events in the files set no of events to -1"<< std::endl;
		std::cout << "* you can analyse any number of the *.root files provided they have the same structure"<< std::endl;
		std::cout << "\n" << std::endl;
		return false;
	}
	else
	{
		// choice of the stage
		std::cout << "\n" << std::endl;
		if (std::atoi(argv[2])==1)
		{
			std::cout << "* data will be checked according to the conditions from CONFIG" << std::endl;
		}
		if (std::atoi(argv[2])==2)
		{
			std::cout << "* preselected data (no check)" << std::endl;
		}
		return true;
	}
}




#endif