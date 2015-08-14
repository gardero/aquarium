/*
 * MyDateTime.h
 *
 *  Created on: Jul 28, 2015
 *      Author: gardero
 */
#ifndef MYDATETIME_H_
#define MYDATETIME_H_
#include "WString.h"
#include "stdint.h"
#include "RTClib.h"

class MyDateTime : public DateTime{
public:

	MyDateTime ():DateTime(0){}
	MyDateTime (uint32_t t):DateTime(t){}
	MyDateTime (uint16_t year, uint8_t month, uint8_t day,
	                uint8_t hour =0, uint8_t min =0, uint8_t sec =0):DateTime(year,month,day,hour,min,sec){}
	MyDateTime (const DateTime& copy):DateTime(copy){}
	MyDateTime (const char* date, const char* time):DateTime(date,time){}
	MyDateTime (const __FlashStringHelper* date, const __FlashStringHelper* time):DateTime(date,time){}

	bool operator>(const DateTime& other) const{
	    return this->unixtime() > other.unixtime();
	}

	bool operator<(const DateTime& other) const{
		    return this->unixtime() < other.unixtime();
	}

	bool isOn(const DateTime& anow, const TimeSpan& duration) const{
		DateTime onow = anow;
	    MyDateTime later(onow+duration);
	    return *this < anow  &&  later > anow ;
	}

	virtual ~MyDateTime(){}

	uint8_t getD() const {
		return d;
	}

	void setD(uint8_t d) {
		this->d = d;
	}

	uint8_t getHh() const {
		return hh;
	}

	void setHh(uint8_t hh) {
		this->hh = hh;
	}

	uint8_t getM() const {
		return m;
	}

	void setM(uint8_t m) {
		this->m = m;
	}

	uint8_t getMm() const {
		return mm;
	}

	void setMm(uint8_t mm) {
		this->mm = mm;
	}

	uint8_t getSs() const {
		return ss;
	}

	void setSs(uint8_t ss) {
		this->ss = ss;
	}

	uint8_t getOff() const {
		return yOff;
	}

	void setOff(uint8_t off) {
		yOff = off;
	}
};

#endif /* MYDATETIME_H_ */
