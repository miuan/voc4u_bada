/*
 * LangSelect.h
 *
 *  Created on: 23.10.2011
 *      Author: m1uan
 */

#ifndef LANGSELECT_H_
#define LANGSELECT_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FMedia.h>
#include <FLclLocale.h>
#include <FApp.h>

using namespace Osp::App;
using namespace Osp::Locales;
using namespace Osp::Base;
using namespace Osp::Graphics;
using namespace Osp::Ui::Controls;
using namespace Osp::Media;


class ILangSelectListener
{
public:
	virtual void onSelectLang(int type, Locale &selected) = 0;
};

class CustomListElement: public ICustomListElement
{



public:
	result DrawElement(const Osp::Graphics::Canvas& canvas,
			const Osp::Graphics::Rectangle& rect,
			CustomListItemStatus itemStatus)
	{
		result r = E_SUCCESS;

		Canvas* pCanvas = const_cast<Canvas*> (&canvas);

		pCanvas->SetLineWidth(5);
		pCanvas->SetForegroundColor(Color::COLOR_GREEN);
		if (pCanvas->DrawRectangle(rect) != E_SUCCESS)
			return r;

		pCanvas->SetForegroundColor(Color::COLOR_WHITE);
		if (pCanvas->DrawText(Point(rect.x + 20, rect.y + 20), L"Custom") != E_SUCCESS)
		return r;

		return r;
	}
};

class LangSelect: public Popup, public Osp::Ui::ICustomItemEventListener
{
	ILangSelectListener * __langSelectListener;
	CustomList *__list;
	CustomListItemFormat *__pCustomListItemFormat;
	CustomListElement *__pListElement;
	int __type;

	static Locale __locales[];
	static const int __numLocales;

public:
	static const int ID_LIST_ITEM = 101;
	static const int ID_LIST_TEXT = 102;
	static const int ID_LIST_BITMAP = 103;
	static const int ID_FORMAT_CUSTOM = 104;

public:
	LangSelect(int type, ILangSelectListener * lsl);
	bool Init(Locale *without);
	virtual ~LangSelect();

	virtual void OnItemStateChanged(const Osp::Ui::Control &source, int index,
			int itemId, int elementId, Osp::Ui::ItemStatus status);
	virtual void OnItemStateChanged(const Osp::Ui::Control &source, int index,
			int itemId, Osp::Ui::ItemStatus status);

	result AddListItem(CustomList& customList, int index,
			Bitmap* pBitmapNormal, Bitmap* pBitmapFocused);

	Bitmap * GetBitmapN(int i)
	{
		Bitmap *bitmap;
		Image* bitmapDecoder = new Image();
		result r = bitmapDecoder->Construct();
		if (IsFailed(r))
		{
			AppLog("Failed to construct decoder!");
		}

		// 4. decode the image with alphas (to allow transparency)
		bitmap = bitmapDecoder->DecodeN(L"/Home/Res/flags_preview_large.png", BITMAP_PIXEL_FORMAT_ARGB8888);

		return bitmap;
	};

};

#endif /* LANGSELECT_H_ */
