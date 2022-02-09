
#ifndef PAGE_RW_H
#define PAGE_RW_H

#include "MyDB_PageType.h"
//#include "MyDB_TableReaderWriter.h"
#include "MyDB_BufferManager.h"
#include "MyDB_PageRecIterator.h"
#include "MyDB_Record.h"
#include "MyDB_TableReaderWriter.h"
//#include "MyDB_PageHandle.h"

struct PageHeader {
    MyDB_PageType type;
    size_t offset;//offset to the last record
    char rec[0];//begin of the first record
};

//class MyDB_PageReaderWriter;
//typedef shared_ptr <MyDB_PageReaderWriter> MyDB_PageReaderWriterPtr;

class MyDB_PageReaderWriter {

public:

	// ANY OTHER METHODS YOU WANT HERE

	// empties out the contents of this page, so that it has no records in it
	// the type of the page is set to MyDB_PageType :: RegularPage
	void clear ();	

	// return an itrator over this page... each time returnVal->next () is
	// called, the resulting record will be placed into the record pointed to
	// by iterateIntoMe
	MyDB_RecordIteratorPtr getIterator (MyDB_RecordPtr iterateIntoMe);

	// appends a record to this page... return false is the append fails because
	// there is not enough space on the page; otherwise, return true
	bool append (MyDB_RecordPtr appendMe);

	// gets the type of this page... this is just a value from an ennumeration
	// that is stored within the page
	MyDB_PageType getType ();

	// sets the type of the page
	void setType (MyDB_PageType toMe);

    PageHeader* getHeader();

    //the current page
    MyDB_PageHandle pageHandle;

    //constructor
    MyDB_PageReaderWriter(MyDB_PageHandle pageHandle, size_t pageSize);
    MyDB_PageReaderWriter(MyDB_TableReaderWriter &tableRW, int id);
private:

	// ANYTHING ELSE YOU WANT HERE


    // size of the page
    size_t pageSize;
};

#endif
