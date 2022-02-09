//
// Created by Shawn Zeng on 2022/2/4.
//

#include "MyDB_PageRecIterator.h"
#include "MyDB_PageReaderWriter.h"

void MyDB_PageRecIterator::getNext() {
    if(hasNext()){
        //move to the next position and update the current offset
        void* nextP = recordPtr->fromBinary(((char*)pageRWParent.getHeader() + curOffSet));
        curOffSet = (char *)nextP - (char*)pageRWParent.getHeader();
    }
}

bool MyDB_PageRecIterator::hasNext() {
    //check if current offset is smaller than the page record's length
//    cout<<"a"<<endl;

    if(curOffSet < pageRWParent.getHeader()->offset){
        return true;
    }else{
        return false;
    }

}

MyDB_PageRecIterator::MyDB_PageRecIterator(MyDB_PageReaderWriter &pageRW, MyDB_RecordPtr recordPtr) : pageRWParent(pageRW) {
//    this->pageRWParent = pageRW;
    this->recordPtr = recordPtr;

    //get the address of rec[0], which is exactly behind the pageHeader
    this->curOffSet = (size_t)(&(pageRW.getHeader()->rec[0]) - (char *)pageRW.getHeader());
//    this->curOffSet = sizeof(PageHeader);
}
