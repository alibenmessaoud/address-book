#include <iostream>
#include "addressbookcontroller.h"
#include "dummydatasource.h"
#include <QApplication>

#include "sqlitedatasource.h"

int main(int argc, char *argv[])
{
/*
    QApplication app(argc, argv);

    DummyDataSource dSrc;  
    AddressBookController myBook(dSrc);
    myBook.start();
    return app.exec();
*/
    SQLiteDataSource myDB("foo.db");
    
}

