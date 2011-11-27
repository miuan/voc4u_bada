/*
 * LangSelect.cpp
 *
 *  Created on: 23.10.2011
 *      Author: m1uan
 */

#include "AddWord.h"

AddWord::AddWord() : __resultListener(null), __resultActionCode(0)
{

}

AddWord::~AddWord()
{

}

bool AddWord::ShowPopup(Form * parent)
{
	__pParentForm = parent;
	result result = Construct(L"IDP_ADD_WORD");
	GetControl(L"IDC_BTN_ADD");
	Button *pbtnAdd = static_cast<Button *> (GetControl("IDC_BTN_ADD"));
	if (pbtnAdd)
	{
		pbtnAdd->AddActionEventListener(*this);
		pbtnAdd->SetActionId(ID_BTN_ADD);
	}

	Button *pbtnCancel = static_cast<Button *> (GetControl("IDC_BTN_CANCEL"));
	if (pbtnCancel)
	{
		pbtnCancel->AddActionEventListener(*this);
		pbtnCancel->SetActionId(ID_BTN_CANCEL);
	}

	__pLern = static_cast<EditField *> (GetControl("IDC_LERN"));
	__pNative = static_cast<EditField *> (GetControl("IDC_NATIVE"));
	AppAssert(__pLern && __pNative);
	if (!__pLern || !__pNative)
		return false;

	SetShowState(true);
	Show();
	return result;
}

void AddWord::showErrorMessageBox()
{
	String body;
	Application::GetInstance()->GetAppResource()->GetString(L"IDS_MSG_MUST_BE_FILL_BOTH_EDIT_FIELD", body);
	MessageBox messageBox;
	messageBox.Construct(GetTitleText(), body, MSGBOX_STYLE_OK, 3000);
	// Calls ShowAndWait - draw, show itself and process events
	int modalResult = 0;
	messageBox.ShowAndWait(modalResult);
}

void AddWord::OnActionPerformed(const Osp::Ui::Control & source, int actionId)
{
	if (actionId == ID_BTN_ADD)
	{
		String native = __pNative->GetText();
		String lern = __pLern->GetText();

		if (native.GetLength() == 0 || lern.GetLength() == 0)
		{
			showErrorMessageBox();
			return;
		}

		WordCtrl * wc = WordCtrl::GetInstance();
		if (wc)
		{
			Word w(-1, 0, lern, native, 1, 1);
			if(wc->AddWord(w) && __resultListener)
				__resultListener->OnActionPerformed(source, __resultActionCode);
		}
	}

	SetShowState(false);
	if (__pParentForm)
	{
		__pParentForm->Draw();
		__pParentForm->Show();
	}
}
