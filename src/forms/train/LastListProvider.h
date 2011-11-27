/*
 * LastListProvider.h
 *
 *  Created on: 27.11.2011
 *      Author: miuan
 */

#ifndef LASTLISTPROVIDER_H_
#define LASTLISTPROVIDER_H_

#include <FBase.h>
#include <FGraphics.h>
#include <FUi.h>
#include "ctrl/Word.h"

using namespace Osp::Base::Collection;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

class LastListProvider : public IListViewItemEventListener, public IListViewItemProvider
{
public:
	static const int MAX_IN_LAST_LIST = 15;
private:
	ArrayList array;
	EnrichedText *PrepareText(String text, bool know, bool bold);
    Word *GetWordAt(int index);


public:
	LastListProvider();
	virtual ~LastListProvider();

	ArrayList *GetArray(){return &array;};
	void AddWord(Word &word);


	virtual void  OnListViewContextItemStateChanged (ListView &listView, int index, int elementId, ListContextItemStatus status);
	virtual void  OnListViewItemLongPressed (ListView &listView, int index, int elementId, bool &invokeListViewItemCallback);
	virtual void  OnListViewItemStateChanged (ListView &listView, int index, int elementId, ListItemStatus status);
	virtual void  OnListViewItemSwept (ListView &listView, int index, SweepDirection direction);

	virtual ListItemBase * CreateItem (int index, int itemWidth);
	virtual bool DeleteItem (int index, ListItemBase *pItem, int itemWidth);
	virtual int GetItemCount (void);

};

#endif /* LASTLISTPROVIDER_H_ */
