/*
 * Event.cpp
 *
 *  Created on: Jul 28, 2015
 *      Author: gardero
 */

#include "Event.h"
#include "Arduino.h"


void Event::processTime(const DateTime & now){
	if (!started){
		started = (this->startingDate < now);
		if (started){
			begin();
		}
	} else {
		bool wasactive = active;
		active = isActive(now);
		if (active && !wasactive){
			activatedCount++;
			activate();
			performAction();
		} else if (active){
			performAction();
		} else
		if (!active && wasactive){
			deactivate();
		}
	}
}

bool check(int value, int pattern){
	return pattern <= 0 || pattern==value;
}

void Event::log(uint32_t dsec, uint32_t t, uint32_t dt, uint32_t d) {
	Serial.print(dsec, DEC);
	Serial.print(" % ");
	Serial.print(t, DEC);
	Serial.print(" == ");
	Serial.print(dt, DEC);
	Serial.print(" ?< ");
	Serial.print(d, DEC);
	Serial.println("/");
}

bool Event::isActive(const DateTime & now){
	if (repeated){
		uint32_t dsec = (now.unixtime() - startingDate.unixtime());
		uint32_t t = period.getSeconds();
		uint32_t d = duration.getSeconds();
		uint32_t dt = dsec % t;
		log(dsec, t, dt, d);
		return ((dt) < d);
	} else {
		return !active && activatedCount==0;
	}
}


