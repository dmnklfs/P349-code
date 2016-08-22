#ifndef D1_H
#define D1_H
#include "DCLayer.h"

#define ND1L1  8	// layer 1 is the closest one to D1
#define ND1L2  7
#define ND1L3  6
#define ND1L4  5
#define ND1L5  4 
#define ND1L6  3
#define ND1L7  2
#define ND1L8  1 // layer 8 is the closest one to TOF

class D1
	: public Config
{
public:
	D1();
	~D1();
	void fill_good_hits(single_gh_data _good_hit_data);
	D1_hist_data* get_hist_data();
	bool was_correct_event();
	int get_no_of_layers_with_hits();

private:
	DCLayer *Layer[8];
	int no_of_layers_with_hits;
	bool correct_event;
};


#endif


/*

 Double_t drift_time[200]=
    {   0.,
        0.57,   1.65,   2.92,   4.17,   5.50,   6.73,   7.99,   9.56,  10.95,  12.38,
        13.77,  15.30,  16.90,  18.40,  19.87,  21.41,  23.15,  24.88,  26.67,  28.48,
        30.43,  32.49,  34.51,  36.47,  38.79,  41.07,  43.63,  45.69,  48.34,  50.75,
        53.62,  56.20,  59.41,  62.12,  65.24,  68.00,  71.37,  74.42,  77.87,  81.14,
        84.39,  88.06,  91.83,  94.93,  98.71, 102.46, 106.49, 109.76, 113.53, 117.31,
        121.47, 125.63, 129.86, 133.69, 138.02, 142.15, 146.01, 150.79, 155.33, 158.95,
        163.32, 167.74, 172.02, 176.94, 181.20, 186.08, 190.44, 194.94, 200.26, 204.45,
        208.91, 214.19, 219.33, 222.91, 226.52, 232.61, 236.84, 242.41, 247.38, 252.20,
        256.96, 261.96, 267.76, 271.89, 276.37, 282.30, 286.93, 292.89, 297.20, 301.78,
        306.89, 312.45, 319.01, 323.51, 327.90, 332.59, 339.16, 344.18, 348.63, 353.58,
        360.13, 365.44, 370.29, 376.06, 381.62, 386.18, 391.80, 396.57, 403.66, 408.66,
        414.31, 419.32, 426.64, 430.58, 435.78, 442.43, 447.38, 453.25, 459.07, 465.33,
        471.49, 475.64, 481.98, 486.77, 493.61, 498.39, 504.73, 510.94, 516.99, 523.75,
        528.53, 534.15, 540.81, 546.22, 554.62, 560.54, 564.45, 569.75, 577.03, 582.98,
        588.37, 595.96, 599.77, 607.67, 614.47, 620.73, 626.80, 633.44, 638.77, 644.80,
        652.49, 657.29, 663.55, 671.27, 678.16, 683.26, 691.02, 697.42, 705.17, 710.42,
        716.28, 722.83, 728.67, 736.13, 741.45, 752.31, 756.16, 762.37, 769.45, 777.72,
        782.68, 787.93, 796.77, 802.82, 809.13, 813.61, 821.15, 826.70, 832.69, 836.43,
        843.59, 847.27, 854.55, 858.17, 864.54, 869.34, 871.39, 878.02, 878.86, 884.77,
        886.29, 888.54, 890.31, 894.63, 895.87, 899.98, 900.24, 901.62, 902.62

    };
    
    Double_t distance[200]=
    {   0.,
        0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5,
        1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0,
        3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.1, 4.2, 4.3, 4.4, 4.5,
        4.6, 4.7, 4.8, 4.9, 5.0, 5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9, 6.0,
        6.1, 6.2, 6.3, 6.4, 6.5, 6.6, 6.7, 6.8, 6.9, 7.0, 7.1, 7.2, 7.3, 7.4, 7.5,
        7.6, 7.7, 7.8, 7.9, 8.0, 8.1, 8.2, 8.3, 8.4, 8.5, 8.6, 8.7, 8.8, 8.9, 9.0,
        9.1, 9.2, 9.3, 9.4, 9.5, 9.6, 9.7, 9.8, 9.9,10.0,10.1,10.2,10.3,10.4,10.5,
        10.6,10.7,10.8,10.9,11.0,11.1,11.2,11.3,11.4,11.5,11.6,11.7,11.8,11.9,12.0,
        12.1,12.2,12.3,12.4,12.5,12.6,12.7,12.8,12.9,13.0,13.1,13.2,13.3,13.4,13.5,
        13.6,13.7,13.8,13.9,14.0,14.1,14.2,14.3,14.4,14.5,14.6,14.7,14.8,14.9,15.0,
        15.1,15.2,15.3,15.4,15.5,15.6,15.7,15.8,15.9,16.0,16.1,16.2,16.3,16.4,16.5,
        16.6,16.7,16.8,16.9,17.0,17.1,17.2,17.3,17.4,17.5,17.6,17.7,17.8,17.9,18.0,
        18.1,18.2,18.3,18.4,18.5,18.6,18.7,18.8,18.9,19.0,19.1,19.2,19.3,19.4,19.5,
        19.6,19.7,19.8,19.9

     };

*/
