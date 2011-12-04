/*
 * Speaker.cpp
 *
 *  Created on: 3.12.2011
 *      Author: m1uan
 */

#include "Speaker.h"

LastListProvider *Speaker::__llProv = null;

Speaker::Speaker() :
	__pTimer(null)
{
	if (!__llProv)
		__llProv = new LastListProvider();

	__pTimer = new Timer();
	if (__pTimer)
	{
		__pTimer->Construct(*this);
	}
}

Speaker::~Speaker()
{

	if (__pTimer)
	{
		__pTimer->Cancel();
		delete __pTimer;
	}
}

result Speaker::OnInitializing(void)
{
	result r = BaseTrainer::OnInitializing();
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
		GetTextToSpeechHelper()->Play(lern);
	}

}

void Speaker::OnTimerExpired(Timer& timer)
{
	UpdateListWithWord();
	PlayAndGetFirstWord();
	__pTimer->Start(TIMER_TIME);
}

LastListProvider & Speaker::GetProvider()
{
	if (!__llProv)
		__llProv = new LastListProvider(GetTextToSpeechHelper(), 100);

	return *__llProv;
}

String Speaker::GetTextForTestLabel()
{
    return L"*** tap for show ***";
}
