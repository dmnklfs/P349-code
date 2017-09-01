CC=g++ -std=c++0x
CFLAGS=-c -Wall -pthread -m64 -fPIC -I$(shell root-config --incdir) -I$(shell root-config --cflags) -lMinuit -lgslcblas -lm -lgsl
# CFLAGS=-c -Wall -pthread -m64 -I$(shell root-config --incdir)
LDFLAGS= -Wl,--no-as-needed -Wall $(shell root-config --libs) -m64 -lboost_system -lboost_filesystem -lMinuit
SOURCES= MinuitFit.cpp LineFit.cpp LineFit_D2.cpp LineFit_HEX.cpp UncorrelatedOpt.cpp Calibration3d.cpp Calibration3d_D2.cpp Calibration3d_HEX.cpp CalibrationLayer3d.cpp CalibrationLayer3d_D2.cpp CalibrationLayer3d_HEX.cpp Calibration2d.cpp CalibrationLayer2d.cpp SimpleCalibration.cpp Config.cpp main.cpp  Tree.cpp Start.cpp TOF.cpp Intermediate.cpp Fiber.cpp D1.cpp D2.cpp HEX.cpp DCLayer.cpp P349_data.cpp SingleEvent.cpp dictp349_data.cpp Hist.cpp EventDisplay.cpp CommonFunctions.cpp Fit3d.cpp Fit3d_D2.cpp Fit3d_HEX.cpp
# OBJECTS=easyparser_timecut.o P349_data.o  dictp349_data.o
OBJECTS=$(SOURCES:.cpp=.o) 
EXECUTABLE=test.exe
LIBP349SO=libP349_data.so

all: $(LIBP349SO) $(EXECUTABLE) 

$(LIBP349SO): P349_data.o dictp349_data.o
	$(CC) -shared $(LDFLAGS) $^ -o $@  

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.cc.o:
	$(CC) $(CFLAGS) $< -o $@
	
.cxx.o:
	$(CC) $(CFLAGS) $< -o $@
	
dictp349_data.cpp: P349_data.h P349_Linkdef.h
	rootcint -f $@ $(CFLAGS) -p $^
	 
	
clean:
	$(RM) $(OBJECTS) *~
	
	
realclean:
	$(RM) $(OBJECTS) *~
	$(RM) dictp349_data.cpp
	$(RM) $(EXECUTABLE) $(LIBP349SO)
