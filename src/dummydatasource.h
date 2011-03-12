#ifndef DATASTORAGE_DUMMYDATASOURCE_H
#define DATASTORAGE_DUMMYDATASOURCE_H

#include "datasource.h"
#include "contact.h"


const int NUM_CONTACTS = 5;

/************************************************************
    Class: DummyDataSource

    Author: Phil Grohe

    Mock object implementing the DataSource interface.
    Creates a vector with dummy data when created.
    DataSource interface methods act on this data rather
    than any kind of persistently stored data. Used as a 
    placeholder until DataSource implementations providing
    true persistence are written (flat file, SQL, etc...)
************************************************************/

class DummyDataSource : public DataSource
{
    public:
        //Data access services 
        virtual bool getContact(Contact::ContactId id, Contact &c);
        virtual bool getAllContacts(Contact::ContactRecordSet &rs);
        virtual bool addContact(const Contact& c);
        virtual bool updateContact(Contact::ContactId id, const Contact& c);
        virtual bool deleteContact(Contact::ContactId id);
        virtual bool deleteAllContacts(void);

        DummyDataSource();  
        ~DummyDataSource() { };

    private:
        bool idExists(Contact::ContactId id, Contact::ContactRecordSet::iterator &pos);

        Contact::ContactRecordSet recordList;
        Contact::ContactId nextId;
};

#endif
