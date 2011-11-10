/*
 * Dictionary.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "Dictionary.h"

Dictionary::Dictionary()
{
	// TODO Auto-generated constructor stub

}

Dictionary::~Dictionary()
{
	// TODO Auto-generated destructor stub
}

result Dictionary::OnInitializing(void)
{
	__pList = static_cast<ListView *>(GetControl(L"IDC_LESSON"));
	__pList->SetItemProvider(*this);
	return E_SUCCESS;
}

// ListViewItemEvents
void OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus status)
{
}

void OnListViewItemLongPressed(Osp::Ui::Controls::ListView &listView, int index, int elementId, bool &invokeListViewItemCallback)
{
}

void OnListViewItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status)
{
}

void OnListViewItemSwept(Osp::Ui::Controls::ListView &listView, int index, Osp::Ui::Controls::SweepDirection direction)
{
}

// list item provider
Osp::Ui::Controls::ListItemBase * Dictionary::CreateItem(int index, int itemWidth)
{
	ListAnnexStyle style = LIST_ANNEX_STYLE_NORMAL;
	    CustomItem* pItem = new CustomItem();
	    pItem->Construct(Osp::Graphics::Dimension(itemWidth,100), style);

	    switch (index % 3)
	    {
	    case 0:
	        pItem->AddElement(Rectangle(80, 25, 200, 50), ID_FORMAT_STRING, L"HOME", true);
	        break;
	    case 1:
	        pItem->AddElement(Rectangle(80, 25, 200, 50), ID_FORMAT_STRING, L"Msg", true);
	        break;
	    case 2:
	        pItem->AddElement(Rectangle(80, 25, 200, 50), ID_FORMAT_STRING, L"Alarm", true);
	        break;
	    default:
	        break;
	    }


	    return pItem;
}

bool Dictionary::DeleteItem(int index, Osp::Ui::Controls::ListItemBase *pItem, int itemWidth)
{
	return false;
}

int Dictionary::GetItemCount(void)
{
	return 10;
}
