//
// Created by Shawn Zeng on 2022/2/6.
//

#include "MyDB_TableRecIterator.h"
#include "MyDB_TableReaderWriter.h"
#include "MyDB_PageReaderWriter.h"

MyDB_TableRecIterator::MyDB_TableRecIterator(MyDB_TableReaderWriter *tableRW, MyDB_RecordPtr iterRecordPtr, MyDB_TablePtr tablePtr) {
    tableRWParent = tableRW;
    recordPtr = iterRecordPtr;
    myDbTable = tablePtr;
    pageIndex = 0;
    MyDB_PageReaderWriter temp = tableRWParent->operator[](0);
    pageRecIterator = temp.getIterator(recordPtr);
}

void MyDB_TableRecIterator::getNext() {
    pageRecIterator->getNext();
}

bool MyDB_TableRecIterator::hasNext() {
    if(!pageRecIterator->hasNext()){
        pageIndex++;
        if(pageIndex > myDbTable->lastPage()){
            return false;
        }
        pageRecIterator = tableRWParent[pageIndex].getIterator(recordPtr);
        return pageRecIterator->hasNext();
    }
    return true;
}
