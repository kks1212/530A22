
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "MyDB_PageReaderWriter.h"

void MyDB_PageReaderWriter :: clear () {
    //set offset to the size of pageheader sizeof(PageHeader);
    this->getHeader()->offset = (size_t)(&(getHeader()->rec[0]) - (char *)getHeader());
    setType(MyDB_PageType::RegularPage);
    pageHandle->wroteBytes();
}

MyDB_PageType MyDB_PageReaderWriter :: getType () {
//	return MyDB_PageType :: RegularPage;
    return getHeader()->type;
}

MyDB_RecordIteratorPtr MyDB_PageReaderWriter :: getIterator (MyDB_RecordPtr iterateIntoMe) {
	return make_shared<MyDB_PageRecIterator>(this, iterateIntoMe);
}

void MyDB_PageReaderWriter :: setType (MyDB_PageType toMe) {
    getHeader()->type = toMe;
    pageHandle->wroteBytes();
}

bool MyDB_PageReaderWriter :: append (MyDB_RecordPtr appendMe) {
    //check whether we have enough space
    PageHeader *header = getHeader();
    if(header->offset + appendMe->getBinarySize() > pageSize){
        return false;
    }

    //todo: ? char * address calculation
    header->offset = (size_t)((char *)appendMe->toBinary( ((char *)header + header->offset)) - (char *)header);

    pageHandle->wroteBytes();
	return true;
}

PageHeader *MyDB_PageReaderWriter::getHeader() {
    return (PageHeader*) pageHandle->getBytes();
}

MyDB_PageReaderWriter::MyDB_PageReaderWriter(MyDB_PageHandle pageHandle, size_t pageSize) {
    this->pageSize = pageSize;
    this->pageHandle = pageHandle;
//    //initialization of pageHeader todo:??
    PageHeader* header = getHeader();
    header->type = MyDB_PageType :: RegularPage;
    header->offset = (size_t)(&(header->rec[0]) - (char *)header);
//            (size_t)(&(header->rec[0]) - (char *)header);
}

#endif
