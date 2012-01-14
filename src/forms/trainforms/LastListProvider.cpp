/*
 * LastListProvider.cpp
 *
 *  Created on: 27.11.2011
 *      Author: miuan
 */

#include "LastListProvider.h"

LastListProvider::LastListProvider(TextToSpeechHelper *pTTSH, int maxInList) :
	__pTTSH(pTTSH), __maxInList(maxInList)
{
	array.Construct();
}

LastListProvider::~LastListProvider()
{
	array.RemoveAll(true);
}

void LastListProvider::AddWord(Word &word)
{
	array.Add(word);

	if (array.GetCount() > __maxInList)
	{
		array.RemoveAt(0, true);
	}
}

void LastListProvider::OnListViewContextItemStateChanged(ListView &listView, int index, int elementId, ListContextItemStatus status)
{

}

void LastListProvider::OnListViewItemLongPressed(ListView &listView, int index, int elementId, bool &invokeListViewItemCallback)
{
}

void LastListProvider::OnListViewItemStateChanged(ListView &listView, int index, int elementId, ListItemStatus status)
{
	if (__pTTSH)
	{
		Word *word = GetWordAt(index);
		AppLog("text to speech: %S", word->__lern.GetPointer());

		if (word)
		{
			__pTTSH->Play(word->__lern);
			//		result r = __pTextToSpeech->Speak(word->__lern);
			//		if(IsFailed(r))
			//		{
			//			AppLog("text speach failed: %s", GetErrorMessage(r));
			//		}
		}
	}
}

void LastListProvider::OnListViewItemSwept(ListView &listView, int index, SweepDirection direction)
{

}

EnrichedText *LastListProvider::PrepareText(String text, bool know, bool bold)
{
	//pItem->SetBackgroundColor(LIST_ITEM_DRAWING_STATUS_NORMAL, LangSetting::LESSON_COLORS[lesson - 1]);
	result r;
	EnrichedText *pEnrichedText = new EnrichedText();
	r = pEnrichedText->Construct(Dimension(200, 200));

	TextElement *pTextElement = new TextElement();
	r = pTextElement->Construct(text);
	if (!pTextElement)
		return null;

	Font font;
	if (bold)
		font.Construct(FONT_STYLE_BOLD, 30);
	else font.Construct(FONT_STYLE_PLAIN, 30);
	pTextElement->SetFont(font);
	pTextElement->SetTextColor(know ? Color::COLOR_BLUE : Color::COLOR_RED);

	pEnrichedText->Add(*pTextElement);
	pEnrichedText->SetTextWrapStyle(TEXT_WRAP_WORD_WRAP);

	return pEnrichedText;
}

Word *LastListProvider::GetWordAt(int index)
{
	int count = array.GetCount();
	int pos = count - (index % count) - 1;

	if (count < 1)
		return null;

	return static_cast<Word*> (array.GetAt(pos));
}

ListItemBase * LastListProvider::CreateItem(int index, int itemWidth)
{
	ListAnnexStyle style = LIST_ANNEX_STYLE_NORMAL;
	CustomItem *pItem = new CustomItem();
	pItem->Construct(Osp::Graphics::Dimension(itemWidth, 70), style);

	Word *word = GetWordAt(index);
//	word->__lern = "MMMMMMMMMMMMMMMMM";
//	word->__native= "MMMMMMMMMMMMMMMMM";
	EnrichedText *pELern = PrepareText(word->__lern, word->__type || word->__know, true);
	EnrichedText *pENative = PrepareText(word->__native, !word->__type || word->__know, false);

	int columnWidth = itemWidth;
	//AddToDestructList(pTextElement);
	//AddToDestructList(pEnrichedText);

	Color blue(133, 133, 255);

	Color cl = word->__type || word->__know ? blue : Color::COLOR_RED;
	Color cn = !word->__type || word->__know ? blue : Color::COLOR_RED;


	int width1 = columnWidth / 2;
	int top1 = 13;
	int top2 = 13;
	int left2 = width1;
	int width2 = width1;
	int fontSize = 30;


	if(word->__lern.GetLength() > 15 || word->__native.GetLength() > 15)
	{
		fontSize = 24;
		top1 = 0;
		top2 = 22;
		left2 = 3;
		width1 = columnWidth- 3;
		width2 = width1;
	}



	if (pELern)
	{
		pItem->AddElement(Rectangle(3, top1, width1, 50), 1, word->__lern, fontSize, cl, cl, cl);
	}
	if (pENative)
	{
		pItem->AddElement(Rectangle(left2, top2, width2, 50), 2, word->__native, fontSize, cn, cn, cn);
	}

	pItem->SetElementTextHorizontalAlignment(1, ALIGNMENT_LEFT);
	pItem->SetElementTextHorizontalAlignment(2, ALIGNMENT_RIGHT);

	return pItem;
}

bool LastListProvider::DeleteItem(int index, ListItemBase *pItem, int itemWidth)
{
	return false;
}

int LastListProvider::GetItemCount(void)
{
	return array.GetCount();
}

