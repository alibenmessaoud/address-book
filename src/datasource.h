#ifndef DATASOURCE_H
#define DATASOURCE_H

//datasource.h
//Interface that different data sources sub-class


//VERY preliminary design for interface for data source, will evolve

#include <memory>
#include "contact.h"

class DataSource
{

    public:
        //Data access services
        virtual bool getContact(int id, Contact& c) = 0;
        virtual bool getAllContacts(ContactRecordSet &rs) = 0;
        virtual bool addContact(const Contact& c) = 0;
        virtual bool updateContact(int id, const Contact& c) = 0;
        virtual bool deleteContact(int id)=0;
        virtual bool deleteAllContacts(void)=0;

        virtual ~DataSource() {};

};

#endif
