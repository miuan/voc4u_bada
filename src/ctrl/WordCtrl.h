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

#define UPDATE_TABLE L"UPDATE %S SET \
		%S = ?,\
		%S = ?,\
		%S = ?,\
		%S = ?,\
		%S = ? WHERE %S = ?"

#define WORD_COUNT L"SELECT COUNT(*) FROM %S"
#define LESSON_EXISTS L"SELECT COUNT(*) FROM %S"
#define SELECT_WORD L"SELECT %S, %S, %S, %S, %S, %S, %S FROM %S ORDER BY %S ASC, %S ASC %S"

enum WORD_TYPE
{
	WORD_TYPE_ALL,
	WORD_TYPE_ENABLED,
	WORD_TYPE_ENABLED_DONTKNOW,
	WORD_TYPE_DISABLED
};


class WordCtrl: public ILessonWorkerLissener
{
public:
	static const int CUSTOM_WORD_LESSON_ID = 0;

private:
	static WordCtrl *__wc;
	Database *__db;

	LessonWorker *__lw;
	ILessonWorkerLissener * __lwLissener;

	 friend Object *LessonWorker::Run(void);
private:

	String PrepareWordWhere(const WORD_TYPE type = WORD_TYPE_ALL, const int lesson = -1);
	Word * CreateWordFromDbEnumeratorN(DbEnumerator & pEnum);


    String SQLSelectWord(String where, String limit);
    String SQLUpdateWord();
    result PrepareDB();
    void CreateLessonWorker();
public:
    WordCtrl();
    virtual ~WordCtrl();
    result Init();
    static WordCtrl *GetInstance();

    bool EnableNextWords();
    bool AddWord(Word & word);
    bool GetLessonLoaded(const int lesson);
    int GetWordCount(const WORD_TYPE type = WORD_TYPE_ALL, const int lesson = -1);
    bool LoadLesson(const int lesson, bool unload);
    void SetLessonWorkerListener(ILessonWorkerLissener *ilwl);
    virtual void OnLessonTask(const int lesson);
    int *GetWorkerTaskLessonInProgressN(int & count);

    /**
     * lesson : id ( -1 is all lesson)
     * limit : maximum word loaded ( -1 is infinity )
     * type : type of word see to enum WORD_TYPE for more
     * withoutWords : list with words and theirs id will be escaped
     */
    ArrayList *GetWordsN(const int lesson = -1, const int limit = -1, const WORD_TYPE type = WORD_TYPE_ALL, Osp::Base::Collection::ArrayList *withoutWords = null);
    Word *GetFirstWordN(Osp::Base::Collection::ArrayList *lastList);
    bool UpdateWord(Word & word);
private:
    bool DeleteLesson(const int lesson);
};

#endif /* WORDCTRL_H_ */
