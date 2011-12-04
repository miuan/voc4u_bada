/*
 * Speaker.h
 *
 *  Created on: 3.12.2011
 *      Author: m1uan
 */

#ifndef SPEAKER_H_
#define SPEAKER_H_

#include "../BaseTrainer.h"

using namespace Osp::System;

class Speaker: public BaseTrainer, public ITimerEventListener
{
private:
	static LastListProvider *__llProv;
	Timer *__pTimer;
    void PlayAndGetFirstWord();

public:
	// 10s for next word
	static const int TIMER_TIME = 10000;
public:


	Speaker();

	virtual ~Speaker();

	virtual result OnInitializing(void);

	virtual void OnTimerExpired(Timer& timer);

	virtual LastListProvider & GetProvider();
	virtual BaseTrainer * NewThisN(){return new Speaker();};

protected:
	virtual String GetTextForTestLabel();
};

#endif /* SPEAKER_H_ */
