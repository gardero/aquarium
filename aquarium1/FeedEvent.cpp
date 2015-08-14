/*
 * FeedEvent.cpp
 *
 *  Created on: Jul 28, 2015
 *      Author: gardero
 */

#include "FeedEvent.h"
#include "Arduino.h"


FeedEvent::~FeedEvent() {
	// TODO Auto-generated destructor stub
}

void FeedEvent::begin() {
}

void FeedEvent::activate() {
	// light something?
}



void FeedEvent::performAction() {
//	stepper.step(STEPS/2);
		stepper.step(2*STEPS);
}

void FeedEvent::deactivate() {
	digitalWrite(10,LOW);
	digitalWrite(11,LOW);
	digitalWrite(12,LOW);
	digitalWrite(13,LOW);
}

void FeedEvent::end() {
}
