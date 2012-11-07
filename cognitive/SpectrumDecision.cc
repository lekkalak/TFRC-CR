// CRAHNs Model START
// @author:  Marco Di Felice


#include "SpectrumDecision.h"

// Spectrum Decision initializer
SpectrumDecision::SpectrumDecision(SpectrumManager *sm) {

	decision_policy_=DECISION_POLICY_ALWAYS_SWITCH;

	spectrum_policy_=ROUND_ROBIN_SWITCH;
	
	smanager_=sm;

}

        


// decideSwitch: decide wether to stay or leave the current channel, when a PU is detected       
bool
SpectrumDecision::decideSwitch() {

	double randomValue;
	bool switch_decision;
	
	switch(decision_policy_) {
		
		// Switch with probability equal to THRESHOLD_SWITCH, stay otherwise
		case DECISION_POLICY_PROBABILISTIC_SWITCH:

			randomValue=Random::uniform();

			if (randomValue < THRESHOLD_SWITCH)
				switch_decision=true;
			else	
				switch_decision=false;
			break;

		// Switch to a new channel in anycase
		case DECISION_POLICY_ALWAYS_SWITCH:

			switch_decision=true;
			break;
					
		default:
			
			switch_decision=true;	
			break;	
	}

	return switch_decision;
}





// decideSpectrum: get the next spectrum to be used, based on the allocation policy
int
SpectrumDecision::decideSpectrum(int current_channel) {
		
	int next_channel;

	switch(decision_policy_) {	
		
		// Policy RANDOM_SWITCH: next_channel -> random(1..MAX_CHANNELS)
		case RANDOM_SWITCH:
			
			next_channel=((int)(Random::uniform()*MAX_CHANNELS))+1;		
			if (next_channel >= MAX_CHANNELS)
				next_channel = MAX_CHANNELS-1;
			break;
		
		// Policy ROUND_ROBIN_SWITCH: next channel -> ( next_channel + 1 ) % MAX_CHANNELS
		case ROUND_ROBIN_SWITCH:

			next_channel=(current_channel+1) % MAX_CHANNELS;
			if (next_channel ==0)
				next_channel++;
			break;
	
	 }
		
	return next_channel;

}

// CRAHNs Model END
// @author:  Marco Di Felice

