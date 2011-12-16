/*
 * Speaker.cpp
 *
 *  Created on: 3.12.2011
 *      Author: m1uan
 */

#include "Speaker.h"

LastListProvider *Speaker::__llProv = null;
bool Speaker::__paused = false;
Timer *Speaker::__pTimer = null;

Speaker::Speaker()
{
	if (!__llProv)
		__llProv = new LastListProvider();

	// if exist, but shouldn't exist
	// only for sure
	DeleteTimer();

	__pTimer = new Timer();
	if (__pTimer)
	{
		__pTimer->Construct(*this);
	}
}

Speaker::~Speaker()
{
    DeleteTimer();
}

void Speaker::DeleteTimer()
{
    if (__pTimer)
	{
    	__pTimer->Cancel();
		delete __pTimer;
		__pTimer = null;
	}
}

/**
 * static function called from voc4u.cpp when app go to background
 * stop the speaking word, when the timer is active
 */
void Speaker::Pause()
{
	if (__pTimer)
	{
		__pTimer->Cancel();
	}
	__paused = true;
}

/**
 * caled from voc4u.cpp when app go to foreground
 * when prev stop the timer, start the timer again
 */
void Speaker::CanPlay()
{
	if (__pTimer)
	{
		__pTimer->Start(10);
	}
	__paused = false;
}

result Speaker::OnInitializing(void)
{
	result r = BaseTrainer::OnInitializing();

	__lblTest->AddTouchEventListener(*this);

	if (!IsFailed(r))
	{
		PlayAndGetFirstWord();
		__pTimer->Start(TIMER_TIME);
	}
	return E_SUCCESS;
}

void Speaker::PlayAndGetFirstWord()
{
	GetFirstWord();
	AppAssert(__word);
	if (__word)
	{
		String lern = __word->GetLern();
		__word->SetKnow(true);
		GetTextToSpeechHelper()->Play(lern);
	}

}

void Speaker::OnTimerExpired(Timer& timer)
{
	if (!__paused)
	{
		UpdateListWithWord();
		PlayAndGetFirstWord();
		__pTimer->Start(TIMER_TIME);
	}
}

LastListProvider & Speaker::GetProvider()
{
	if (!__llProv)
		__llProv = new LastListProvider(GetTextToSpeechHelper(), 100);

	return *__llProv;
}

String Speaker::GetTextForTestLabel()
{
	return Utils::GetString("IDS_TAP_FOR_DISPLAY");
}

void Speaker::OnTouchDoublePressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
}

void Speaker::OnTouchFocusIn(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
}

void Speaker::OnTouchFocusOut(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
}

void Speaker::OnTouchLongPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
}

void Speaker::OnTouchMoved(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
}

void Speaker::OnTouchPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
	if(__paused)
		return;

	__pTimer->Cancel();

	if (__word)
	{
		__word->SetKnow(false);
		String lern = __word->GetLern();
		GetTextToSpeechHelper()->Play(lern);
		__lblTest->SetText(lern);
		__lblTest->Draw();
		__lblTest->Show();
	}

	__pTimer->Start(TIMER_TIME);
}

void Speaker::OnTouchReleased(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo)
{
}

