/*
 * LangSetting.h
 *
 *  Created on: 23.10.2011
 *      Author: m1uan
 */

#ifndef LANGSETTING_H_
#define LANGSETTING_H_

#include <FBase.h>
#include <FLclLocale.h>
#include <FApp.h>
#include <FGraphics.h>

#include "lang/InitData.h"
#include "system/Utils.h"

using namespace Osp::App;
using namespace Osp::Locales;
using namespace Osp::Base;
using namespace Osp::Graphics;

class LangSetting
{
public:
	/**
	 * all allowed languages
	 */
	static const Locale CZECH;
	static const Locale ENGLISH;
	static const Locale GERMANY;
	static const Locale SPAIN;
	static const Locale PORTUGAL;
	static const Locale POLAND;
	static const Locale FRANCE;
	static const Locale ITALIAN;

	/**
	 * all languages in array
	 */
	static Locale LOCALES[];
	static const int NUM_LOCALES;

	/**
	 * num lesson for initing DB
	 */
	static const int NUM_LESSON = 4;

	/**
	 * colors for lesson
	 */
	static const Color LESSON_COLORS[];
	static const Color CUSTOM_WORD;
public:
	LangSetting();
	virtual ~LangSetting();

	static String GetNameOfLesson(int lesson);
	static Osp::Graphics::Bitmap * GetIcon(Locale & lc);
	static wchar_t ** GetInitDataN(String lang, int lesson, int &count);
	static Locale & GetLocaleFromCode(String langCode);
};

#endif /* LANGSETTING_H_ */
