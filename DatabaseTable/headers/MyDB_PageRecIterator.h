//
// Created by Shawn Zeng on 2022/2/4.
//

#ifndef A2_MYDB_PAGERECITERATOR_H
#define A2_MYDB_PAGERECITERATOR_H


//#include <memory>
#include "MyDB_RecordIterator.h"
#include "MyDB_Record.h"

using namespace std;

class MyDB_PageReaderWriter;
class MyDB_PageRecIterator;
typedef shared_ptr <MyDB_PageRecIterator> MyDB_PageRecIteratorPtr;

class MyDB_PageRecIterator : public MyDB_RecordIterator{
public:
    // put the contents of the next record in the file/page into the iterator record
    // this should be called BEFORE the iterator record is first examined
    void getNext () override;

    // return true iff there is another record in the file/page
    bool hasNext () override;

    // destructor and contructor
    MyDB_PageRecIterator (MyDB_PageReaderWriter *pageRW, MyDB_RecordPtr iterRecordPtr);

//    ~MyDB_PageRecIterator ();

private:
    //current iterate offset
    size_t curOffSet;

    //use this single record to iterate
    MyDB_RecordPtr recordPtr;

    //pointer to the parent pageReaderWriter
    MyDB_PageReaderWriter* pageRWParent;
};


#endif //A2_MYDB_PAGERECITERATOR_H
