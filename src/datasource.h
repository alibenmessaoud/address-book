#ifndef DATASOURCE_H
#define DATASOURCE_H

//datasource.h
//Interface that different data source objects must implement


//VERY preliminary design for interface for data source, will evolve

#include "contact.h"

class DataSource
{
    private:

    public:
        virtual Contact getContact(int id) = 0;
        virtual bool addContact(const Contact& c) = 0;
        virtual bool updateContact(int id, const Contact& c) = 0;
        virtual bool deleteContact(int id)=0;
        virtual ~DataSource() {};



};

#endif
