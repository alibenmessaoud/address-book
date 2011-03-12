#ifndef DATASTORAGE_DATASOURCE_H
#define DATASTORAGE_DATASOURCE_H

#include "contact.h"

/***********************************************************************
    Class: DataSource

    Author: Phil Grohe

    Interface class for the data storage back end of the addressbook.
    Provides services for basic retrieval and updating of the contact 
    list.

    Different types of backend storage solutions (flat file, HTTP, SQL,
    etc...) must implement this interface.
***********************************************************************/
class DataSource
{

    public:

        virtual bool getContact(Contact::ContactId id, Contact& c) = 0;
        virtual bool getAllContacts(Contact::ContactRecordSet &rs) = 0;
        virtual bool addContact(const Contact& c) = 0;
        virtual bool updateContact(Contact::ContactId id, const Contact& c) = 0;
        virtual bool deleteContact(Contact::ContactId id)=0;
        virtual bool deleteAllContacts(void)=0;

        virtual ~DataSource() {};

};

#endif
