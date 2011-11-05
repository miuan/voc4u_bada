/*
 * LangSetting.h
 *
 *  Created on: 23.10.2011
 *      Author: m1uan
 */

#ifndef LANGSETTING_H_
#define LANGSETTING_H_

#include <FBase.h>

using namespace Osp::Base;

class LangType
{
public:
	const String __code;
	const int __id;

	LangType(int id, String code) :
		__id(id), __code(code)
	{

	}

	const String getCode() const
	{
		return __code;
	}

	const int getId() const
	{
		return __id;
	}
};

class LangSetting
{
public:
	static const LangType CZECH;
	static const LangType ENGLISH;
	static const LangType GERMANY;
	static const LangType SPAIN;
	static const LangType PORTUGAL;
	static const LangType POLAND;
	static const LangType FRANCE;
	static const LangType ITALIAN;

public:
	LangSetting();
	virtual ~LangSetting();

	LangType * getLangTypeArrayN()
	{

	}
};

#endif /* LANGSETTING_H_ */
