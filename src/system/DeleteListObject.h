/*
 * DeleteListObject.h
 *
 *  Created on: 21.11.2011
 *      Author: m1uan
 */

#ifndef DELETELISTOBJECT_H_
#define DELETELISTOBJECT_H_

#include <FBase.h>

using namespace Osp::Base::Collection;

class DeleteListObject
{
	ArrayList deleteList;

public:
	DeleteListObject();
	virtual ~DeleteListObject();
	void AddToDeleteList(Osp::Base::Object * obj);
};

#endif /* DELETELISTOBJECT_H_ */
