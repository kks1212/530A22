
#ifndef PAGE_RW_C
#define PAGE_RW_C

#include "MyDB_PageReaderWriter.h"

void MyDB_PageReaderWriter :: clear () {
    //set offset to the size of pageheader
    this->getHeader()->offset = sizeof(PageHeader);
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
    header->offset = (size_t)((char *)appendMe->toBinary((void *) ((char *)header + header->offset)) - (char *)header);

    pageHandle->wroteBytes();
	return true;
}

PageHeader *MyDB_PageReaderWriter::getHeader() {
    PageHeader* myHead = (PageHeader*) pageHandle ->getBytes();
    return myHead;
}

MyDB_PageReaderWriter::MyDB_PageReaderWriter(MyDB_PageHandle pageHandle): pageHandle(pageHandle) {
    pageSize = pageHandle->getParent().getPageSize();

    //initialization of pageHeader
    PageHeader* header = getHeader();
    header->type = MyDB_PageType :: RegularPage;
    header->offset = (size_t)(header->rec - (char *)header);
}

#endif
