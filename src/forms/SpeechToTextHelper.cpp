/*
 * SpeechToTextHelper.cpp
 *
 *  Created on: 5.12.2011
 *      Author: m1uan
 */

#include "SpeechToTextHelper.h"

SpeechToTextHelper::SpeechToTextHelper() :
	__pSpeechToText(null), __pISTTEL(null), __initialized(false), __errorOccurred(false)
{

}

SpeechToTextHelper::~SpeechToTextHelper()
{

}

bool SpeechToTextHelper::Init()
{
	__pSpeechToText = new SpeechToText();

	return __pSpeechToText && __pSpeechToText->Construct(*this) == E_SUCCESS;

}

void SpeechToTextHelper::SetListener(ISpeechToTextEventListener * isttel)
{
	__pISTTEL = isttel;
}

void SpeechToTextHelper::Cancel()
{
	if (__pSpeechToText)
		__pSpeechToText->Cancel();
}

void SpeechToTextHelper::Stop()
{
	if (__pSpeechToText)
		__pSpeechToText->Stop();
}

void SpeechToTextHelper::Start()
{
	__pSpeechToText->Initialize();
//	if (__pSpeechToText)
//	{
//		__pSpeechToText->Start();
//	}
}

void SpeechToTextHelper::OnSpeechToTextInitialized(void)
{
	AppLogDebug("*");
	__pSpeechToText->Start();
	__initialized = true;
	if (__pISTTEL)
		__pISTTEL->OnSpeechToTextInitialized();
}

void SpeechToTextHelper::OnSpeechToTextRecordingStatusChanged(Osp::Uix::SpeechToTextRecordingStatus status)
{
	switch (status)
	{
	case STT_STATUS_RECORDING_STARTED:
		AppLogDebug("STT_STATUS_RECORDING_STARTED");
		break;
	case STT_STATUS_RECORDING_STOPPED:
		AppLogDebug("STT_STATUS_RECORDING_STOPPED");
		break;
	case STT_STATUS_RECORDING_COMPLETED:
		AppLogDebug("STT_STATUS_RECORDING_COMPLETED");
		break;
	}

	// set because after once recongnition
	// must call init again, and init call
	// only when __initialized is false
	//if(status == STT_STATUS_RECORDING_COMPLETED)
	//	__initialized = false;

	if (__pISTTEL)
		__pISTTEL->OnSpeechToTextRecordingStatusChanged(status);
}

void SpeechToTextHelper::OnSpeechToTextErrorOccurred(Osp::Uix::SpeechToTextError error)
{
	__errorOccurred = true;

	switch (error)
	{
	case STT_ERROR_INITIALIZATION_FAILED:
		AppLogDebug("STT_ERROR_INITIALIZATION_FAILED");
		break;
	case STT_ERROR_START_FAILED:
		//__initialized = false;
		//__errorOccurred = false;
		AppLogDebug("STT_ERROR_START_FAILED");
		break;
	case STT_ERROR_STOP_FAILED:
		AppLogDebug("STT_ERROR_STOP_FAILED");
		break;
	case STT_ERROR_RECORDING_FAILED:
		AppLogDebug("STT_ERROR_RECORDING_FAILED");
		break;
	case STT_ERROR_NETWORK_FAILED:
		AppLogDebug("STT_ERROR_NETWORK_FAILED");
		break;
	case STT_ERROR_CANCELED:
		AppLogDebug("STT_ERROR_CANCELED");
		break;
	case STT_ERROR_RECOGNITION_FAILED:
		AppLogDebug("STT_ERROR_RECOGNITION_FAILED");
		break;
	case STT_ERROR_TOO_SHORT:
		AppLogDebug("STT_ERROR_TOO_SHORT");
		break;
	case STT_ERROR_TOO_LONG:
		AppLogDebug("STT_ERROR_TOO_LONG");
		break;
	case STT_ERROR_TOO_QUIET:
		AppLogDebug("STT_ERROR_TOO_QUIET");
		break;
	case STT_ERROR_TOO_LOUD:
		AppLogDebug("STT_ERROR_TOO_LOUD");
		break;
	case STT_ERROR_TOO_FAST:
		AppLogDebug("STT_ERROR_TOO_FAST");
		break;
	}

	if (__pISTTEL)
		__pISTTEL->OnSpeechToTextErrorOccurred(error);
}

void SpeechToTextHelper::OnSpeechToTextCompleted(Osp::Base::String & result, Osp::Uix::SpeechToTextWarning warning)
{
	AppLogDebug("*");
	//__initialized = false;

	if (__pISTTEL)
		__pISTTEL->OnSpeechToTextCompleted(result, warning);

}

