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
	static Osp::Graphics::Bitmap * GetBitmapN(Osp::Base::String ID);

	static void ShowFront(Osp::Ui::Controls::Form *form, Osp::Ui::Controls::Form *parent = null);
	static void SplitString(Osp::Base::String &str, Osp::Base::String separator, Osp::Base::Collection::ArrayList & array);

	static void RemovePunctuationFromEnd(Osp::Base::String &str);
};

#endif /* UTILS_H_ */
