/*
 * Train.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "Train.h"
#include "forms/dictionary/Dictionary.h"

Train::Train() :
	__word(null)
{

}

Train::~Train()
{

}

bool Train::GetFirstWord()
{
	// dont delete because the word is
	// stored in lastList and also delete
	//if (__word)
	//	delete __word;

	__word = __WCtrl->GetFirstWordN(__llProv.GetArray());
	if (!__word)
	{
		Dictionary *pDic = new Dictionary();
		pDic->Init();

		// remove this from Frame
		Utils::ShowFront((Form*) pDic, this);

		// create new train
		// because this is called from OnInitialize
		// and return with false ->
		// NOT INITIALIZED SUCCESS
		Train *pTrain = new Train();
		pTrain->Init();
		pDic->SetBackForm(*pTrain);

		return false;
	}
	else if (__lblTest != null)
	{
		__lblTest->SetText(__word->GetTestWord());
		__lblTest->Draw();
		__lblTest->Show();
	}
	return true;
}

result Train::OnInitializing(void)
{
	if (!CommonSetting::GetInstance().NSHTrain)
		ShowInfoDlg();

	__lblTest = static_cast<Label *> (GetControl(L"IDC_TEST"));

	if (!GetFirstWord())
		return E_FAILURE;

	__lastList = static_cast<ListView* >(GetControl(L"IDC_LASTLIST"));
	__lastList->SetItemProvider(__llProv);
	__lastList->AddListViewItemEventListener(__llProv);
	return E_SUCCESS;
}

void Train::PrepareFooter()
{
	BaseWordForm::PrepareFooter();
	Footer * footer = GetFooter();
	if (footer)
	{
		Bitmap * pB1 = Utils::GetBitmap("bg_listener_normal.png");
		FooterItem f1;
		f1.Construct(ID_BTN_DONTKNOW);
		f1.SetIcon(FOOTER_ITEM_STATUS_NORMAL ,pB1);
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
	Osp::Graphics::Bitmap *info = Utils::GetBitmap(L"ic_dictionary.png");
	//	Osp::Graphics::Bitmap *reset = Utils::GetBitmap(L"ic_reset.png");
	__pContextMenu->AddItem(Utils::GetString(L"IDS_DIC_MENU_DICTIONARY"), ID_DICTIONARY, *info);
	//	__pContextMenu->AddItem(Utils::GetString(L"IDS_DIC_MENU_RESET_DB"), ID_MENU_RESETDB, *reset);
}

String Train::GetResourceID()
{
	return L"IDF_TRAIN";
}

void Train::UpdateWord(bool know)
{
	if (__word)
	{
		__word->SetKnow(know);
		__WCtrl->UpdateWord(*__word);

		__llProv.AddWord(*__word);
		__lastList->UpdateList();
		__lastList->Draw();
		__lastList->Show();
	}


}

void Train::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	static bool bswitch = false;

	bswitch = !bswitch;

	if (!bswitch)
	{
		return;
	}

	if (ID_BTN_KNOW == actionId)
	{
		AppLog("know");
		UpdateWord(true);
		GetFirstWord();
	}
	else if (ID_BTN_DONTKNOW == actionId)
	{
		AppLog("dont know");
		UpdateWord(false);
		GetFirstWord();
	}
	else
	{
		BaseWordForm::OnActionPerformed(source, actionId);
	}
}
