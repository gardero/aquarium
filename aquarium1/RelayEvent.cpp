/*
 * LightEvent.cpp
 *
 *  Created on: Jul 28, 2015
 *      Author: gardero
 */

#include "RelayEvent.h"
#include "Arduino.h"


RelayEvent::RelayEvent(int arelayPin):relayPin(arelayPin) {
	pinMode(arelayPin, OUTPUT);
	digitalWrite(relayPin,HIGH);
	Serial.println("init on");

}

RelayEvent::~RelayEvent() {
	// TODO Auto-generated destructor stub
}

void RelayEvent::activate() {
	digitalWrite(relayPin,LOW);
	Serial.println("active!");
}

void RelayEvent::deactivate() {
	digitalWrite(relayPin,HIGH);
}

