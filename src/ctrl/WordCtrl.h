/*
 * WordCtrl.h
 *
 *  Created on: 6.11.2011
 *      Author: m1uan
 */

#ifndef WORDCTRL_H_
#define WORDCTRL_H_

#include "Word.h"
#include <FIo.h>

using namespace Osp::Io;

#define DB_NAME L"/Home/testingDatabase"

#define TABLE_NAME L"t_words"
#define COLUMN_LWEIGHT L"lweight"
#define COLUMN_NWEIGHT L"nweight"
#define COLUMN_NATIVE L"native"
#define COLUMN_LERN L"lern"
#define COLUMN_USER_CHANGE L"user"
#define COLUMN_LESSON L"lesson"
#define COLUMN_ID L"id"

#define INSERT_TABLE L"CREATE TABLE IF NOT EXISTS %ls\
		(%ls INTEGER PRIMARY KEY AUTOINCREMENT,\
		%ls INTEGER,\
		%ls VCHAR(100),\
		%ls VCHAR(100),\
		%ls INTEGER,\
		%ls INTEGER,\
		%ls INTEGER)"


#define LESSON_EXISTS L"SELECT COUNT(*) FROM %S WHERE %S = %d"

class WordCtrl
{
private:
	static WordCtrl *__wc;
	Database *__db;


private:
    result PrepareDB();


public:
	WordCtrl();
	virtual ~WordCtrl();

	result Init();
	static WordCtrl * GetInstance();
	bool AddWord(Word &word);
    bool GetLessonEnabled(const int lesson);
};

#endif /* WORDCTRL_H_ */
