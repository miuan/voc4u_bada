#include "Init.h"
#include <FGraphics.h>
#include "ctrl/WordCtrl.h"

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

	__pbtnLern = static_cast<Button *> (GetControl(L"IDC_BTN_LERN"));
	if (__pbtnLern != null)
	{
		__pbtnLern->SetActionId(ID_BUTTON_LERN);
		__pbtnLern->AddActionEventListener(*this);
	}

	__pbtnMenu = static_cast<Button *> (GetControl(L"IDC_BTN_BEGIN"));
	if (__pbtnMenu != null)
	{

		__pbtnMenu->SetActionId(ID_BUTTON_BEGIN);
		__pbtnMenu->AddActionEventListener(*this);
		__pbtnMenu->SetEnabled(false);
	}

	__pbtnTrain = static_cast<Button *> (GetControl(L"IDC_BTN_TRAIN"));
	if (__pbtnTrain != null)
	{

		__pbtnTrain->SetActionId(ID_BUTTON_TRAIN);
		__pbtnTrain->AddActionEventListener(*this);
		__pbtnTrain->SetEnabled(false);
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
		else __pPopup->Init(null);

		//__pPopup->Draw();
		__pPopup->SetShowState(true);
		__pPopup->Show();

		break;
	}
	case ID_BUTTON_BEGIN:
	{
		__setting->Store();
		WordCtrl::GetInstance()->LoadLesson(1, false);

		//Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

		//		Dictionary * init = new Dictionary();
		//		init->Init();
		//		pFrame->AddControl(*init);
		//		pFrame->SetCurrentForm(*init);
		//		init->RequestRedraw(true);
		//		pFrame->RemoveControl(*this);
		Dashboard *dash = new Dashboard();
		dash->Init();

		Utils::ShowFront(dash, this);
		break;
	}
	case ID_BUTTON_TRAIN:
	{
		__setting->Store();
		WordCtrl::GetInstance()->LoadLesson(1);

		Thread::GetCurrentThread()->Sleep(500);
		Dashboard *dash = new Dashboard();
		dash->Init();

		Utils::ShowFront(dash, this);

		Train *train = new Train();
		train->Init();
		train->SetBackForm(*dash);

		Utils::ShowFront(train, null);
	}
	default:
		break;
	}

}

void InitFrm::onSelectLang(int type, Locale &selected)
{
	String str, code;
	selected.GetLanguageName(str);
	// be carefully with this function
	// when changet to LanguageCode you must changed
	// also in LangSetting::GetLocaleFromCode
	code = selected.GetCountryCodeString();

	Osp::Graphics::Bitmap * icon = LangSetting::GetIconN(selected);

	int posY = __pbtnNative->GetHeight() / 2 - icon->GetHeight()/ 2;

	Osp::Graphics::Point bpoint(30, posY);

	AddToDeleteList(icon);

	// for icon
	str = "   " + str;

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
	if (type == ID_BUTTON_LERN)
	{
		__pbtnLern->SetText(str);
		__pbtnLern->SetNormalBitmap(bpoint, *icon);
		__pLern = &selected;
		__setting->lern = code;
	}

	__pbtnMenu->SetEnabled(__pLern && __pNative);
	__pbtnTrain->SetEnabled(__pLern && __pNative);
	//__pButtonOk->Show();
	//__pButtonOk->Draw();
	Draw();
	Show();

}
