/*
 * Dashboard.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "Dashboard.h"
#include "forms/train/Train.h"

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

	Header *header = GetHeader();

	if (header)
	{
		ButtonItem btnAddWord;
		btnAddWord.Construct(BUTTON_ITEM_STYLE_TEXT, BaseWordForm::ID_ADD_WORD);
		btnAddWord.SetText("Add word");
		HeaderItem headerItem1;

		header->SetTitleText("voc4u");
		header->SetButton(BUTTON_POSITION_RIGHT, btnAddWord);
		header->PlayWaitingAnimation(HEADER_ANIMATION_POSITION_BUTTON_LEFT);
		header->AddActionEventListener(*this);
	}
	return r;
}

bool Dashboard::Init()
{
	Construct(L"IDF_DASHBOARD");
	return true;
}

void Dashboard::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	switch (actionId)
	{
	case BaseWordForm::ID_ADD_WORD:
	{
		AddWord * pAddWord = new AddWord();
		pAddWord->ShowPopup(this);
		break;
	}
	case BaseWordForm::ID_TRAIN:
	{
		Train *train = new Train();
		train->Init();
		train->SetBackForm(*this);
		Utils::ShowFront(train, null);
		break;
	}

	}

}

void Dashboard::ShowInfoDlg()
{
	__info.SetType(IDS_DASHBOARD);
	__info.ShowPopup(this);
}
