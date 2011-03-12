#ifndef UI_QTADDRESSBOOKGUI_H
#define UI_QTADDRESSBOOKGUI_H

#include <QMainWindow>

#include "addressbookui.h"
#include "addressbookcontroller.h"
#include "qtcontactlist.h"


/***********************************************************************
    Class: QtAddressBookGUI

    Author: Phil Grohe

    A Qt front end GUI for the addressbook.

    Implements the AddressBookUI interface
***********************************************************************/

class QtAdressBookGUI :  public AddressBookUI
{
    Q_OBJECT

    public:
        QtAddressBookGUI(AddressBookController &controller);
        ~QtAddressBookGUI() {};

        //AddressBookUI interface
        virtual bool updateData(void);
        virtual bool show(void);

    private:

    signal:
        void updateWidgets(AddressBookController &controller);

};

#endif


