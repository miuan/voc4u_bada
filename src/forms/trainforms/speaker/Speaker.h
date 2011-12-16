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

class Speaker: public BaseTrainer, public ITimerEventListener, public Osp::Ui::ITouchEventListener
{

private:
	static bool __paused;
	static LastListProvider *__llProv;
	static Timer *__pTimer;
    void PlayAndGetFirstWord();
    void DeleteTimer();

public:
    static const int TIMER_TIME = 10000;
public:


	Speaker();

	virtual ~Speaker();

	virtual result OnInitializing(void);

	virtual void OnTimerExpired(Timer& timer);

	virtual LastListProvider & GetProvider();
	virtual BaseTrainer * NewThisN(){return new Speaker();};

	virtual void OnTouchDoublePressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchFocusIn (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchFocusOut (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchLongPressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchMoved (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchPressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void OnTouchReleased (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);

protected:
	virtual String GetTextForTestLabel();

public:
	static void Pause();
    static void CanPlay();
};

#endif /* SPEAKER_H_ */
