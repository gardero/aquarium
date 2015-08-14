#include <Wire.h>
#include <LiquidCrystal.h>
#include "RTClib.h"
#include "Arduino.h"
#include "RelayEvent.h"
#include "FeedEvent.h"
#include "Event.h"
// Number of steps the motor can give.
#define RELAY1 8
#define RELAY2 9

#define Nrelays  2

#define STEPS 100
#define Nfeeding 2

LiquidCrystal lcd(7,6, 5,4,3,2);
RTC_DS1307 rtc;
RelayEvent* light1;
RelayEvent* light2;

Event feeding_events[Nfeeding];
MyTimeSpan feeding_duration(0, 0, 4, 0);

Event relay_events[Nrelays];
long lastp = 0;

void feed() {
	DateTime now1 = rtc.now();
	for (int i = 0; i < Nfeeding; ++i) {
		feeding_events[i].processTime(now1);
	}
}

void relay() {
	MyDateTime now1 = rtc.now();
//	printDate(now1);
	for (int i = 0; i < Nrelays; ++i) {
		relay_events[i].processTime(now1);
	}
}

void setupTimeFeed() {
	FeedEvent* feed = new FeedEvent();
	MyDateTime d(2000, 1, 1, 9, 0, 0);
	MyTimeSpan t(1, 0, 0, 0);
	feeding_events[0].setStartingDate(d);
	feeding_events[0].setDuration(feeding_duration);
	feeding_events[0].setPeriod(t);
	feeding_events[0].setHandler(feed);
	MyDateTime d1(2000, 1, 1, 20, 5, 0);
	feeding_events[1].setStartingDate(d1);
	feeding_events[1].setDuration(feeding_duration);
	feeding_events[1].setPeriod(t);
	feeding_events[1].setHandler(feed);
}

void setupRelay() {

	light1 = new RelayEvent(RELAY1);
	MyDateTime date(2000, 1, 1, 20, 0, 0);
	MyTimeSpan t(1, 0, 0, 0);
	MyTimeSpan d(0, 4, 0, 0);
	relay_events[0].setStartingDate(date);
	relay_events[0].setDuration(d);
	relay_events[0].setPeriod(t);
	relay_events[0].setHandler(light1);

	light2 = new RelayEvent(RELAY2);
	MyDateTime date1(2000, 1, 1, 20, 0, 0);
	MyTimeSpan t1(1, 0, 0, 0);
	MyTimeSpan d1(0, 2, 0, 0);
	relay_events[1].setStartingDate(date1);
	relay_events[1].setDuration(d1);
	relay_events[1].setPeriod(t1);
	relay_events[1].setHandler(light2);

}

void setupTime() {
	Serial.begin(9600);
#ifdef AVR
	Wire.begin();
#else
	Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
	rtc.begin();
	Serial.println("hola");
	if (!rtc.isrunning()) {
		Serial.println("RTC is NOT running!");
		// following line sets the RTC to the date & time this sketch was compiled
		rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
		// This line sets the RTC with an explicit date & time, for example to set
		// January 21, 2014 at 3am you would call:
		// rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
	} else {
		Serial.println("RTC is running!");
	}
//	rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	MyDateTime now1 = rtc.now();
	printDate(now1);
}

void setup() {
//	pinMode(RELAY1, OUTPUT);
//	digitalWrite(RELAY1,LOW);
	lcd.begin(16, 2);
	setupTime();
	setupTimeFeed();
	setupRelay();
}

void printDate(MyDateTime& t) {
	// send it to the serial monitor
	Serial.print(t.getHh(), DEC);
	// convert the byte variable to a decimal number when displayed
	Serial.print(":");
	if (t.getMm() < 10) {
		Serial.print("0");
	}
	Serial.print(t.getMm(), DEC);
	Serial.print(":");
	if (t.getSs() < 10) {
		Serial.print("0");
	}
	Serial.print(t.getSs(), DEC);
	Serial.print(" ");
	Serial.print(t.getD(), DEC);
	Serial.print("/");
	Serial.print(t.getM(), DEC);
	Serial.print("/");
	Serial.print(t.getOff(), DEC);
	Serial.println();
}

void printLDate(MyDateTime& t) {
	if (t.secondstime() > lastp) {
		lcd.clear();
		// send it to the serial monitor
		lcd.setCursor(0, 0);
		lcd.print(t.getHh(), DEC);
		// convert the byte variable to a decimal number when displayed
		lcd.print(":");
		if (t.getMm() < 10) {
			lcd.print("0");
		}
		lcd.print(t.getMm(), DEC);
		lcd.print(":");
		if (t.getSs() < 10) {
			lcd.print("0");
		}
		lcd.print(t.getSs(), DEC);
		lcd.print(" ");
		lcd.print(t.getD(), DEC);
		lcd.print("/");
		lcd.print(t.getM(), DEC);
		lcd.print("/");
		lcd.print(t.getOff(), DEC);
		lcd.setCursor(0, 1);
		lastp = t.secondstime();
		lcd.print("LIGHTS: ");
		for (int i = 0; i < Nrelays; ++i) {
			if (relay_events[i].isActive())
				lcd.print("*");
			else
				lcd.print("-");
		}

		bool feeding = false;
		for (int i = 0; i < Nfeeding; ++i) {
			feeding = feeding || (feeding_events[i].isActive());
		}
		lcd.print((feeding ? " F_ON" :""));// feeding
	}
}

void loop() {
	feed();
	relay();
	MyDateTime now1 = rtc.now();
	printLDate(now1);
}
