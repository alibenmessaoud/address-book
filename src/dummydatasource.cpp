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

std::auto_ptr<Contact> DummyDataSource::getContact(int id)
{


    //check if the item with this id exists
    try
    {
        //throws out of range exception if object does not exist
        Contact *c = new Contact(recordList.at(id-1));
        std::auto_ptr<Contact> ret(c);
        return ret;
    }
    catch(std::out_of_range &err)
    {
        //no item found, return null auto_ptr 
        return std::auto_ptr<Contact>();
    }

}

std::auto_ptr<ContactRecordSet> DummyDataSource::getAllContacts()
{
    if(recordList.empty())
    {
        return std::auto_ptr<ContactRecordSet>();
    }
    else
    {
        return std::auto_ptr<ContactRecordSet>(
                                new ContactRecordSet(recordList));
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

void DummyDataSource::deleteAllContacts(void)
{
    recordList.clear();    
}

