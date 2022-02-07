
#ifndef TABLE_RW_C
#define TABLE_RW_C

#include <fstream>
#include "MyDB_PageReaderWriter.h"
#include "MyDB_TableReaderWriter.h"

using namespace std;

MyDB_TableReaderWriter :: MyDB_TableReaderWriter (MyDB_TablePtr forMe, MyDB_BufferManagerPtr myBuffer) {
    this->myDbTable = forMe;
    this->myDbBufferManager = myBuffer;

    //initialization of lastPage
    if(myDbTable->lastPage() == -1){
        myDbTable->setLastPage(0);
        lastPage = make_shared<MyDB_PageReaderWriter>(last());
        //?
//        lastPage->clear();
    }else{
        lastPage = make_shared<MyDB_PageReaderWriter>(last());
    }
}

MyDB_PageReaderWriter MyDB_TableReaderWriter :: operator [] (size_t i) {
    //if bigger than the last index, initialize the intermediate pages
    if(i > myDbTable->lastPage()){
        myDbTable->setLastPage (myDbTable->lastPage () + 1);
        lastPage = make_shared <MyDB_PageReaderWriter> (last());
        lastPage->clear ();
    }

	return MyDB_PageReaderWriter(myDbBufferManager->getPage(myDbTable, i));
}

MyDB_RecordPtr MyDB_TableReaderWriter :: getEmptyRecord () {
    MyDB_RecordPtr recordPtr = make_shared<MyDB_Record>(myDbTable->getSchema());
	return recordPtr;
}

MyDB_PageReaderWriter MyDB_TableReaderWriter :: last () {
    //get the last index of the page, and return;
    int last = myDbTable->lastPage();
    MyDB_PageReaderWriter lastP = MyDB_PageReaderWriter(myDbBufferManager->getPage(myDbTable, last));
	return lastP;
}

void MyDB_TableReaderWriter :: append (MyDB_RecordPtr appendMe) {
    // if we cannot append the new record in the current last page
    if(!lastPage->append(appendMe)){
        //create a new page
        myDbTable->setLastPage(myDbTable->lastPage() + 1);
        lastPage = make_shared<MyDB_PageReaderWriter>(myDbBufferManager->getPage(myDbTable, myDbTable->lastPage()));
        //need or not?
        lastPage->clear();
        append(appendMe);
    }
}

MyDB_RecordIteratorPtr MyDB_TableReaderWriter :: getIterator (MyDB_RecordPtr iterateIntoMe) {
	return make_shared<MyDB_TableRecIterator>(this, iterateIntoMe, myDbTable);
}

// load a text file into this table... overwrites the current contents
void MyDB_TableReaderWriter :: loadFromTextFile (string fromMe) {
    ifstream tableFile(fromMe,ios::in);

    if (tableFile.is_open()) {

        // clear the table
        myDbTable->setLastPage(0);
        lastPage = make_shared<MyDB_PageReaderWriter>(myDbBufferManager->getPage(myDbTable, 0));
        lastPage->clear();

        // create an empty record to read the table;
        MyDB_RecordPtr record = getEmptyRecord();

        string line;
        while (getline(tableFile, line)) {
            record->fromString(line);
            append(record);
        }

        tableFile.close();

    } else {
        cout << "error: can not open the text for reading!";
        exit(1);
    }
}

void MyDB_TableReaderWriter :: writeIntoTextFile (string toMe) {
    ofstream tableFile(toMe, ios::out);
    if (tableFile.is_open()) {
        // create an empty record
        MyDB_RecordPtr record = getEmptyRecord();

        // get the table iterator
        MyDB_RecordIteratorPtr recIter = getIterator(record);

        while (recIter->hasNext()) {
            recIter->getNext();
            tableFile << record << endl;
        }

        tableFile.close();
    } else {
        cout << "error: cannot open the text file for writing!";
        exit(1);
    }
}

#endif

