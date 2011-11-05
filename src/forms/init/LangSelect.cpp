/*
 * LangSelect.cpp
 *
 *  Created on: 23.10.2011
 *      Author: m1uan
 */

#include "LangSelect.h"

Locale LangSelect::__locales[] = {
			Locale(LANGUAGE_CES, COUNTRY_CZ),
			Locale(LANGUAGE_ENG, COUNTRY_US),
			Locale(LANGUAGE_DEU, COUNTRY_DE),
			Locale(LANGUAGE_FRA, COUNTRY_FR)
	};

const int LangSelect::__numLocales = 4;

LangSelect::LangSelect(int type, ILangSelectListener * lsl)
{
	__type = type;
	__langSelectListener = lsl;
}

LangSelect::~LangSelect()
{
	// TODO Auto-generated destructor stub
}

bool LangSelect::Init(Locale * without)
{

	bool result = Construct(true, Dimension(340,650));

	 // Create Bitmap
	    Bitmap *pBitmapNormal  = GetBitmapN(0);
	    Bitmap *pBitmapFocused = GetBitmapN(1);

	    AppResource *res = Application::GetInstance()->GetAppResource();
	    String title;
	    if(res->GetString(L"IDS_LANGUAGE_SELECT", title) == E_SUCCESS)
	    	SetTitleText(title);
	// Creates CustomListElement
	__pListElement = new CustomListElement();

	__list = new CustomList();
	__list->Construct(Rectangle(5, 5, 330, 640), CUSTOM_LIST_STYLE_NORMAL);
	__list->AddCustomItemEventListener(*this);

	// Create a item format of the CustomList
	__pCustomListItemFormat = new CustomListItemFormat();
	__pCustomListItemFormat->Construct();
	__pCustomListItemFormat->AddElement(ID_LIST_TEXT,
			Osp::Graphics::Rectangle(10, 25, 200, 80));
	__pCustomListItemFormat->AddElement(ID_LIST_BITMAP,
			Osp::Graphics::Rectangle(220, 10, 70, 80));
	__pCustomListItemFormat->SetElementEventEnabled(ID_LIST_TEXT, true);
	__pCustomListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP, true);

	AddControl(*__list);


	 // Adds an item to the CustomList
	    for(int i=0;i < __numLocales;i++)
	    {
	    	if(without != null && without->GetLanguageCode() == (__locales[i]).GetLanguageCode())
	    		continue;

	        AddListItem(*__list, i, pBitmapNormal, pBitmapFocused);
	    }

	return result;
}

result
LangSelect::AddListItem(CustomList& customList, int index, Bitmap* pBitmapNormal, Bitmap* pBitmapFocused)
{
    // Creates an item of the CustomList
    CustomListItem* pItem = new CustomListItem();
    String str = L"";
    __locales[index].GetLanguageName(str);
    pItem->Construct(100);
    pItem->SetItemFormat(*__pCustomListItemFormat);
    pItem->SetElement(ID_LIST_TEXT, str);
    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapFocused);
    pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));

    customList.AddItem(*pItem, index);

    return E_SUCCESS;
}

void LangSelect::OnItemStateChanged(const Osp::Ui::Control & source, int index, int itemId,
		int elementId, Osp::Ui::ItemStatus status)
{

}

void LangSelect::OnItemStateChanged(const Osp::Ui::Control & source, int index, int itemId,
		Osp::Ui::ItemStatus status)
{
	SetShowState(false);
	if(__langSelectListener)
		__langSelectListener->onSelectLang(__type, __locales[itemId]);
}

