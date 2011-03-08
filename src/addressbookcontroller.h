#ifndef ADDRESSBOOKCONTROLLER_H
#define ADDRESSBOOKCONTROLLER_H

//addressbookcontroller.h - main controller of addressbook application.  Business logic layer between the UI and the backend data source.

#include <memory>
#include "contact.h"
#include "datasource.h"
#include "errorinfo.h"

class AddressBookController
{
    public:
        //Interface to UI module
        ErrorInfo submitContact(const Contact &c);
        ErrorInfo deleteContact(Contact::ContactId id);
        ErrorInfo getAllContacts(Contact::ContactRecordSet &rs);
        ErrorInfo searchContacts(const Contact &c, Contact::ContactRecordSet &rs);

        //Assumes ownership of DataSource object passed in to constructor
        //Deleted when destructor of this object is run
        explicit AddressBookController(DataSource &d) : dataStore(d) { }
        
    private:
        DataSource &dataStore; 
};


#endif
