/*
 * Speaker.cpp
 *
 *  Created on: 3.12.2011
 *      Author: m1uan
 */

#include "Listener.h"

LastListProvider *Listener::__llProv = null;

Listener::Listener() :
	__pSttDlg(null)
{
	if (!__llProv)
		__llProv = new LastListProvider();
}

Listener::~Listener()
{
	// TODO Auto-generated destructor stub
}

bool Listener::Init()
{
	result r = E_SUCCESS;

	return BaseTrainer::Init();
}

result Listener::OnInitializing()
{
	result r = BaseTrainer::OnInitializing();

	SetSpeechToTextListener(this);
	SpeechToTextStart();
	return r;
}

void Listener::CreateOrShowDlg()
{
	if (!__pSttDlg)
	{
		__pSttDlg = new SpeechToTextDlg();
		__pSttDlg->ShowPopup(this, __word->GetNative());
	}
	else
	{
		__pSttDlg->SetTitleText(__word->GetNative());
		__pSttDlg->SetShowState(true);
		__pSttDlg->Show();
	}

}

void Listener::OnSpeechToTextInitialized(void)
{
	//SpeechToTextStart();

}

void Listener::OnSpeechToTextRecordingStatusChanged(Osp::Uix::SpeechToTextRecordingStatus status)
{
	switch (status)
	{
	case STT_STATUS_RECORDING_STARTED:
	{
		CreateOrShowDlg();
		break;
	}
	case STT_STATUS_RECORDING_COMPLETED:
	{
		break;
	}
	}
}

void Listener::Exit()
{
	//SpeechToTextCancel();
	SetSpeechToTextListener(null);
	Utils::ShowFront(GetBackForm(), this);
}

void Listener::PlayActualWord()
{
    TextToSpeechHelper *ttsh = GetTextToSpeechHelper();
    if(ttsh && __word){
        String lern = __word->GetLern();
        ttsh->Play(lern);
    }
}

void Listener::RecognitionWordIsNotSuccess()
{
    PlayActualWord();

    String body = Utils::GetString("IDS_STT_NOT_SUCCESS");
	MessageBox messageBox;
	messageBox.Construct(GetTitleText(), body, MSGBOX_STYLE_YESNOCANCEL, 0);
	// Calls ShowAndWait - draw, show itself and process events
	int modalResult = 0;
	messageBox.ShowAndWait(modalResult);
	if (modalResult == MSGBOX_RESULT_NO)
	{
		//SetSpeechToTextListener(this);
		SpeechToTextStart();
	}
	else if (modalResult == MSGBOX_RESULT_YES)
	{
		UpdateListWithWord();
		GetFirstWord();
		SpeechToTextStart();
	}
	else
	{
		Exit();
	}

}

void Listener::OnSpeechToTextErrorOccurred(Osp::Uix::SpeechToTextError error)
{
	//SpeechToTextCancel();
	//	if (error == STT_ERROR_START_FAILED)
	//	{
	//		AppLogDebug("Try start again");
	//		//SpeechToTextStart();
	//		SetSpeechToTextListener(this);
	//	}
	//	else
	if(error == STT_ERROR_CANCELED)
		return;

	if(error == STT_ERROR_INITIALIZATION_FAILED)
	{
		SpeechToTextStart();
		return;
	}

	if (error == STT_ERROR_RECOGNITION_FAILED)
	{
		//TestWordIsSuccess();
		RecognitionWordIsNotSuccess();
	}
	else
	{
		String body = Utils::GetString("IDS_STT_ERROR_OCCURRED");
		MessageBox messageBox;
		messageBox.Construct(GetTitleText(), body, MSGBOX_STYLE_CANCEL, 0);
		// Calls ShowAndWait - draw, show itself and process events
		int modalResult = 0;

		messageBox.ShowAndWait(modalResult);
		Exit();
	}
}

void Listener::TestWordIsSuccess()
{
	PlayActualWord();

	int modalResult;

    MessageBox messageBox;
    messageBox.Construct(GetTitleText(), Utils::GetString("IDS_STT_SUCCESS"), MSGBOX_STYLE_OK, 0);
    messageBox.ShowAndWait(modalResult);
    __word->SetKnow(true);
    __WCtrl->UpdateWord(*__word);

    UpdateListWithWord();
    GetFirstWord();
    SpeechToTextStart();
}

void Listener::OnSpeechToTextCompleted(Osp::Base::String& result, Osp::Uix::SpeechToTextWarning warning)
{
	AppLog("Get word: %S", result.GetPointer());

	String lern = __word->GetLern();

	if (result.CompareTo(lern) != 0)
	{
		RecognitionWordIsNotSuccess();
	}
	else
	{
	    TestWordIsSuccess();
	}


	//SetSpeechToTextListener(this);

}

void Listener::OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList *pArgs)
{
	if (requestId == SpeechToTextDlg::ID_BTN_STOP_SPEAKING)
	{
		if (__pSttDlg)
		{
			__pSttDlg->SetShowState(false);
			Draw();
			Show();
		}
		SpeechToTextStop();
	}
	else if (requestId == SpeechToTextDlg::ID_BTN_CANCEL)
	{
		Exit();
	}
	//BaseTrainer::OnUserEventReceivedN(requestId, pArgs);
}
