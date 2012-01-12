/*
 * Train.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "Train.h"
#include "forms/dictionary/Dictionary.h"

LastListProvider *Train::__llProv = null;

Train::Train()
{

}

Train::~Train()
{

}

void Train::PrepareFooter()
{
	BaseWordForm::PrepareFooter();
	Footer * footer = GetFooter();
	if (footer)
	{
		Bitmap * pB1 = Utils::GetBitmapN("bg_listener_normal.png");
		FooterItem f1;
		f1.Construct(ID_BTN_DONTKNOW);
		f1.SetIcon(FOOTER_ITEM_STATUS_NORMAL, pB1);
		f1.SetText(GetString("IDS_BTN_DONTKNOW"));
		footer->AddItem(f1);
		FooterItem f2;
		f2.Construct(ID_BTN_KNOW);
		f2.SetText(GetString("IDS_BTN_KNOW"));
		footer->AddItem(f2);
	}
}

void Train::PrepareContextMenu()
{
	BaseWordForm::PrepareContextMenu();
	Osp::Graphics::Bitmap *info = Utils::GetBitmapN(L"ic_dictionary.png");
	//	Osp::Graphics::Bitmap *reset = Utils::GetBitmap(L"ic_reset.png");
	__pContextMenu->AddItem(Utils::GetMenuString(L"IDS_DIC_MENU_DICTIONARY"), ID_DICTIONARY, *info);
	//	__pContextMenu->AddItem(Utils::GetString(L"IDS_DIC_MENU_RESET_DB"), ID_MENU_RESETDB, *reset);
}

void Train::UpdateWord(bool know)
{
	if (__word)
	{
		__word->SetKnow(know);
		__WCtrl->UpdateWord(*__word);

		UpdateListWithWord();
	}

}

void Train::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	static bool bswitch = false;

	bswitch = !bswitch;

	if (ID_BTN_KNOW == actionId)
	{

		if (!bswitch)
		{
			return;
		}
		AppLog("know");
		UpdateWord(true);
		GetFirstWord();
	}
	else if (ID_BTN_DONTKNOW == actionId)
	{
		if (!bswitch)
		{
			return;
		}

		AppLog("dont know");
		UpdateWord(false);
		GetFirstWord();
	}
	else
	{
		BaseWordForm::OnActionPerformed(source, actionId);
	}
}


LastListProvider & Train::GetProvider()
{
	if (!__llProv)
			__llProv = new LastListProvider(GetTextToSpeechHelper());

	return *__llProv;
}
