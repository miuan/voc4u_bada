/*
 * Dictionary.h
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include "../BaseWordForm.h"

class Dictionary: public BaseWordForm
{
public:
	Dictionary();
	virtual ~Dictionary();

	String  GetResourceID(){return L"IDF_DICTIONARY";}
};

#endif /* DICTIONARY_H_ */
