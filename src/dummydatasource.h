#ifndef DUMMYDATASOURCE_H
#define DUMMYDATASOURCE_H

//dummydatasource.h
//A mock/dummy class that implements the DataSource interface


#define NUM_CONTACTS 5

#include <vector>
#include <memory>
#include "datasource.h"
#include "contact.h"



class DummyDataSource : public DataSource
{
    public:
        //Data access services 
        virtual bool getContact(int id, Contact &c);
        virtual bool getAllContacts(ContactRecordSet &rs);
        virtual bool addContact(const Contact& c);
        virtual bool updateContact(int id, const Contact& c);
        virtual bool deleteContact(int id);
        virtual bool deleteAllContacts(void);

        DummyDataSource();  
        ~DummyDataSource() { };

    private:
        std::vector<Contact> recordList;
};

#endif
