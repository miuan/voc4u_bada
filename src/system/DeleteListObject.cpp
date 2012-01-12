/*
 * DeleteListObject.cpp
 *
 *  Created on: 21.11.2011
 *      Author: m1uan
 */

#include "DeleteListObject.h"

DeleteListObject::DeleteListObject()
{
	deleteList.Construct(1000);
}

DeleteListObject::~DeleteListObject()
{
	deleteList.RemoveAll(true);
}

void DeleteListObject::AddToDeleteList(Osp::Base::Object * obj)
{
	if(obj != null)
		deleteList.Add(*obj);
}
