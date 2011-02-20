//dummydatasource.cpp
//Implementation of dummy data source class

#include <string>
#include <sstream>
#include <stdexcept>
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

bool DummyDataSource::getContact(int id, Contact &c)
{
    //Currently this will never return false because the dummy data
    //source is a vector contained in the class
    //In a real data source backed by a database or file this 
    //would return false if the file could not be opened or the
    //database could not be reached

    //Does not return false for record not found, returns true
    //but output pointer parameter is NULL

    //check if the item with this id exists
    try
    {
        //throws out of range exception if object does not exist
        c = Contact(recordList.at(id-1));
        return true;
    }
    catch(std::out_of_range &err)
    {
        //no item found, return null auto_ptr 
        c =  Contact();
        return true;
    }

    
}

bool DummyDataSource::getAllContacts(ContactRecordSet &rs)
{
    //Never returns false in this dummy class
    //Would return false in a real datasource if file could not be
    //opened or database could not be reached for example

    if(recordList.empty())
    {
        rs = ContactRecordSet();
        return true;
    }
    else
    {
         rs = ContactRecordSet(recordList);
        return true;
    }
}

bool DummyDataSource::addContact(const Contact& c)
{
    recordList.push_back(c);
    return true;
}

bool DummyDataSource::updateContact(int id, const Contact& c)
{

    try
    {
        recordList.at(id-1) = c;
        return true;
    }
    catch(std::out_of_range &err)
    {
        //no item with that id
        return false;
    }
}

bool DummyDataSource::deleteContact(int id)
{
    ContactRecordSet::iterator it = recordList.begin() + (id-1);

    if(it >= recordList.end())
    {
        //item does not exist, cannot delete
        return false;
    }
    else
    {
        recordList.erase(it);
        return true;

    }


}

bool DummyDataSource::deleteAllContacts(void)
{
    recordList.clear();    
    return true;
}

