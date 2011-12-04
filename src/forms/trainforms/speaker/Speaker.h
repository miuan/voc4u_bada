/*
 * Speaker.h
 *
 *  Created on: 3.12.2011
 *      Author: m1uan
 */

#ifndef SPEAKER_H_
#define SPEAKER_H_

#include "../BaseTrainer.h"

class Speaker: public BaseTrainer
{
private:
	static LastListProvider *__llProv;

public:
	Speaker();

	virtual ~Speaker();

	virtual result OnInitializing(void);

	virtual LastListProvider & GetProvider(){ return *__llProv;};
	virtual BaseTrainer * NewThisN(){return new Speaker();};
};

#endif /* SPEAKER_H_ */
