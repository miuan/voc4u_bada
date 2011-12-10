/*
 * SpeechToTextHelper.h
 *
 *  Created on: 5.12.2011
 *      Author: m1uan
 */

#ifndef SPEECHTOTEXTHELPER_H_
#define SPEECHTOTEXTHELPER_H_

#include <FUix.h>

using namespace Osp::Uix;

class SpeechToTextHelper: public ISpeechToTextEventListener
{
private:
	Osp::Uix::SpeechToText *__pSpeechToText;
	ISpeechToTextEventListener *__pISTTEL;

	bool __initialized;
	bool __errorOccurred;
public:
	SpeechToTextHelper();
	virtual ~SpeechToTextHelper();

	bool Init();

	bool IsInitialized() { return __initialized; };
	bool IsNotWorks(){ return !__initialized && __errorOccurred;};

	void SetListener(ISpeechToTextEventListener * isttel);
	void Cancel();
	void Stop();
	bool Start();

	virtual void OnSpeechToTextInitialized(void);
	virtual void OnSpeechToTextRecordingStatusChanged(Osp::Uix::SpeechToTextRecordingStatus status);
	virtual void OnSpeechToTextErrorOccurred(Osp::Uix::SpeechToTextError error);
	virtual void OnSpeechToTextCompleted(Osp::Base::String& result, Osp::Uix::SpeechToTextWarning warning);

};

#endif /* SPEECHTOTEXTHELPER_H_ */
