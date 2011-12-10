/*
 * Speaker.h
 *
 *  Created on: 3.12.2011
 *      Author: m1uan
 */

#ifndef LISTENER_H_
#define LISTENER_H_

#include "../BaseTrainer.h"
#include "SpeechToTextDlg.h"
#include <FUix.h>

using namespace Osp::Uix;
class Listener: public BaseTrainer, public ISpeechToTextEventListener
{

private:
	static LastListProvider *__llProv;
	SpeechToTextDlg * __pSttDlg;
    void CreateOrShowDlg();
    void Exit();
    void RecognitionWordIsNotSuccess();
    void TestWordIsSuccess();
    void PlayActualWord();
public:
	Listener();
	virtual LastListProvider & GetProvider()
	{
		return *__llProv;
	}
	;
	virtual BaseTrainer * NewThisN()
	{
		return new Listener();
	}
	;
	virtual ~Listener();


	virtual bool Init();

	virtual result OnInitializing();

	virtual void OnSpeechToTextInitialized(void);
	virtual void OnSpeechToTextRecordingStatusChanged(Osp::Uix::SpeechToTextRecordingStatus status);
	virtual void OnSpeechToTextErrorOccurred(Osp::Uix::SpeechToTextError error);
	virtual void OnSpeechToTextCompleted(Osp::Base::String& result, Osp::Uix::SpeechToTextWarning warning);

	virtual void OnUserEventReceivedN (RequestId requestId, Osp::Base::Collection::IList *pArgs);

protected:
	virtual String GetTextForTestLabel();
};

#endif /* LISTENER_H_ */
