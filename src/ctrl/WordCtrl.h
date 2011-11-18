/*
 * WordCtrl.h
 *
 *  Created on: 6.11.2011
 *      Author: m1uan
 */

#ifndef WORDCTRL_H_
#define WORDCTRL_H_

#include "Word.h"
#include "LessonWorker.h"
#include <FIo.h>
#include <FBase.h>

using namespace Osp::Io;
using namespace Osp::Base;
using namespace Osp::Base::Runtime;
using namespace Osp::Base::Collection;

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
#define SELECT_WORD L"SELECT %S, %S, %S, %S, %S, %S, %S FROM %S ORDER BY %S DESC, %S DESC %S"
class WordCtrl: public ILessonWorkerLissener
{
public:
	static const int CUSTOM_WORD_LESSON_ID = 0;

private:
	static WordCtrl *__wc;
	Database *__db;

	LessonWorker *__lw;
	ILessonWorkerLissener * __lwLissener;

	friend Object * LessonWorker::Run(void);

private:

	String SQLSelectWord(String where, String limit);
	result PrepareDB();
	void CreateLessonWorker();
public:
	WordCtrl();
	virtual ~WordCtrl();
	result Init();
	static WordCtrl *GetInstance();
	bool AddWord(Word & word);
	bool GetLessonEnabled(const int lesson);

	bool AddLesson(const int lesson, bool remove);

	void SetLessonWorkerListener(ILessonWorkerLissener *ilwl);
	virtual void OnLessonTask(const int lesson);
	int * GetWorkerTaskLessonInProgressN(int &count);

	ArrayList * GetWordsByLessonN(const int lesson);
private:

	/*
	 * no call directly, use AddLesson with remove parameter
	 * because this is called from LessonWorker
	 *
	 * 0 = delete all words in db
	 */
	bool DeleteLesson(const int lesson);
};

#endif /* WORDCTRL_H_ */
