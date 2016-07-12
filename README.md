sample usage
------------

- on data from easyparser:
	./test.exe 2016-07-06 1 1000 1 1 xx15179020304.root Trees/calibrated

- on data from this code
	./test.exe 2016-07-10 1 1000 1 1 data_2016-07-10.root preselected


alternative compilation
-----------------------
g++ -std=c++0x -Wall `root-config --cflags` -g Tree.cpp Start.cpp TOF.cpp D1.cpp D1Layer.cpp Config.cpp P349_data.cpp SingleEvent.cpp dictp349_data.cpp Hist.cpp main.cpp -o test.exe -Wl,--no-as-needed -Wall `root-config --glibs` -lMinuit -lboost_system -lboost_filesystem
