/*
 * Train.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "Train.h"

Train::Train()
{
	// TODO Auto-generated constructor stub

}

Train::~Train()
{
	// TODO Auto-generated destructor stub
}

result Train::OnInitializing(void)
{

	return E_SUCCESS;
}

void Train::PrepareFooter()
{
	BaseWordForm::PrepareFooter();
	Footer * footer = GetFooter();
	if (footer)
	{
		FooterItem f1;
		f1.Construct(ID_BTN_DONTKNOW);
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
	Osp::Graphics::Bitmap *info = Utils::GetBitmap(L"ic_info.png");
	//	Osp::Graphics::Bitmap *reset = Utils::GetBitmap(L"ic_reset.png");
	__pContextMenu->AddItem(Utils::GetString(L"IDS_DIC_MENU_INFO"), ID_DICTIONARY, *info);
	//	__pContextMenu->AddItem(Utils::GetString(L"IDS_DIC_MENU_RESET_DB"), ID_MENU_RESETDB, *reset);
}

String Train::GetResourceID()
{
	return L"IDF_TRAIN";
}

void Train::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	static bool bswitch = false;

	bswitch = !bswitch;

	if(!bswitch)
	{
		return;
	}

	if (ID_BTN_KNOW == actionId)
	{
		AppLog("know");
	}
	else if (ID_BTN_DONTKNOW == actionId)
	{
		AppLog("dont know");
	}
	else
	{
		BaseWordForm::OnActionPerformed(source, actionId);
	}
}
