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
		btnAddWord.SetText(GetString("IDS_ADD_WORD_BUTTON"));
		HeaderItem headerItem1;

		header->SetTitleText("voc4u");
		header->SetButton(BUTTON_POSITION_RIGHT, btnAddWord);
		header->PlayWaitingAnimation(HEADER_ANIMATION_POSITION_BUTTON_LEFT);
		header->AddActionEventListener(*this);
	}

	Footer *footer = GetFooter();

	if (footer)
	{
		FooterItem btnSave;
		btnSave.Construct(ID_ADD_WORD);
		btnSave.SetText(GetString("IDS_SAVE_DICTIONARY"));
		footer->AddItem(btnSave);
	}
	return true;
}

String BaseWordForm::GetString(Osp::Base::String ID)
{
	String out = "";
	Application* pApp = Application::GetInstance();
	pApp->GetAppResource()->GetString(ID, out);
	return out;
}

result BaseWordForm::OnInitializing()
{
	return E_SUCCESS;
}

void BaseWordForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
}
