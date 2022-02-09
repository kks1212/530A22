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
    pageRecIterator = tableRWParent->operator[](0).getIterator(recordPtr);
}

void MyDB_TableRecIterator::getNext() {
    pageRecIterator->getNext();
}

bool MyDB_TableRecIterator::hasNext() {
    if(!(pageRecIterator->hasNext())){
        while (pageIndex < myDbTable->lastPage()){
            pageIndex++;
            pageRecIterator = tableRWParent[pageIndex].getIterator(recordPtr);
            if(pageRecIterator->hasNext()) return true;
        }
        return false;
    }
    return true;
}
