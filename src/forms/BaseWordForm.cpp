/*
 * BaseWordForm.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "BaseWordForm.h"

BaseWordForm::BaseWordForm()
{

}


BaseWordForm::~BaseWordForm()
{

}


bool BaseWordForm::Init()
{
	__WCtrl = WordCtrl::GetInstance();
	Construct(GetResourceID());

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
	return true;
}


result BaseWordForm::OnInitializing()
{
	return E_SUCCESS;
}

void BaseWordForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
}
