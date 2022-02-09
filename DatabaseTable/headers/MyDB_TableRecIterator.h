//
// Created by Shawn Zeng on 2022/2/6.
//

#ifndef A2_MYDB_TABLERECITERATOR_H
#define A2_MYDB_TABLERECITERATOR_H

#include <memory>
#include "MyDB_RecordIterator.h"
#include "MyDB_Record.h"
#include "MyDB_Table.h"

class MyDB_TableReaderWriter;
class MyDB_TableRecIterator;
typedef shared_ptr <MyDB_TableRecIterator> MyDB_TableRecIteratorPtr;

class MyDB_TableRecIterator : public MyDB_RecordIterator {
public:
    void getNext () override;

    bool hasNext () override;

    MyDB_TableRecIterator(MyDB_TableReaderWriter &tableRW, MyDB_RecordPtr iterRecordPtr, MyDB_TablePtr tablePtr);
//    ~MyDB_TableRecIterator();

private:
    //current page index
    size_t pageIndex;

    //current page iterator
    MyDB_RecordIteratorPtr pageRecIterator;

    //use this single record to iterate
    MyDB_RecordPtr recordPtr;

    //pointer to the parent pageReaderWriter
    MyDB_TableReaderWriter& tableRWParent;

    MyDB_TablePtr myDbTable;
};

#endif //A2_MYDB_TABLERECITERATOR_H
