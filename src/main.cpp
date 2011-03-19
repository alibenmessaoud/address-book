#include <iostream>
#include "addressbookcontroller.h"
#include "dummydatasource.h"
#include "contact.h"
#include "errorinfo.h"

#include <QApplication>
#include "qtaddressbookgui.h"
#include "qtcontactlist.h"
#include "qtcontactdetailform.h"

#include "qtaddressbookgui.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    DummyDataSource dSrc;  
    AddressBookController myBook(dSrc);
    myBook.start();

    return app.exec();
}

