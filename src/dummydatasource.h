#ifndef DUMMYDATASOURCE_H
#define DUMMYDATASOURCE_H

//dummydatasource.h
//A mock/dummy class that implements the DataSource interface


#define NUM_CONTACTS 5

#include <vector>
#include "datasource.h"
#include "contact.h"



class DummyDataSource : DataSource
{
    private:
        std::vector<Contact> recordList;
    public:
        DummyDataSource();  
        ~DummyDataSource() { };
        
        virtual Contact getContact(int id);
        virtual ContactRecordSet getAllContacts();
        virtual bool addContact(const Contact& c);
        virtual bool updateContact(int id, const Contact& c);
        virtual bool deleteContact(int id);
};

#endif
