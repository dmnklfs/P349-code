#include "P349_data.h"

ClassImp(P349_data)

P349_data::P349_data(){
   globalchan = -1;
   trb = -1;
   tdc = -1;
   chan = -1;
   edge = -1;
   realtime = -1;
   tottime = -1; 
   detector = -1;
   detectorlayer = -1;
   layerelement = -1;
 
}

P349_data::P349_data(int cglobalchan, int ctrb, int ctdc, int cchan, int cedge, double crealtime, double ctottime, int cdetector, int cdetectorlayer, int clayerelement):globalchan(cglobalchan), trb(ctrb), tdc(ctdc), chan(cchan), edge(cedge), realtime(crealtime), tottime(ctottime), detector(cdetector), detectorlayer(cdetectorlayer), layerelement(clayerelement)  {
  
}

P349_data::P349_data(int cglobalchan, int ctrb, int ctdc, int cchan, double crealtime, double ctottime, int cdetector, int cdetectorlayer, int clayerelement):globalchan(cglobalchan), trb(ctrb), tdc(ctdc), chan(cchan), realtime(crealtime), tottime(ctottime), detector(cdetector), detectorlayer(cdetectorlayer), layerelement(clayerelement)  {
  
  edge = -1;
}




P349_data::P349_data(P349_data const &other)
{
    copy(other);
}

P349_data &P349_data::operator=(P349_data const &other)
{
    if (this != &other)
    {
	destroy();
	copy(other);
    }
    return *this;
}

void P349_data::copy(P349_data const &other)
{
    
   globalchan 	  = other.globalchan; 
   trb  	  = other.trb;       
   tdc 		  = other.tdc;       
   chan 	  = other.chan; 
   edge 	  = other.edge;   
   realtime  	  = other.realtime;   
   tottime  	  = other.tottime;    
   detector       = other.detector;      
   detectorlayer  = other.detectorlayer;   
   layerelement   = other.layerelement;   
  
}


void P349_data::destroy()
{
   
}