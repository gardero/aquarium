/*
 * Duration.h
 *
 *  Created on: Jul 28, 2015
 *      Author: gardero
 */

#ifndef DURATION_H_
#define DURATION_H_
#include "RTClib.h"

class MyTimeSpan : public TimeSpan {
public:
	MyTimeSpan():TimeSpan(0){
	}
	MyTimeSpan(long seconds):TimeSpan(seconds){
	}
	MyTimeSpan(int16_t days, int8_t hours, int8_t min, int8_t sec):TimeSpan(days,hours,min,sec){
	}
	virtual ~MyTimeSpan(){}
	void update(int16_t days, int8_t hours, int8_t min, int8_t sec){
		this->_seconds = sec + min*60 + hours*3600 + days*3600*24;
	}

	uint32_t getSeconds(){
		return _seconds;
	}
};

#endif /* DURATION_H_ */
