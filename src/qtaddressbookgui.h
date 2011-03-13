#ifndef UI_QTADDRESSBOOKGUI_H
#define UI_QTADDRESSBOOKGUI_H

#include "addressbookui.h"
#include "addressbookcontroller.h"
#include "qtmainwindow.h"


/***********************************************************************
    Class: QtAddressBookGUI

    Author: Phil Grohe

    A Qt front end GUI for the addressbook.

    Implements the AddressBookUI interface
***********************************************************************/

class QtAddressBookGUI :  public AddressBookUI
{

    public:
        QtAddressBookGUI(AddressBookController &controller);
        ~QtAddressBookGUI();

        //AddressBookUI interface
        virtual bool updateData(void);
        virtual bool show(void);

    private:
        QtMainWindow *appWindow;

};

#endif


