#ifndef CORE_ADDRESS_BOOK_H
#define CORE_ADDRESS_BOOK_H


#include "contact.h"
#include "datasource.h"
#include "errorinfo.h"


class AddressBookUI;
/************************************************************
    Class: AddressBookController

    Author: Phil Grohe

    Main application controller for the address book program,
    The intermediary between the UI and the data storage
    object.  Routes UI actions to data store and returns
    data to UI. Interprets errors from data store and
    passes ErrorInfo objects back up to UI
************************************************************/

class AddressBookController
{
    public:
        //Interface to UI module
        ErrorInfo submitContact(const Contact &c);
        ErrorInfo deleteContact(Contact::ContactId id);
        ErrorInfo getContact(Contact::ContactId id, Contact &c);
        ErrorInfo getAllContacts(Contact::ContactRecordSet &rs);

        //Stores reference to DataSource  abstract base class
        //allowing for different kinds of back end data storage
        //provided it implements the DataSource interface
        explicit AddressBookController(DataSource &d);
        ~AddressBookController();
        
    private:
        DataSource &dataStore; 
        AddressBookUI *frontEnd;
        
};


#endif
