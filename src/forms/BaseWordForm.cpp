/*
 * BaseWordForm.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "BaseWordForm.h"
#include "dialogs/information/Information.h"
#include "forms/dictionary/Dictionary.h"

Bitmap * BaseWordForm::__pBGLogo = null;
Bitmap * BaseWordForm::__pICHeader = null;
SpeechToTextHelper *BaseWordForm::__pSTTH = null;
BaseWordForm::BaseWordForm() :
	__pAddWordDlg(null), __pContextMenu(null), __pBackForm(null)
{
	__destructList.Construct(2000);
}

BaseWordForm::~BaseWordForm()
{
	if (__pAddWordDlg)
		delete __pAddWordDlg;

	if (__destructList.GetCount() > 0)
	{
		__destructList.RemoveAll(true);
	}
}

void BaseWordForm::PrepareHeader()
{
	Header *header = GetHeader();

	if (header)
	{
		if (!__pICHeader)
			__pICHeader = Utils::GetBitmap("ic_header.png");

		header->SetTitleIcon(__pICHeader);
		header->RemoveAllButtons();
		header->RemoveAllItems();

		if (__pContextMenu)
		{
			ButtonItem btnMenu;
			btnMenu.Construct(BUTTON_ITEM_STYLE_ICON, ID_MENU);
			btnMenu.SetIcon(BUTTON_ITEM_STATUS_NORMAL, Utils::GetBitmap(L"ic_menu.png"));
			header->SetButton(BUTTON_POSITION_RIGHT, btnMenu);
		}

		//		ButtonItem btnAddWord;
		//		 btnAddWord.Construct(BUTTON_ITEM_STYLE_ICON, ID_ADD_WORD);
		//		 //btnAddWord.SetText(GetString("IDS_ADD_WORD_BUTTON"));
		//		 btnAddWord.SetIcon(BUTTON_ITEM_STATUS_NORMAL, Utils::GetBitmap(L"ic_add_word.png"));
		//		 HeaderItem headerItem1;
		//		 header->SetTitleText("voc4u");
		//		 header->SetButton(BUTTON_POSITION_RIGHT, btnAddWord);
		//		 header->PlayWaitingAnimation(HEADER_ANIMATION_POSITION_BUTTON_LEFT);
		header->SetTitleText("Voc4u");
		header->AddActionEventListener(*this);
	}
}

void BaseWordForm::PrepareFooter()
{
	Footer *footer = GetFooter();

	if (footer)
	{
		// cleaning because function can be call
		// from SetBackForm
		footer->RemoveAllButtons();
		footer->RemoveAllItems();
		footer->RemoveBackButton();

		if (__pBackForm)
		{
			footer->SetBackButton();
			footer->SetBackButtonEnabled(true);
			SetFormBackEventListener(this);
		}
		footer->AddActionEventListener(*this);
	}

}

bool BaseWordForm::Init()
{
	__WCtrl = WordCtrl::GetInstance();

	Construct(GetResourceID());

	// context menu must be first
	// because when is created
	// show menu button in footer
	PrepareContextMenu();
	PrepareHeader();
	PrepareFooter();

	return true;
}

void BaseWordForm::SetBackForm(Form &frm)
{
	__pBackForm = &frm;

	//if (IsVisible())
	PrepareFooter();
}

Form * BaseWordForm::GetBackForm()
{
	return __pBackForm;
}

String BaseWordForm::GetString(Osp::Base::String ID)
{
	return Utils::GetString(ID);
}

result BaseWordForm::OnInitializing()
{
	return E_SUCCESS;
}

void BaseWordForm::ShowDictionary()
{
	Dictionary *pDic = new Dictionary();
	pDic->Init();
	pDic->SetBackForm(*this);

	Utils::ShowFront((Form*) pDic);
}

void BaseWordForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	switch (actionId)
	{
	case ID_ADD_WORD:
	{
		if (__pAddWordDlg)
			delete __pAddWordDlg;

		__pAddWordDlg = new AddWord();
		__pAddWordDlg->ShowPopup(this);

		break;
	}
	case ID_MENU:
	{
		int hp = 0;
		int wp = 0;
		Header *header = GetHeader();

		if (header)
		{
			int posy = GetBounds().height - GetClientAreaBounds().height;

			Footer * footer = GetFooter();
			if (footer)
				posy -= footer->GetHeight();

			hp = (posy - 10);
			wp = header->GetWidth() - 10;
		}
		// Set the anchor position of the ContextMenu
		__pContextMenu->SetPosition(Point(wp, hp));

		// Show the ContextMenu
		__pContextMenu->SetShowState(true);
		__pContextMenu->Show();

		break;
	}
	case ID_DICTIONARY:
	{
		ShowDictionary();
		break;
	}
	case ID_MENU_INFO:
	{
		ShowInfoDlg();
		break;
	}
	}
}

void BaseWordForm::PrepareContextMenu()
{
	__pContextMenu = new ContextMenu();
	__pContextMenu->Construct(Point(0, 0), CONTEXT_MENU_STYLE_LIST);
	Osp::Graphics::Bitmap *add_word = Utils::GetBitmap(L"ic_add_word.png");

	__pContextMenu->AddItem(Utils::GetString(L"IDS_DIC_MENU_ADD_WORD"), ID_ADD_WORD, *add_word);
	if (GetShowInfoCode())
	{
		Osp::Graphics::Bitmap *info = Utils::GetBitmap(L"ic_info.png");
		__pContextMenu->AddItem(Utils::GetString(L"IDS_DIC_MENU_INFO"), ID_MENU_INFO, *info);
	}

	__pContextMenu->AddActionEventListener(*this);
}

void BaseWordForm::AddToDestructList(Object *obj)
{
	__destructList.Add(*obj);
}

wchar_t * BaseWordForm::GetShowInfoCode()
{
	return null;
}

void BaseWordForm::ShowInfoDlg()
{
	wchar_t * code = GetShowInfoCode();

	if (!code)
		return;

	Information * info = new Information();
	if (info)
	{
		info->SetType(code);
		info->ShowPopup(this);
		AddToDestructList(info);
	}
}

void BaseWordForm::OnFormBackRequested(Osp::Ui::Controls::Form &source)
{
	if (__pBackForm)
	{
		Utils::ShowFront(__pBackForm, &source);
	}
	else
	{
		AppLogDebug("call OnFormBackRequested, but the __pBackForm isn\'t set!");
	}
}

result BaseWordForm::OnDraw(void)
{
	result r = Form::OnDraw();
	Rectangle bound = GetBounds();
	Canvas * canvas = GetCanvasN(bound);

	if (!__pBGLogo)
		__pBGLogo = Utils::GetBitmap("bg_logo.png");

	int x = bound.width / 2 - (__pBGLogo->GetWidth() / 2);
	int y = bound.height - __pBGLogo->GetHeight() - 15;

	Footer * footer = GetFooter();
	if (footer)
	{
		y -= footer->GetHeight();
	}

	canvas->DrawBitmap(Point(x, y), *__pBGLogo);

	delete canvas;

	return r;
}

void BaseWordForm::SetSpeechToTextListener(ISpeechToTextEventListener *isttl)
{
	// when is isttl null not create new helper
	if (!__pSTTH && isttl != null)
	{
		AppLogDebug("__pSTTH = new SpeechToTextHelper()");
		__pSTTH = new SpeechToTextHelper();
	}

	// must set isttl before init because
	// after init success will call __pSTTH->OnSpeechToTextInitialized
	// and __pSTTH->OnSpeechToTextInitialized call isttl->OnSpeechToTextInitialized
	if (__pSTTH)
	{
		__pSTTH->SetListener(isttl);
		// when was initialized before
		// call OnSpeechToTextInitialized manualy
//		if (isttl && __pSTTH->IsInitialized())
//		{
//			AppLogDebug("__pSTTH->SetListener and __pSTTH->OnSpeechToTextInitialized()");
//			__pSTTH->OnSpeechToTextInitialized();
//		}
//		else
//			if (__pSTTH->IsNotWorks())
//		{
//			AppLogDebug("__pSTTH->SetListener and __pSTTH->OnSpeechToTextErrorOccurred(STT_ERROR_INITIALIZATION_FAILED)");
//			__pSTTH->OnSpeechToTextErrorOccurred(STT_ERROR_INITIALIZATION_FAILED);
//			delete __pSTTH;
//			__pSTTH = null;
//		}
	}

	// wasn't initialized -> init
	if (__pSTTH && !__pSTTH->IsInitialized())
	{
		AppLogDebug("call __pSTTH->Init()");
		if (!__pSTTH->Init())
		{
			delete __pSTTH;
			__pSTTH = null;
		}
	}

}

void BaseWordForm::SpeechToTextCancel()
{
	if (__pSTTH)
	{
		__pSTTH->Cancel();
	}
}

void BaseWordForm::SpeechToTextStop()
{
	if (__pSTTH)
	{
		__pSTTH->Stop();
	}
}

void BaseWordForm::SpeechToTextStart()
{
	if (__pSTTH)
	{
		__pSTTH->Start();
	}
}
