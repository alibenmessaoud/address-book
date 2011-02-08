//dummydatasource.cpp
//Implementation of dummy data source class

#include "dummydatasource.h"
#include "contact.h"

DummyDataSource::DummyDataSource()
{
    data.firstName = "John";
    data.lastName = "Doe";
    data.phoneNumber = "(555)555-5555";
    data.address = "123 1st Street";
    data.email = "j.doe@abc.def";
}


Contact DummyDataSource::getContact(int id)
{
    return data;
}

bool DummyDataSource::addContact(const Contact& c)
{
    data.firstName = c.firstName;
    data.lastName = c.lastName;
    data.phoneNumber = c.phoneNumber;
    data.address = c.address;
    data.email = c.email;

    return true;
}

bool DummyDataSource::updateContact(int id, const Contact& c)
{
    addContact(c);
}

bool DummyDataSource::deleteContact(int id)
{
    return true;
}

