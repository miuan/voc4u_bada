/*
 * Dictionary.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "Dictionary.h"

Dictionary::Dictionary()
{

}

Dictionary::~Dictionary()
{

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
	BaseWordForm::Init();
	__pList = static_cast<ListView *> (GetControl(L"IDC_LESSON"));
	__pList->SetItemProvider(*this);
	__pList->AddListViewItemEventListener(*this);

	return true;
}

result Dictionary::OnInitializing(void)
{
	Footer *footer = GetFooter();

	if (footer)
	{
		FooterItem btnSave;
		btnSave.Construct(ID_ADD_WORD);
		btnSave.SetText(GetString("IDS_SAVE_DICTIONARY"));
		footer->AddItem(btnSave);
	}
	footer->AddActionEventListener(*this);

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
	if (actionId == ID_ADD_WORD)
	{
		//		for (int i = 0; i != LangSetting::NUM_LESSON; i++)
		//		{
		//			saveState[i] = __pList->IsItemChecked(i);
		//		}

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
	__WCtrl->AddLesson(index, !add);
	saveState[index] =  add;
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

