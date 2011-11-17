/*
 * LangSelect.cpp
 *
 *  Created on: 23.10.2011
 *      Author: m1uan
 */

#include "Information.h"
#include "setting/CommonSetting.h"

void Information::SetType(String type)
{
    __type = type;
}

Information::Information()
{
    SetType(L"");
}

Information::Information(String type)
{
    SetType(type);
}

Information::~Information()
{

}



bool Information::ShowPopup(Form * parent)
{
	String titleid = L"IDS_FORM_";
	titleid.Append(__type);
	String title = Utils::GetString(titleid);
	//                IDS_INFORMATION_DICTIONARY
	String textid = L"IDS_INFORMATION_";
	textid.Append(__type);
	String text = Utils::GetString(textid);

	__pParentForm = parent;
	result result = Construct(L"IDP_INFORMATION");

	SetTitleText(title);

	__chkNoShowMore = static_cast<CheckButton *> (GetControl("IDC_NOSHOWMORE"));
	if (__chkNoShowMore)
	{
		bool checked = false;
		SetupCheckbox(checked);
		__chkNoShowMore->SetSelected(checked);
	}

	EditArea *peaText = static_cast<EditArea *> (GetControl("IDC_TEXT"));
	if (peaText)
	{
		peaText->SetText(text);
		peaText->SetEnabled(false);
	}

	Button *pbtnCancel = static_cast<Button *> (GetControl("IDC_BTN_CANCEL"));
	if (pbtnCancel)
	{
		pbtnCancel->AddActionEventListener(*this);
		pbtnCancel->SetActionId(ID_BTN_CANCEL);
	}

	SetShowState(true);
	Show();
	return result;
}


void Information::SetupCheckbox(bool & checked)
{
	CommonSetting *cs = &CommonSetting::GetInstance();
	if (__type == String(IDS_DICTIONARY))
	{
		checked = cs->NSHDictionary;
	}
	else
	{
		checked = true;
	}
}

void Information::SetupCommonSetting(bool checked)
{
	CommonSetting *cs = &CommonSetting::GetInstance();

	if (__type == String(IDS_DICTIONARY))
	{
		cs->NSHDictionary = checked;
	}

	cs->Store();
	cs->Restore();
}

void Information::OnActionPerformed(const Osp::Ui::Control & source, int actionId)
{

	if (actionId == ID_BTN_CANCEL)
	{
		if (__chkNoShowMore)
		{
			SetupCommonSetting(__chkNoShowMore->IsSelected());
		}

		SetShowState(false);
		if (__pParentForm)
		{
			__pParentForm->Draw();
			__pParentForm->Show();
		}
	}
}
