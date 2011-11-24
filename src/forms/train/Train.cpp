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
}

void Train::PrepareContextMenu()
{
	BaseWordForm::PrepareContextMenu();
	//Osp::Graphics::Bitmap *info = Utils::GetBitmap(L"ic_info.png");
//	Osp::Graphics::Bitmap *reset = Utils::GetBitmap(L"ic_reset.png");
//	__pContextMenu->AddItem(Utils::GetString(L"IDS_DIC_MENU_INFO"), ID_MENU_INFO, *info);
//	__pContextMenu->AddItem(Utils::GetString(L"IDS_DIC_MENU_RESET_DB"), ID_MENU_RESETDB, *reset);
}

String Train::GetResourceID()
{
	return L"IDF_TRAIN";
}
