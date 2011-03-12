#ifndef UI_ADDRESSBOOKUI_H
#define UI_ADDRESSBOOKUI_H

#include "addressbookcontroller.h"

/***********************************************************************
    Class: AddressBookUI

    Author: Phil Grohe

    Interface for the application's UI to implement.
***********************************************************************/
class AddressBookUI
{
    public:
        
        AddressBookUI(AddressBookController& controller);
        virtual ~AddressBookUI();

        //Model has changed, update info in UI
        virtual bool updateData(void) = 0;

        //Display the UI
        virtual bool show(void) = 0;

    private:
        AddressBookController &appController;
};

#endif
