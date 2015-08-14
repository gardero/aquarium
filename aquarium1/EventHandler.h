/*
 * EventHandler.h
 *
 *  Created on: Jul 28, 2015
 *      Author: gardero
 */

#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_
class EventHandler {
public:
	virtual ~EventHandler(){}
	virtual void begin() {}
	virtual void activate() {}
	virtual void performAction() {}
	virtual void deactivate() {}
	virtual void end() {}
};
#endif /* EVENTHANDLER_H_ */
