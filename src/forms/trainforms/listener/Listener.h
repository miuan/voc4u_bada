/*
 * Speaker.h
 *
 *  Created on: 3.12.2011
 *      Author: m1uan
 */

#ifndef LISTENER_H_
#define LISTENER_H_

#include "../BaseTrainer.h"

class Listener: public BaseTrainer
{
private:
	static LastListProvider *__llProv;


public:
	Listener();
	virtual LastListProvider & GetProvider(){ return *__llProv;};
	virtual BaseTrainer * NewThisN(){return new Listener();};
	virtual ~Listener();
};

#endif /* LISTENER_H_ */
