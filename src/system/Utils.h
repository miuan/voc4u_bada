/*
 * Utils.h
 *
 *  Created on: 10.11.2011
 *      Author: m1uan
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <FBase.h>
#include <FGraphics.h>
#include <FUi.h>

class Utils
{
public:
	Utils();
	virtual ~Utils();

	static Osp::Base::String GetString(Osp::Base::String ID);
	static Osp::Graphics::Bitmap * GetBitmap(Osp::Base::String ID);

	static void ShowFront(Osp::Ui::Controls::Form *parent, Osp::Ui::Controls::Form *form);
};

#endif /* UTILS_H_ */
