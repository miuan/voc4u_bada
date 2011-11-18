/*
 * Dictionary.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "Dictionary.h"
#include "forms/init/Init.h"

Dictionary::Dictionary() :
	__info(null), __pContextMenu(null)
{

}

Dictionary::~Dictionary()
{
	if (__info)
		delete __info;
	if (__pContextMenu)
		delete __pContextMenu;
}

void Dictionary::SetupInitSetting()
{
	for (int i = 0; i != LangSetting::NUM_LESSON; i++)
	{

		__pList->SetItemChecked(i, saveState[i]);
	}
}

void Dictionary::InitLessonState()
{
	for (int i = 0; i != LangSetting::NUM_LESSON; i++)
	{
		initState[i] = __WCtrl->GetLessonEnabled((i + 1));
		saveState[i] = initState[i];
	}
}

bool Dictionary::Init()
{
	CommonSetting *cs = &CommonSetting::GetInstance();
	cs->lern = L"EN";
	cs->native = L"CS";
	cs->Store();

	BaseWordForm::Init();
	__pList = static_cast<ListView *> (GetControl(L"IDC_LESSON"));
	__pList->SetItemProvider(*this);
	__pList->AddListViewItemEventListener(*this);

	return true;
}

void Dictionary::ShowInfoDlg()
{
	if (__info)
		delete __info;

	__info = new Information();
	if (__info)
	{
		__info->SetType(IDS_DICTIONARY);
		__info->ShowPopup(this);
	}
}

void Dictionary::PrepareFooter()
{
	Footer *footer = GetFooter();
	if (footer)
	{
		ButtonItem btnSave;
		btnSave.Construct(BUTTON_ITEM_STYLE_ICON, ID_MENU);
		btnSave.SetIcon(BUTTON_ITEM_STATUS_NORMAL, Utils::GetBitmap(L"ic_menu.png"));
		footer->SetButton(BUTTON_POSITION_LEFT, btnSave);
		footer->SetBackButton();
		footer->SetBackButtonEnabled(true);
	}
	footer->AddActionEventListener(*this);
}

void Dictionary::PrepareContextMenu()
{
	__pContextMenu = new ContextMenu();
	__pContextMenu->Construct(Point(0, 0), CONTEXT_MENU_STYLE_LIST);
	Osp::Graphics::Bitmap *info = Utils::GetBitmap(L"ic_info.png");
	Osp::Graphics::Bitmap *reset = Utils::GetBitmap(L"ic_reset.png");
	Osp::Graphics::Bitmap *add_word = Utils::GetBitmap(L"ic_add_word.png");
	__pContextMenu->AddItem(Utils::GetString(L"IDS_DIC_MENU_INFO"), ID_MENU_INFO, *info);
	__pContextMenu->AddItem(Utils::GetString(L"IDS_DIC_MENU_RESET_DB"), ID_MENU_RESETDB, *reset);
	__pContextMenu->AddItem(Utils::GetString(L"IDS_DIC_MENU_ADD_WORD"), ID_ADD_WORD, *add_word);
	__pContextMenu->AddActionEventListener(*this);
}

result Dictionary::OnInitializing(void)
{
	if (!CommonSetting::GetInstance().NSHDictionary)
		ShowInfoDlg();

	PrepareFooter();
	PrepareContextMenu();

	InitLessonState();
	//BaseWebForm::OnInitializing();

	__WCtrl->SetLessonWorkerListener(this);
	return E_SUCCESS;
}

result Dictionary::OnTerminating(void)
{
	//BaseWebForm::OnTerminating();
	__WCtrl->SetLessonWorkerListener(null);
	return E_SUCCESS;
}

void Dictionary::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{

	//ShowInfoDlg();
	if (actionId == ID_MENU)
	{
		int hp = GetHeight();

		Footer *footer = GetFooter();
		if (footer)
			hp -= (footer->GetHeight() - 5);

		// Set the anchor position of the ContextMenu
		__pContextMenu->SetPosition(Point(10, hp));

		// Show the ContextMenu
		__pContextMenu->SetShowState(true);
		__pContextMenu->Show();

	}
	else if (actionId == ID_MENU_INFO)
	{
		ShowInfoDlg();
	}
	else if (actionId == ID_MENU_RESETDB)
	{
		MessageBox messageBox;
		messageBox.Construct(Utils::GetString("IDS_DIC_MENU_RESET_DB"), Utils::GetString("IDS_MSG_RESET_DB"), MSGBOX_STYLE_YESNO);
		// Calls ShowAndWait - draw, show itself and process events
		int modalResult = 0;
		messageBox.ShowAndWait(modalResult);
		if(modalResult == MSGBOX_RESULT_YES)
		{
			CommonSetting *cs = &CommonSetting::GetInstance();
			cs->lern = "";
			cs->native = "";
			cs->Store();
			// remove all word!
			__WCtrl->AddLesson(0, true);
			InitFrm * pInit = new InitFrm();
			pInit->Initialize();
			Utils::ShowFront(this, pInit);
		}
	}
	else BaseWordForm::OnActionPerformed(source, actionId);
}
// ListViewItemEvents
void Dictionary::OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus status)
{
	//listView.Get
	//saveState[index]
}

void Dictionary::OnListViewItemLongPressed(Osp::Ui::Controls::ListView &listView, int index, int elementId, bool &invokeListViewItemCallback)
{
}

void Dictionary::OnListViewItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status)
{
	bool add = status == LIST_ITEM_STATUS_CHECKED;
	__WCtrl->AddLesson(index + 1, !add);
	saveState[index] = add;
	listView.UpdateList();
}

void Dictionary::OnListViewItemSwept(Osp::Ui::Controls::ListView &listView, int index, Osp::Ui::Controls::SweepDirection direction)
{
}

CustomItem *Dictionary::CreateLessonItem(int itemWidth, int lesson)
{
	ListAnnexStyle style = LIST_ANNEX_STYLE_MARK;
	CustomItem *pItem = new CustomItem();
	pItem->Construct(Osp::Graphics::Dimension(itemWidth, 100), style);
	pItem->SetBackgroundColor(LIST_ITEM_DRAWING_STATUS_NORMAL, LangSetting::LESSON_COLORS[lesson - 1]);

	String name = LangSetting::GetNameOfLesson(lesson);
	pItem->AddElement(Rectangle(5, 5, 250, 50), ID_FORMAT_STRING, name, true);
	//pItem->

	SetupInitSetting();
	return pItem;
}

// list item provider
Osp::Ui::Controls::ListItemBase * Dictionary::CreateItem(int index, int itemWidth)
{
	CustomItem *pItem = CreateLessonItem(itemWidth, index + 1);

	return pItem;
}

bool Dictionary::DeleteItem(int index, Osp::Ui::Controls::ListItemBase *pItem, int itemWidth)
{
	return false;
}

int Dictionary::GetItemCount(void)
{
	return LangSetting::NUM_LESSON;
}

void Dictionary::OnLessonTask(const int lesson)
{
	AppLog("OnLessonDone %i", lesson);
}

