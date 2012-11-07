// CRAHNs Model START
// @author:  Marco Di Felice



#include "SpectrumSensing.h"


// SpectrumSensing initialization: PU model off
SpectrumSensing::SpectrumSensing(SpectrumManager *sm) {
 	
	smanager_=sm;
}




// SpectrumSensing initialization: PU model on
SpectrumSensing::SpectrumSensing(SpectrumManager *sm, double prob_misdetect, PUmodel *p) {
	
	pumodel_=p;

	prob_misdetect_=prob_misdetect;

}               




// sense: return true if PU activity is detected in the time interval [current_time:current_time + sense_time]
bool
SpectrumSensing::sense(int id, double sense_time, double transmit_time, int channel) {
	
	MobileNode *pnode = (MobileNode*)Node::get_node_by_address(id);
        double x=pnode->X();
        double y=pnode->Y();
	bool cr_on=false;

	if (pumodel_) {

		double randomValue=Random::uniform();

		// Ask the PUmodel if a PU is active  in the time interval [current_time:current_time + sense_time]
		cr_on=pumodel_->is_PU_active(Scheduler::instance().clock(),sense_time,x,y, channel);
		// Apply the probability of false negative detection
		if ((randomValue < prob_misdetect_) and cr_on)
			cr_on=false;
	}
		
	return cr_on;	
		
}

                

// CRAHNs Model END
// @author:  Marco Di Felice




		

