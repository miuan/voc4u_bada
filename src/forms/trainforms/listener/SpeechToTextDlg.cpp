/*
 * LangSelect.cpp
 *
 *  Created on: 23.10.2011
 *      Author: m1uan
 */

#include "SpeechToTextDlg.h"

SpeechToTextDlg::SpeechToTextDlg() :
	__resultListener(null), __resultActionCode(0)
{

}

SpeechToTextDlg::~SpeechToTextDlg()
{

}

bool SpeechToTextDlg::ShowPopup(Form * parent, String title)
{
	__pParentForm = parent;

	result result = Construct(L"IDP_SPEECH_TO_TEXT");

	EditArea *peaText = static_cast<EditArea *> (GetControl("IDC_TEXT"));
	if (peaText)
	{
		peaText->SetEnabled(false);
	}

	Button *pbtnStopSpeak = static_cast<Button *> (GetControl("IDC_BTN_STOP_SPEAKING"));
	if (pbtnStopSpeak)
	{
		pbtnStopSpeak->AddActionEventListener(*this);
		pbtnStopSpeak->SetActionId(ID_BTN_STOP_SPEAKING);
	}

	Button *pbtnCancel = static_cast<Button *> (GetControl("IDC_BTN_CANCEL"));
	if (pbtnCancel)
	{
		pbtnCancel->AddActionEventListener(*this);
		pbtnCancel->SetActionId(ID_BTN_CANCEL);
	}

	SetTitleText(title);

	SetShowState(true);
	Show();
	return result;
}

void SpeechToTextDlg::showErrorMessageBox()
{
	String body;
	Application::GetInstance()->GetAppResource()->GetString(L"IDS_MSG_MUST_BE_FILL_BOTH_EDIT_FIELD", body);
	MessageBox messageBox;
	messageBox.Construct(GetTitleText(), body, MSGBOX_STYLE_OK, 3000);
	// Calls ShowAndWait - draw, show itself and process events
	int modalResult = 0;
	messageBox.ShowAndWait(modalResult);
}

void SpeechToTextDlg::OnActionPerformed(const Osp::Ui::Control & source, int actionId)
{
	//if (actionId == ID_BTN_ADD)
	{
		//		String native = __pNative->GetText();
		//		String lern = __pLern->GetText();
		//
		//		if (native.GetLength() == 0 || lern.GetLength() == 0)
		//		{
		//			showErrorMessageBox();
		//			return;
		//		}
		//
		//		WordCtrl * wc = WordCtrl::GetInstance();
		//		if (wc)
		//		{
		//			Word w(-1, 0, lern, native, 1, 1);
		//			if (wc->AddWord(w) && __resultListener)
		//				__resultListener->OnActionPerformed(source, __resultActionCode);
		//		}
	}


	//SetShowState(false);
	if (__pParentForm)
	{
		__pParentForm->SendUserEvent(actionId, null);
		//__pParentForm->Draw();
		//__pParentForm->Show();
	}
}
