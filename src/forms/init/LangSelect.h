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
#include "setting/LangSetting.h"
#include "system/DeleteListObject.h"

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

class CustomListElement: public ICustomElement
{

public:
	//	result DrawElement(const Osp::Graphics::Canvas& canvas,
	//			const Osp::Graphics::Rectangle& rect,
	//			CustomListItemStatus itemStatus)
	//	{
	//		result r = E_SUCCESS;
	//
	//		Canvas* pCanvas = const_cast<Canvas*> (&canvas);
	//
	//		pCanvas->SetLineWidth(5);
	//		pCanvas->SetForegroundColor(Color::COLOR_GREEN);
	//		if (pCanvas->DrawRectangle(rect) != E_SUCCESS)
	//			return r;
	//
	//		pCanvas->SetForegroundColor(Color::COLOR_WHITE);
	//		if (pCanvas->DrawText(Point(rect.x + 20, rect.y + 20), L"Custom") != E_SUCCESS)
	//		return r;
	//
	//		return r;
	//	}

	bool OnDraw(Osp::Graphics::Canvas& canvas, const Osp::Graphics::Rectangle& rect, Osp::Ui::Controls::ListItemDrawingStatus itemStatus)
	{
		// Sets the Font
		Osp::Graphics::Font font;
		font.Construct(Osp::Graphics::FONT_STYLE_PLAIN, 20);
		canvas.SetFont(font);
		canvas.SetLineWidth(5);
		canvas.SetForegroundColor(Osp::Graphics::Color::COLOR_GREEN);
		if (canvas.DrawRectangle(rect) != E_SUCCESS)
			return false;
		if (canvas.DrawText(Osp::Graphics::Point(rect.x + 2, rect.y + 20), L"Custom") != E_SUCCESS)
			return false;

		return true;
	}
};

class LangSelect: public Popup,
	public Osp::Ui::Controls::IListViewItemEventListener,
	public Osp::Ui::Controls::IListViewItemProvider,
	public DeleteListObject
{
	ILangSelectListener * __langSelectListener;
	ListView *__pList;
	//CustomListElement *__pCustomListItemFormat;
	CustomListElement *__pListElement;
	int __type;

	Locale **__aUsedLocales;
	int __numUsedLocales;

public:
	static const int ID_LIST_ITEM = 101;
	static const int ID_LIST_TEXT = 102;
	static const int ID_LIST_BITMAP = 103;
	static const int ID_FORMAT_CUSTOM = 104;

	static const int ID_FORMAT_STRING = 100;
	static const int ID_FORMAT_BITMAP = 101;
	// static const int ID_FORMAT_CUSTOM = 102;
	static const int ID_CONTEXT_ITEM_1 = 103;
	static const int ID_CONTEXT_ITEM_2 = 104;

public:
	LangSelect(int type, ILangSelectListener * lsl);
	bool Init(Locale *without);
	virtual ~LangSelect();

	// IListViewItemEventListener
	virtual void OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus state);
	virtual void OnListViewItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Osp::Ui::Controls::ListView &listView, int index, Osp::Ui::Controls::SweepDirection direction);

	//IListViewItemProvider
	virtual Osp::Ui::Controls::ListItemBase* CreateItem(int index, int itemWidth);
	virtual bool DeleteItem(int index, Osp::Ui::Controls::ListItemBase* pItem, int itemWidth);
	virtual int GetItemCount(void);

	result AddListItem(CustomList& customList, int index, Bitmap* pBitmapNormal, Bitmap* pBitmapFocused);

//	Bitmap * GetBitmapN(int i)
//	{
//		Bitmap *bitmap;
//		Image* bitmapDecoder = new Image();
//		result r = bitmapDecoder->Construct();
//		if (IsFailed(r))
//		{
//			AppLog("Failed to construct decoder!");
//		}
//
//		// 4. decode the image with alphas (to allow transparency)
//		bitmap = bitmapDecoder->DecodeN(L"/Home/Res/flags_preview_large.png", BITMAP_PIXEL_FORMAT_ARGB8888);
//
//		return bitmap;
//	}
//	;

};

#endif /* LANGSELECT_H_ */
