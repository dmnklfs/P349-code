#ifndef __P349_data__
#define __P349_data__

#include <TROOT.h>
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TProfile.h>
#include <TPad.h>
#include <TError.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TGraph.h>
#include <TVector.h>
#include <TObject.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include "TLine.h"
#include "TEllipse.h"
#include "TLine.h"
#include "TAttAxis.h"
#include "TFrame.h"
#include "TAxis.h"
#include <TArrow.h>
#include "TPaveText.h"
#include "TPostScript.h"
#include "TText.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
//#include "Riostream.h"
#include <iostream>


class P349_data : public TObject{
public:
   
   P349_data();
   P349_data(int, int, int, int, int, double, double, int, int, int);
   P349_data(int, int, int, int, double, double, int, int, int);
   virtual ~P349_data() {};
   /// Copy constructor 
   P349_data(P349_data const &other);

   /// Assignment operator
   P349_data &operator=(P349_data const &other);
   
   ///Set Functions
   void SetGlobalchan(int newval)    { globalchan = newval; }
   void SetTrb(int newval)	     { trb = newval; }
   void SetTdc(int newval) 	     { tdc = newval; }   
   void SetChan(int newval) 	     { chan = newval; }
   void SetEdge(int newval) 	     { edge = newval; }
   void SetRealtime(double newval)   { realtime = newval; }
   void SetTottime(double newval)    { tottime = newval; }   
   void SetDetector(int newval)      { detector = newval; }
   void SetDetectorlayer(int newval) { detectorlayer = newval; }   
   void SetLayerelement(int newval)  { layerelement = newval; }   
   
      ///Get Functions
   int GetGlobalchan() const 	{ return globalchan; }
   int GetTrb() const 		{ return trb; }
   int GetTdc() const 		{ return tdc; }   
   int GetChan() const 		{ return chan; }
   int GetEdge() const 		{ return edge; }
   double GetRealtime() const 	{ return realtime; }
   double GetTottime() const 	{ return tottime; }   
   int GetDetector() const 	{ return detector; }
   int GetDetectorlayer() const { return detectorlayer; }   
   int GetLayerelement() const  { return layerelement; } 
   
   
   
private:
   void copy(P349_data const &other);
   void destroy();
   int globalchan; //Global Channel Number
   int trb;       //TRB Board Number
   int tdc;        //TDC Number 
   int chan;         //Channel Number
   int edge;         //Edge Marker, 1 Leading, 0 Trailing only valid for 2015+ data
   double realtime;   //Realtime
   double tottime;    //Time over Treshold
   int detector;       //Detectornumber
   int detectorlayer;   //Number of Detectorlayer
   int layerelement;   //Elementnumber
   
   
   ClassDef(P349_data,1)
};

#endif
