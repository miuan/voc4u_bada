/*
 * Speaker.h
 *
 *  Created on: 3.12.2011
 *      Author: m1uan
 */

#ifndef LISTENER_H_
#define LISTENER_H_

#include "../BaseWordForm.h"

class Listener : public BaseWordForm
{
public:
	Listener();
	virtual String GetResourceID(){return L"IDF_TRAIN";};
	virtual ~Listener();
};

#endif /* LISTENER_H_ */
