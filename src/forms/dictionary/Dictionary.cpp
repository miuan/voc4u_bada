/*
 * Dictionary.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "Dictionary.h"
#include "forms/init/Init.h"

Dictionary::Dictionary() :
	__info(null)
{

}

Dictionary::~Dictionary()
{
	if (__info)
		delete __info;
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
	GetLessonsInProgress();
	for (int i = 0; i != LangSetting::NUM_LESSON; i++)
	{
		saveState[i] = __WCtrl->GetLessonLoaded((i + 1));
	}
}

bool Dictionary::Init()
{
//	CommonSetting *cs = &CommonSetting::GetInstance();
//	cs->lern = L"ES";
//	cs->native = L"CS";
//	cs->Store();

	BaseWordForm::Init();
	__pList = static_cast<ListView *> (GetControl(L"IDC_LESSON"));
	__pList->SetItemProvider(*this);
	__pList->AddListViewItemEventListener(*this);

	return true;
}


void Dictionary::PrepareFooter()
{
	BaseWordForm::PrepareFooter();
}

void Dictionary::PrepareContextMenu()
{
	BaseWordForm::PrepareContextMenu();

	Osp::Graphics::Bitmap *info = Utils::GetBitmapN(L"ic_info.png");
	Osp::Graphics::Bitmap *reset = Utils::GetBitmapN(L"ic_reset.png");
	__pContextMenu->AddItem(Utils::GetString(L"IDS_DIC_MENU_INFO"), ID_MENU_INFO, *info);
	__pContextMenu->AddItem(Utils::GetString(L"IDS_DIC_MENU_RESET_DB"), ID_MENU_RESETDB, *reset);
}

result Dictionary::OnInitializing(void)
{
	if (!CommonSetting::GetInstance().NSHDictionary)
		ShowInfoDlg();

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

	if (actionId == ID_MENU_INFO)
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
		if (modalResult == MSGBOX_RESULT_YES)
		{
			// remove all word!
			__WCtrl->DeleteLesson(0);
			CommonSetting *cs = &CommonSetting::GetInstance();
			cs->lern = "";
			cs->native = "";
			cs->Store();

			InitFrm * pInit = new InitFrm();
			pInit->Initialize();
			Utils::ShowFront(pInit, this);
		}
	}
	else if(actionId == ID_ADD_WORD)
	{
		AddWord *aw = new AddWord();
		aw->SetResultListener(this, ID_MENU_ADD_WORD_SUCCCES);
		aw->ShowPopup(this);
		AddToDestructList(aw);
	}
	else if(actionId == ID_MENU_ADD_WORD_SUCCCES)
	{
		__pList->RefreshList(__pList->GetItemCount() -1, LIST_REFRESH_TYPE_ITEM_MODIFY);
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
	GetLessonsInProgress();

	if(__WCtrl->LoadLesson(index + 1, !add))
		__progressState[index] = true;

	saveState[index] = add;
	listView.UpdateList();
}

void Dictionary::OnListViewItemSwept(Osp::Ui::Controls::ListView &listView, int index, Osp::Ui::Controls::SweepDirection direction)
{
}

void Dictionary::AddItemPreparing(CustomItem *& pItem, int itemWidth)
{
	result r;

	EnrichedText* pEnrichedText = new EnrichedText();
	r = pEnrichedText->Construct(Dimension(itemWidth, 250));
	pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
	pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_RIGHT);
	TextElement * pTextElement = new TextElement();
	r = pTextElement->Construct(Utils::GetString("IDS_PREPARING"));

	Font font;
	font.Construct(FONT_STYLE_PLAIN, 25);
	pTextElement->SetFont(font);
	pEnrichedText->Add(*pTextElement);

	AddToDestructList(pTextElement);
	AddToDestructList(pEnrichedText);
	int width, height;
	pEnrichedText->GetSize(width, height);
	pItem->AddElement(Rectangle(0, 5, itemWidth -10, 30), ID_FORMAT_PREPARING, *pEnrichedText);
}

void Dictionary::AddItemTitle(CustomItem *& pItem, String name, int itemWidth)
{
	result r;

	EnrichedText* pEnrichedText = new EnrichedText();
	r = pEnrichedText->Construct(Dimension(itemWidth, 200));

	TextElement * pTextElement = new TextElement();
	r = pTextElement->Construct(name);

	Font font;
	font.Construct(FONT_STYLE_BOLD, 40);
	pTextElement->SetFont(font);

	pEnrichedText->Add(*pTextElement);

	AddToDestructList(pTextElement);
	AddToDestructList(pEnrichedText);
	pItem->AddElement(Rectangle(10, 5, itemWidth -10, 50), ID_FORMAT_STRING, *pEnrichedText);
}

void Dictionary::AddItemExamples(CustomItem *& pItem, int itemWidth, String examples)
{
	result r;

	EnrichedText* pEnrichedText = new EnrichedText();
	r = pEnrichedText->Construct(Dimension(itemWidth, 200));
	pEnrichedText->SetTextWrapStyle(TEXT_WRAP_WORD_WRAP);
	pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
	pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);

	TextElement * pTextElement = new TextElement();
	r = pTextElement->Construct(examples);

	Font font;
	font.Construct(FONT_STYLE_PLAIN, 20);
	pTextElement->SetFont(font);

	pEnrichedText->Add(*pTextElement);

	AddToDestructList(pTextElement);
	AddToDestructList(pEnrichedText);

	pItem->AddElement(Rectangle(10, 45, itemWidth-80, ITEM_HEIGHT-60), ID_FORMAT_EXAMPLES, *pEnrichedText);
}

CustomItem *Dictionary::CreateLessonItem(int itemWidth, int lesson)
{

	ListAnnexStyle style = LIST_ANNEX_STYLE_MARK;
	CustomItem *pItem = new CustomItem();
	pItem->Construct(Osp::Graphics::Dimension(itemWidth, ITEM_HEIGHT), style);
	pItem->SetBackgroundColor(LIST_ITEM_DRAWING_STATUS_NORMAL, LangSetting::LESSON_COLORS[lesson - 1]);

	String name = LangSetting::GetNameOfLesson(lesson);

	if(__progressState[lesson-1])
		AddItemPreparing(pItem, itemWidth);
	AddItemTitle(pItem, name, itemWidth);

	int count;
	wchar_t ** words = LangSetting::GetInitDataN(CommonSetting::GetInstance().lern, lesson, count);
	String examples = L"";
	count = count > EXAMPLES_MAX ? EXAMPLES_MAX : count;

	bool first = true;
	for (int i = 0; i != count; i++)
	{
		int indexOfComa;
		String word = words[i];
		//word.IndexOf(",", 0, indexOfComa);
		if(word.IndexOf(",", 0, indexOfComa) == E_SUCCESS)
		{
			String neww;
			word.SubString(0, indexOfComa, neww);
			word = neww;
		}

		if(!first)
			examples.Append(L", ");
		examples.Append(word);
		first = false;
	}

	AddItemExamples( pItem, itemWidth, examples);
	SetupInitSetting();
	return pItem;
}

CustomItem *Dictionary::CreateCustomWordItem(int itemWidth)
{

	ListAnnexStyle style = LIST_ANNEX_STYLE_NORMAL;
	CustomItem *pItem = new CustomItem();
	pItem->Construct(Osp::Graphics::Dimension(itemWidth, ITEM_HEIGHT), style);
	pItem->SetBackgroundColor(LIST_ITEM_DRAWING_STATUS_NORMAL, LangSetting::CUSTOM_WORD);

	String examples = L"";

	ArrayList *words = __WCtrl->GetWordsN(WordCtrl::CUSTOM_WORD_LESSON_ID);

	if(words && words->GetCount() > 0)
	{
		int cnt = words->GetCount();
		for(int i = 0; i!= cnt; i++)
		{
			Word * w = static_cast<Word*>(words->GetAt(i));
			if(i > 0)
				examples.Append(",");
			examples.Append(w->__lern);
		}

		words->RemoveAll(true);
		delete words;
	}
	else
		examples = Utils::GetString("IDS_EMPTY_CUSTOM_LIST");

	String name = Utils::GetString("IDS_CUSTOM_WORD_ITEM");
	AddItemTitle(pItem, name, itemWidth);
	AddItemExamples(pItem, itemWidth, examples);

	return pItem;
}

// list item provider
Osp::Ui::Controls::ListItemBase * Dictionary::CreateItem(int index, int itemWidth)
{
	CustomItem *pItem;
	if (index < LangSetting::NUM_LESSON)
		pItem = CreateLessonItem(itemWidth, index + 1);
	else pItem = CreateCustomWordItem(itemWidth);

	return pItem;
}

bool Dictionary::DeleteItem(int index, Osp::Ui::Controls::ListItemBase *pItem, int itemWidth)
{
	return false;
}

int Dictionary::GetItemCount(void)
{
	// TODO: add special item for custom words
	return LangSetting::NUM_LESSON +1;
}

void Dictionary::GetLessonsInProgress()
{
    int count;
    int *lessons = __WCtrl->GetWorkerTaskLessonInProgressN(count);
    if(count > 0){
        for(int i = 0;i != count;i++){
            int pos = Math::Abs(lessons[i]) - 1;
            __progressState[pos] = true;
        }
    }

    if(lessons)
    	delete lessons;

}

void Dictionary::OnLessonTask(const int lesson)
{
	AppLog("OnLessonDone %i", lesson);
	int position = Math::Abs(lesson) -1;
    GetLessonsInProgress();
    __progressState[position] = false;
	__pList->RefreshList(position, LIST_REFRESH_TYPE_ITEM_MODIFY);
	__pList->UpdateList();
}

