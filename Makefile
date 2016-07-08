CC=g++ -std=c++0x
CFLAGS=-c -Wall -pthread -m32 -fPIC -I$(shell root-config --incdir) -I$(shell root-config --cflags)
# CFLAGS=-c -Wall -pthread -m64 -I$(shell root-config --incdir)
LDFLAGS= -Wl,--no-as-needed -Wall $(shell root-config --libs) -m32 -lboost_system -lboost_filesystem
SOURCES=main.cpp  Tree.cpp Start.cpp Config.cpp P349_data.cpp SingleEvent.cpp dictp349_data.cpp Hist.cpp
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