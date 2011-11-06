/*
 * Dashboard.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "Dashboard.h"

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

	WordCtrl * wc = WordCtrl::GetInstance();
	if (wc)
	{
		Word w(-1, 0, L"ahoj", L"hello", 1, 1);
		wc->AddWord(w);
	}

	Button *pBtn_train = static_cast<Button *> (GetControl("IDC_BTN_TRAIN"));
	if (pBtn_train)
	{
		pBtn_train->SetActionId(101);
		pBtn_train->AddActionEventListener(*this);
	}

	Header *header = GetHeader();

	if (header)
	{
		ButtonItem btnAddWord;
		btnAddWord.Construct(BUTTON_ITEM_STYLE_TEXT, ID_ADD_WORD);
		btnAddWord.SetText("Add word");
		HeaderItem headerItem1;

		header->SetTitleText("voc4u");
		header->SetButton(BUTTON_POSITION_RIGHT, btnAddWord);
		header->PlayWaitingAnimation(HEADER_ANIMATION_POSITION_BUTTON_LEFT);
		header->AddActionEventListener(*this);
	}
	return r;
}

bool Dashboard::Initialize()
{
	Construct(L"IDF_DASHBOARD");
	return true;
}

#include "../init/Init.h"
void Dashboard::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{

	if (actionId == ID_ADD_WORD)
	{
		AddWord * pAddWord = new AddWord();
		pAddWord->ShowPopup(this);
		//pAddWord->Show();

	}
	else
	{
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

		Init * init = new Init();
		init->Initialize();
		pFrame->RemoveControl(*init);
		pFrame->AddControl(*init);
		pFrame->SetCurrentForm(*init);
		init->RequestRedraw(true);
	}
}
