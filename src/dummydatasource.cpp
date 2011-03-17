//dummydatasource.cpp
//Implementation of dummy data source class

#include <string>
#include <sstream>
#include <stdexcept>

#include "addressbookmodel.h"
#include "dummydatasource.h"
#include "contact.h"


DummyDataSource::DummyDataSource()
{

    nextId = 1;

    std::stringstream ss;
    std::string temp;
    Contact c;
    
    for(int i=0; i < NUM_CONTACTS; i++)
    {
        ss << i+1; 
        temp = ss.str();
        c.firstName = temp;
        c.lastName = temp;
        c.phoneNumber = temp;
        c.address = temp;
        c.email = temp;
    
        addContact(c);
        ss.str("");
    }
        
}

void DummyDataSource::registerView(AddressBookModel *viewToRegister)
{
    if(viewToRegister)
    {
        observerList.push_back(viewToRegister);
    }

}

void DummyDataSource::removeView(AddressBookModel *viewToRemove)
{
    if(viewToRemove)
    {
        //Find the view in the list and remove it
        //How does this work?
        //How do we compare objects
        //Look up pointer comparison before implementing this
    }
}

void DummyDataSource::notifyViews(void)
{
    /*
    for each element in observer list
    call the updateView method
    */
}

}

bool DummyDataSource::getContact(Contact::ContactId id, Contact &c)
{
    Contact::ContactRecordSet::iterator it;
    
    if(idExists(id, it))
    {
        c = *it;
        return true;
    }
    else
    {
        return false;
    }

}

bool DummyDataSource::getAllContacts(Contact::ContactRecordSet &rs)
{
    //Never returns false in this dummy class
    //Would return false in a real datasource if file could not be
    //opened or database could not be reached for example

    if(recordList.empty())
    {
        rs = Contact::ContactRecordSet();
        return true;
    }
    else
    {
         rs = Contact::ContactRecordSet(recordList);
        return true;
    }
}

bool DummyDataSource::addContact(const Contact& c)
{
    Contact contactToAdd = c;
    contactToAdd.id = nextId;
    recordList.push_back(contactToAdd);
    nextId++;
    return true;
}

bool DummyDataSource::updateContact(Contact::ContactId id, const Contact& c)
{
    Contact::ContactRecordSet::iterator it;

    if(idExists(id, it))
    {
        *it = c;
        return true;
    }
    else
    {
        //no item with that id
        return false;
    }
}

bool DummyDataSource::deleteContact(Contact::ContactId id)
{
    Contact::ContactRecordSet::iterator itemToDeletePosition;

    if(idExists(id, itemToDeletePosition))
    {
        recordList.erase(itemToDeletePosition);
        return true;
    }
    else
    {
        //item does not exist, cannot delete
        return false;
    }
}

bool DummyDataSource::deleteAllContacts(void)
{
    recordList.clear();    
    return true;
}

bool DummyDataSource::idExists(Contact::ContactId id, Contact::ContactRecordSet::iterator &pos)
{
    Contact::ContactRecordSet::iterator it;

    for(it = recordList.begin(); it != recordList.end(); it++)
    {
        //id found
        if(it->id == id)
        {
            pos = it;
            return true;

        }
    }

    //no item with that id exists
    //if loop has run it's course then it == recordList.end()
    pos = it;
    return false;
}
