/*
 * FeedEvent.h
 *
 *  Created on: Jul 28, 2015
 *      Author: gardero
 */

#ifndef FEEDEVENT_H_
#define FEEDEVENT_H_

#define STEPS 100

#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11

#include "Stepper.h"
#include "EventHandler.h"
#include "Arduino.h"


class FeedEvent : public EventHandler{

private:
//	Stepper stepper = Stepper(STEPS, 8,10,a11,9);
	Stepper stepper = Stepper(STEPS, 11,13,12,10);
public:
	FeedEvent(){
		stepper.setSpeed(100);
	}
	virtual ~FeedEvent();

	void begin();
	 void activate();
	 void performAction();
	 void deactivate();
	 void end();

};


#endif /* FEEDEVENT_H_ */
