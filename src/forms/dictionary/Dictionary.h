/*
 * Dictionary.h
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include "../BaseWordForm.h"
#include <FGraphics.h>
#include "setting/LangSetting.h"
#include "dialogs/information/Information.h"

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::Base;

class Dictionary: public BaseWordForm, public Osp::Ui::Controls::IListViewItemEventListener, public Osp::Ui::Controls::IListViewItemProvider
, public ILessonWorkerLissener
{
	ListView * __pList;

	Information *__info;


	bool initState[LangSetting::NUM_LESSON];
	bool saveState[LangSetting::NUM_LESSON];
	CustomItem *CreateLessonItem(int itemWidth, int lesson);
	void InitLessonState();
    void SetupInitSetting();
    void ShowInfoDlg();

public:
    static const int ID_FORMAT_STRING = 1;
public:
    Dictionary();
    virtual ~Dictionary();
    String GetResourceID()
    {
        return L"IDF_DICTIONARY";
    }

    virtual result OnInitializing(void);
    virtual result OnTerminating(void);
    virtual void OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView & listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus status);
    virtual void OnListViewItemLongPressed(Osp::Ui::Controls::ListView & listView, int index, int elementId, bool & invokeListViewItemCallback);
    virtual void OnListViewItemStateChanged(Osp::Ui::Controls::ListView & listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status);
    virtual void OnListViewItemSwept(Osp::Ui::Controls::ListView & listView, int index, Osp::Ui::Controls::SweepDirection direction);
    virtual Osp::Ui::Controls::ListItemBase *CreateItem(int index, int itemWidth);
    virtual bool DeleteItem(int index, Osp::Ui::Controls::ListItemBase *pItem, int itemWidth);
    virtual int GetItemCount(void);
    void OnActionPerformed(const Osp::Ui::Control & source, int actionId);
public:
    virtual void OnLessonTask(const int lesson);

	bool Init();
};

#endif /* DICTIONARY_H_ */
