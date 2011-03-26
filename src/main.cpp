#include <iostream>
#include "addressbookcontroller.h"
#include "dummydatasource.h"
//#include "contact.h"
#include <QApplication>
//#include "qtaddcontactdialog.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    DummyDataSource dSrc;  
    AddressBookController myBook(dSrc);
    myBook.start();
    return app.exec();
    
}

