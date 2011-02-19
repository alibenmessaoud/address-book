#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

//addressbook.h - main controller of addressbook application.  Business logic layer between the UI and the backend data source.

#include <memory>
#include "contact.h"
#include "datasource.h"

class AddressBook
{
    public:
        //Interface to UI module
        bool submitContact(Contact &c);
        bool deleteContact(Contact &c);
        std::auto_ptr<ContactRecordSet> getAllContacts(void);
        std::auto_ptr<ContactRecordSet> searchContacts(Contact &c);

        explicit AddressBook(DataSource *d) : dataStore(d) { }
        
    private:
        //Validation
        bool isContactValidtoAdd(Contact &c);

        std::auto_ptr<DataSource> dataStore; 
};


#endif
