/*
 * LightEvent.h
 *
 *  Created on: Jul 28, 2015
 *      Author: gardero
 */

#ifndef LIGHTEVENT_H_
#define LIGHTEVENT_H_
#include "EventHandler.h"

class RelayEvent : public EventHandler{
private:
	int relayPin;
public:
	RelayEvent(int);
	virtual ~RelayEvent();
	void activate();
	void deactivate();

};


#endif /* LIGHTEVENT_H_ */
