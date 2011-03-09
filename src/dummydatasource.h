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
