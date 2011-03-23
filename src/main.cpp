/*
#include <iostream>
#include "addressbookcontroller.h"
#include "dummydatasource.h"
#include "contact.h"
#include "errorinfo.h"

#include <QApplication>
#include "qtaddressbookgui.h"
#include "qtcontactlist.h"
#include "qtcontactdetailview.h"

#include "qtaddressbookgui.h"
*/
#include "qtaddcontactdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    
    QtAddContactDialog myDialog;

    myDialog.show();
//    DummyDataSource dSrc;  
//   AddressBookController myBook(dSrc);
//    myBook.start();

    return app.exec();
}

