/*
 * Dashboard.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "Dashboard.h"
#include "forms/trainforms/train/Train.h"
#include "forms/trainforms/speaker/Speaker.h"
#include "forms/trainforms/listener/Listener.h"

Dashboard::Dashboard()
{
	// TODO Auto-generated constructor stub

}

Dashboard::~Dashboard()
{
	// TODO Auto-generated destructor stub
}

result Dashboard::OnInitializing(void)
{
	result r = E_SUCCESS;

	if (!CommonSetting::GetInstance().NSHDashboard)
		ShowInfoDlg();

	Button *pBtn_train = static_cast<Button *> (GetControl("IDC_BTN_TRAIN"));
	if (pBtn_train)
	{
		pBtn_train->SetActionId(BaseWordForm::ID_TRAIN);
		pBtn_train->AddActionEventListener(*this);
	}

	Button *pBtn_speaker = static_cast<Button *> (GetControl("IDC_BTN_SPEAKER"));
	if (pBtn_speaker)
	{
		pBtn_speaker->SetActionId(BaseWordForm::ID_SPEAKER);
		pBtn_speaker->AddActionEventListener(*this);
	}

	Button *pBtn_listener = static_cast<Button *> (GetControl("IDC_BTN_LISTENER"));
	if (pBtn_listener)
	{
		pBtn_listener->SetActionId(BaseWordForm::ID_LISTENER);
		pBtn_listener->AddActionEventListener(*this);
	}

	return r;
}

void Dashboard::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	switch (actionId)
	{
	/*case BaseWordForm::ID_ADD_WORD:
	 {
	 AddWord * pAddWord = new AddWord();
	 pAddWord->ShowPopup(this);
	 break;
	 }*/
	case BaseWordForm::ID_TRAIN:
	{
		Train *train = new Train();
		train->Init();
		train->SetBackForm(*this);
		Utils::ShowFront(train, null);
		break;
	}
	case BaseWordForm::ID_SPEAKER:
	{
		Speaker *speaker = new Speaker();
		speaker->Init();
		speaker->SetBackForm(*this);
		Utils::ShowFront(speaker, null);
		break;
	}
	case BaseWordForm::ID_LISTENER:
	{
//		Speaker *speaker = new Speaker();
//				speaker->Init();
//				speaker->SetBackForm(*this);
//				Utils::ShowFront(speaker, null);
//				break;
		Listener *listener = new Listener();
		listener->Init();
		listener->SetBackForm(*this);
		Utils::ShowFront(listener, null);
		break;
	}
	default:
		BaseWordForm::OnActionPerformed(source, actionId);
	}

}

//void Dashboard::ShowInfoDlg()
//{
//	__info.SetType(IDS_DASHBOARD);
//	__info.ShowPopup(this);
//}
