#include <iostream>
#include <string>
#include "dummydatasource.h"
#include "contact.h"


//Testing code for the DataSource interface as implemented by the DummyDataSource class

int main()
{
    DummyDataSource myDataSource;

    //Get and print out all contacts
    std::auto_ptr<ContactRecordSet> rs = myDataSource.getAllContacts();
    ContactRecordSet::const_iterator it;

    for(it=rs->begin(); it != rs->end(); it++)
    {
        std::cout << it->firstName << std::endl;
    }

    //Get a specific contact by id
    std::cout << "3rd Contact's first name is: " <<myDataSource.getContact(3)->firstName << std::endl;

    //Update a contact
    Contact c = {"Joe", "Blow", "555-5555", "123 1st St", "asdf@abc.def"};

    myDataSource.updateContact(5, c);
    std::cout << "5th Contact's first name is: " << myDataSource.getContact(5)->firstName << std::endl;
    
    //Delete a contact then print all records
    myDataSource.deleteContact(3);

    rs = myDataSource.getAllContacts();

    for(it=rs->begin(); it != rs->end(); it++)
    {
        std::cout << it->firstName << std::endl;
    }

    //Try to get a contact with an id that doesn't exist
    if(myDataSource.getContact(1).get())
    {
        std::cout << "Record exists" << std::endl;
    }
    else
    {
        std::cout << "Record does not exist" << std::endl;
    }

    //Try to update a contact with an id that doesn't exist
    if(myDataSource.updateContact(33, c))
    { 
        std::cout << "Update succeeded." << std::endl;
    }
    else
    {
        std::cout << "Update failed." << std::endl;
    }

    //Try to delete a contact with an id that doesn't exist
    if(myDataSource.deleteContact(67))
    {
        std::cout << "Delete succeeded." << std::endl;
    }
    else
    {
        std::cout << "Delete failed." << std::endl;
    }

    myDataSource.deleteAllContacts();

    rs = myDataSource.getAllContacts();

    if(!rs.get())
    {
        std::cout << "Record Set is empty." << std::endl;
    }

    return 0;
}
