//dummydatasource.cpp
//Implementation of dummy data source class

#include <string>
#include <sstream>
#include "dummydatasource.h"
#include "contact.h"

DummyDataSource::DummyDataSource()
{
    std::stringstream ss;
    std::string temp;
    Contact c;
    
    for(int i=0; i < NUM_CONTACTS; i++)
    {
        ss << i; 
        temp = ss.str();
        c.firstName = temp;
        c.lastName = temp;
        c.phoneNumber = temp;
        c.address = temp;
        c.email = temp;
    
        recordList.push_back(c); 
        ss.str("");
    }
        
}


Contact DummyDataSource::getContact(int id)
{
    return recordList[id-1];
}

ContactRecordSet DummyDataSource::getAllContacts()
{
    return recordList;
}

bool DummyDataSource::addContact(const Contact& c)
{
    recordList.push_back(c);
    return true;
}

bool DummyDataSource::updateContact(int id, const Contact& c)
{
    recordList[id-1] = c;
    return true;
}


bool DummyDataSource::deleteContact(int id)
{
    recordList.erase(recordList.begin()+ (id-1));
    return true;
}

