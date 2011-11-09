#include "Init.h"
#include <FGraphics.h>

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

using namespace Osp::Graphics;

Init::Init(void) :
	__pLern(null), __pNative(null)
{
}

Init::~Init(void)
{
}

bool Init::Initialize()
{
	// Construct an XML form
	Construct(L"IDF_INIT");

	return true;
}

result Init::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	// Get a button via resource ID
	__pbtnNative = static_cast<Button *> (GetControl(L"IDC_BTN_NATIVE"));
	if (__pbtnNative != null)
	{
		__pbtnNative->SetActionId(ID_BUTTON_NATIVE);
		__pbtnNative->AddActionEventListener(*this);
	}

	__pbtnLern = static_cast<Button *>(GetControl(L"IDC_BTN_LERN"));
	if (__pbtnLern != null)
	{
		__pbtnLern->SetActionId(ID_BUTTON_LERN);
		__pbtnLern->AddActionEventListener(*this);
	}

	__pbtnBegin = static_cast<Button *>(GetControl(L"IDC_BTN_BEGIN"));
	if (__pbtnBegin != null)
	{
		AppLog("btnbegin");
		__pbtnBegin->SetActionId(ID_BUTTON_BEGIN);
		__pbtnBegin->AddActionEventListener(*this);
		__pbtnBegin->SetEnabled(false);
	}

	return r;
}

result Init::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void Init::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	switch (actionId)
	{
	case ID_BUTTON_LERN:
	case ID_BUTTON_NATIVE:
	{
		// Creates a Popup
		LangSelect * __pPopup = new LangSelect(actionId, this);

		if (actionId == ID_BUTTON_LERN)
			__pPopup->Init(__pNative);
		else
			__pPopup->Init(null);

		//__pPopup->Draw();
		__pPopup->SetShowState(true);
		__pPopup->Show();


		break;
	}
	case ID_BUTTON_BEGIN:
	{
		CommonSetting::GetInstance().Store();
		AppLog("ahoj");
		 MessageBox messageBox;
		    messageBox.Construct(L"My MessageBox", L"This is MessageBox Sample Code.", MSGBOX_STYLE_OK, 3000);

		    // Calls ShowAndWait - draw, show itself and process events
		    int modalResult = 0;
		    messageBox.ShowAndWait(modalResult);

		    switch(modalResult)
		    {
		    case MSGBOX_RESULT_OK:
		        // Todo:
		        break;

		    default:
		        break;
		    }
		break;
	}
	default:
		break;
	}

}

void Init::onSelectLang(int type, Locale &selected)
{
	String str, code;
	selected.GetLanguageName(str);
	code = selected.GetLanguageCodeString();

	if (type == ID_BUTTON_NATIVE)
	{
		__pbtnNative->SetText(str);
		__pNative = &selected;

		// it's necessary the lern and native must be differend
		if (__pNative == __pLern)
		{
			__pLern = null;
			AppResource *res = Application::GetInstance()->GetAppResource();
			String title;
			if (res->GetString(L"IDS_NOT_SELECTED_YET", title) == E_SUCCESS)
			__pbtnLern->SetText(title);
		}

		CommonSetting::GetInstance().native = code;
	}
	if(type == ID_BUTTON_LERN)
	{
		__pbtnLern->SetText(str);
		__pLern =&selected;
		CommonSetting::GetInstance().lern = code;
	}

	__pbtnBegin->SetEnabled(__pLern && __pNative);
	//__pButtonOk->Show();
					//__pButtonOk->Draw();
					Draw();
					Show();

				}
