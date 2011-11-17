/*
 * BaseWordForm.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "BaseWordForm.h"

BaseWordForm::BaseWordForm(): __pAddWordDlg(null)
{

}

BaseWordForm::~BaseWordForm()
{
	if(__pAddWordDlg)
		delete __pAddWordDlg;
}

bool BaseWordForm::Init()
{
	__WCtrl = WordCtrl::GetInstance();

	Construct(GetResourceID());

	Header *header = GetHeader();

	if (header)
	{
		ButtonItem btnAddWord;
		btnAddWord.Construct(BUTTON_ITEM_STYLE_ICON, ID_ADD_WORD);
		//btnAddWord.SetText(GetString("IDS_ADD_WORD_BUTTON"));
		btnAddWord.SetIcon(BUTTON_ITEM_STATUS_NORMAL, Utils::GetBitmap(L"ic_add_word.png"));
		HeaderItem headerItem1;

		header->SetTitleText("voc4u");
		header->SetButton(BUTTON_POSITION_RIGHT, btnAddWord);
		header->PlayWaitingAnimation(HEADER_ANIMATION_POSITION_BUTTON_LEFT);
		header->AddActionEventListener(*this);
	}


	return true;
}

String BaseWordForm::GetString(Osp::Base::String ID)
{
	return Utils::GetString(ID);
}

result BaseWordForm::OnInitializing()
{
	return E_SUCCESS;
}

void BaseWordForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	if (actionId == ID_ADD_WORD)
	{
		if(__pAddWordDlg)
			delete __pAddWordDlg;

		__pAddWordDlg = new AddWord();
		__pAddWordDlg->ShowPopup(this);
	}
}
