#include "Init.h"
#include <FGraphics.h>

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

using namespace Osp::Graphics;

InitFrm::InitFrm(void) :
	__pLern(null), __pNative(null)
{
	__infoDlg.SetType(L"INIT");
}

InitFrm::~InitFrm(void)
{
}

bool InitFrm::Initialize()
{
	// Construct an XML form
	Construct(L"IDF_INIT");
	__setting = &CommonSetting::GetInstance();
	return true;
}

result InitFrm::OnInitializing(void)
{
	result r = E_SUCCESS;

	__infoDlg.ShowPopup(this);
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

result InitFrm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void InitFrm::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
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
		__setting->Store();
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

		Dictionary * init = new Dictionary();
		init->Init();
		pFrame->AddControl(*init);
		pFrame->SetCurrentForm(*init);
		init->RequestRedraw(true);
		pFrame->RemoveControl(*this);


				AppLog("ahoj");
//		 MessageBox messageBox;
//		    messageBox.Construct(L"My MessageBox", L"This is MessageBox Sample Code.", MSGBOX_STYLE_OK, 3000);
//
//		    // Calls ShowAndWait - draw, show itself and process events
//		    int modalResult = 0;
//		    messageBox.ShowAndWait(modalResult);
//
//		    switch(modalResult)
//		    {
//		    case MSGBOX_RESULT_OK:
//		        // Todo:
//		        break;
//
//		    default:
//		        break;
//		    }
		break;
	}
	default:
		break;
	}

}

void InitFrm::onSelectLang(int type, Locale &selected)
{
	String str, code;
	selected.GetLanguageName(str);
	code = selected.GetLanguageCodeString();
	Osp::Graphics::Point bpoint(350,25);
	Osp::Graphics::Bitmap * icon = LangSetting::GetIcon(selected);


	if (type == ID_BUTTON_NATIVE)
	{
		__pbtnNative->SetText(str);
		__pbtnNative->SetNormalBitmap(bpoint, *icon);
		__pNative = &selected;

		// it's necessary the lern and native must be differend
		if (__pNative == __pLern)
		{
			__pLern = null;
			AppResource *res = Application::GetInstance()->GetAppResource();
			String title;
			if (res->GetString(L"IDS_NOT_SELECTED_YET", title) == E_SUCCESS)
			__pbtnLern->SetText(title);
			//__pbtnLern->SetNormalBitmap(bpoint, (Bitmap*)null);
		}

		__setting->native = code;
	}
	if(type == ID_BUTTON_LERN)
	{
		__pbtnLern->SetText(str);
		__pbtnLern->SetNormalBitmap(bpoint, *icon);
		__pLern =&selected;
		__setting->lern = code;
	}

	__pbtnBegin->SetEnabled(__pLern && __pNative);
	//__pButtonOk->Show();
					//__pButtonOk->Draw();
					Draw();
					Show();

				}
