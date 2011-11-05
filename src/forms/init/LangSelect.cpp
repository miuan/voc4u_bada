/*
 * LangSelect.cpp
 *
 *  Created on: 23.10.2011
 *      Author: m1uan
 */

#include "LangSelect.h"

Locale LangSelect::__locales[] =
{ Locale(LANGUAGE_CES, COUNTRY_CZ), Locale(LANGUAGE_ENG, COUNTRY_US), Locale(LANGUAGE_DEU, COUNTRY_DE), Locale(LANGUAGE_FRA, COUNTRY_FR) };

const int LangSelect::__numLocales = 4;

LangSelect::LangSelect(int type, ILangSelectListener * lsl) : __aUsedLocales(null)
{
	__type = type;
	__langSelectListener = lsl;
}

LangSelect::~LangSelect()
{
	// TODO Auto-generated destructor stub
	delete __aUsedLocales;
	delete __pListElement;
}

bool LangSelect::Init(Locale * without)
{
	// Create Bitmap
	Bitmap *pBitmapNormal = GetBitmapN(0);
	Bitmap *pBitmapFocused = GetBitmapN(1);

	AppResource *res = Application::GetInstance()->GetAppResource();
	Frame * frame = Application::GetInstance()->GetAppFrame()->GetFrame();
	int width = frame->GetWidth() - 10;
	int height = 400;//frame->GetHeight() - 10;

	result result = Construct(false, Dimension(width, height));

	__numUsedLocales = __numLocales;
	if(without)
		__numUsedLocales -= 1;

	__aUsedLocales = new Locale*[__numUsedLocales];
	for(int i = 0, b = 0; i != __numLocales; i++)
		if(without == null || without->GetLanguageCode() != __locales[i].GetLanguageCode())
		__aUsedLocales[b++] = &__locales[i];



	String title;
	if (res->GetString(L"IDS_LANGUAGE_SELECT", title) == E_SUCCESS)
		SetTitleText(title);
	// Creates CustomListElement
	__pListElement = new CustomListElement();

	__pList = new ListView();
	__pList->Construct(Rectangle(5,5, width-10, height-10), true, false);
	__pList->SetItemProvider(*this);
	__pList->AddListViewItemEventListener(*this);
	//__list->AddCustomItemEventListener(*this);

	// Create a item format of the CustomList
	//__pCustomListItemFormat = new CustomListItemFormat();
	//__pCustomListItemFormat->Construct();
	//	__pCustomListItemFormat->AddElement(ID_LIST_TEXT,
	//			Osp::Graphics::Rectangle(10, 25, 200, 80));
	//	__pCustomListItemFormat->AddElement(ID_LIST_BITMAP,
	//			Osp::Graphics::Rectangle(220, 10, 70, 80));
	//	__pCustomListItemFormat->SetElementEventEnabled(ID_LIST_TEXT, true);
	//	__pCustomListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP, true);

	AddControl(*__pList);


	// Adds an item to the CustomList
	//	    for(int i=0;i < __numLocales;i++)
	//	    {
	//	    	if(without != null && without->GetLanguageCode() == (__locales[i]).GetLanguageCode())
	//	    		continue;
	//
	//
	//	        //AddListItem(*__list, i, pBitmapNormal, pBitmapFocused);
	//	    }

	return result;
}

result LangSelect::AddListItem(CustomList& customList, int index, Bitmap* pBitmapNormal, Bitmap* pBitmapFocused)
{
	// Creates an item of the CustomList
	//    CustomListItem* pItem = new CustomListItem();
	//    String str = L"";
	//    __locales[index].GetLanguageName(str);
	//    pItem->Construct(100);
	//    pItem->SetItemFormat(*__pCustomListItemFormat);
	//    pItem->SetElement(ID_LIST_TEXT, str);
	//    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapFocused);
	//    pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
	//
	//    customList.AddItem(*pItem, index);

	return E_SUCCESS;
}

//void LangSelect::OnItemStateChanged(const Osp::Ui::Control & source, int index, int itemId,
//		int elementId, Osp::Ui::ItemStatus status)
//{
//
//}
//
//void LangSelect::OnItemStateChanged(const Osp::Ui::Control & source, int index, int itemId,
//		Osp::Ui::ItemStatus status)
//{
//	SetShowState(false);
//	if(__langSelectListener)
//		__langSelectListener->onSelectLang(__type, __locales[itemId]);
//}


void LangSelect::OnListViewItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status)
{
	SetShowState(false);
	if(__langSelectListener)
		__langSelectListener->onSelectLang(__type, *__aUsedLocales[index]);

	//    switch (elementId)
	//    {
	//    case ID_FORMAT_BITMAP:
	//        // Todo:
	//        break;
	//    case ID_FORMAT_STRING:
	//        // Todo:
	//        break;
	//    default:
	//        break;
	//    }
}

void LangSelect::OnListViewItemSwept(Osp::Ui::Controls::ListView &listView, int index, Osp::Ui::Controls::SweepDirection direction)
{
}

void LangSelect::OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus state)
{
	switch (elementId)
	{
	case ID_CONTEXT_ITEM_1:
		//To do
		break;
	case ID_CONTEXT_ITEM_2:
		//To do
		break;
	}
}

int LangSelect::GetItemCount(void)
{
	return __numUsedLocales;
}
Osp::Ui::Controls::ListItemBase*
LangSelect::CreateItem(int index, int itemWidth)
{
	ListAnnexStyle style = LIST_ANNEX_STYLE_RADIO ;
	CustomItem* pItem = new CustomItem();
	pItem->Construct(Osp::Graphics::Dimension(itemWidth, 100), style);

	// Create Bitmap
		Bitmap *pBitmapNormal = GetBitmapN(0);
		Bitmap *pBitmapFocused = GetBitmapN(1);

//	switch (index % 3)
//	{
//	case 0:
		String str = L"";
		(__aUsedLocales[index])->GetLanguageName(str);
		pItem->AddElement(Rectangle(80, 25, 200, 50), ID_FORMAT_STRING, str, true);
//		break;
//	case 1:
//		pItem->AddElement(Rectangle(80, 25, 200, 50), ID_FORMAT_STRING, L"Msg", true);
//		break;
//	case 2:
//		pItem->AddElement(Rectangle(80, 25, 200, 50), ID_FORMAT_STRING, L"Alarm", true);
//		break;
//	default:
//		break;
//	}
	pItem->AddElement(Rectangle(290, 20, 60, 60), ID_FORMAT_BITMAP, *pBitmapNormal);
//	pItem->AddElement(Rectangle(290, 20, 60, 60), ID_FORMAT_CUSTOM, *(static_cast<ICustomElement *> (__pListElement)));
//
//	ListContextItem* pItemContext = new ListContextItem();
//	pItemContext->Construct();
//	pItemContext->AddElement(ID_CONTEXT_ITEM_1, "Test1");
//	pItemContext->AddElement(ID_CONTEXT_ITEM_2, "Test2");
//	pItem->SetContextItem(pItemContext);

	return pItem;
}

bool LangSelect::DeleteItem(int index, Osp::Ui::Controls::ListItemBase* pItem, int itemWidth)
{
	delete pItem;
	pItem = null;
	return true;
}
