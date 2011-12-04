/*
 * BaseTrainer.cpp
 *
 *  Created on: 4.12.2011
 *      Author: m1uan
 */

#include "BaseTrainer.h"

BaseTrainer::BaseTrainer(): __word(null), __lblTest(null), __lastList(null)
{
	// TODO Auto-generated constructor stub

}

BaseTrainer::~BaseTrainer()
{
	// TODO Auto-generated destructor stub
}

bool BaseTrainer::GetFirstWord()
{
	// dont delete because the word is
	// stored in lastList and also delete
	//if (__word)
	//	delete __word;

	__word = __WCtrl->GetFirstWordN(GetProvider().GetArray());
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
		BaseTrainer *pTrain = NewThisN();
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

result BaseTrainer::OnInitializing(void)
{
	if (!CommonSetting::GetInstance().NSHTrain)
		ShowInfoDlg();

	__lblTest = static_cast<Label *> (GetControl(L"IDC_TEST"));

	if (!GetFirstWord())
		return E_FAILURE;

	__lastList = static_cast<ListView*> (GetControl(L"IDC_LASTLIST"));
	__lastList->SetItemProvider(GetProvider());
	__lastList->AddListViewItemEventListener(GetProvider());

	return E_SUCCESS;
}
