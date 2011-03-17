#ifndef UI_QTADDRESSBOOKGUI_H
#define UI_QTADDRESSBOOKGUI_H

#include "addressbookview.h"
#include "addressbookcontroller.h"
#include "qtmainwindow.h"


/***********************************************************************
    Class: QtAddressBookGUI

    Author: Phil Grohe

    A Qt front end GUI for the addressbook.

    Implements the AddressBookView interface
***********************************************************************/

class QtAddressBookGUI :  public AddressBookView
{

    public:
        QtAddressBookGUI(AddressBookController &controller);
        ~QtAddressBookGUI();

        //AddressBookView interface
        virtual bool updateData(void);
        virtual bool show(void);

    private:
        QtMainWindow *appWindow;

};

#endif


