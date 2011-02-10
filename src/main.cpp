#include <iostream>
#include <string>
#include "dummydatasource.h"
#include "contact.h"


//Testing code for the DataSource interface as implemented by the DummyDataSource class

int main()
{
    DummyDataSource myDataSource;

    ContactRecordSet rs = myDataSource.getAllContacts();

    ContactRecordSet::const_iterator it;

    for(it=rs.begin(); it != rs.end(); it++)
    {
        std::cout << it->firstName << std::endl;
    }

    std::cout << "3rd Contact's first name is: " <<myDataSource.getContact(3).firstName << std::endl;

    Contact c = {"Joe", "Blow", "555-5555", "123 1st St", "asdf@abc.def"};

    myDataSource.updateContact(5, c);
    std::cout << "5th Contact's first name is: " << myDataSource.getContact(5).firstName << std::endl;
    
    myDataSource.deleteContact(5);

    rs = myDataSource.getAllContacts();

    for(it=rs.begin(); it != rs.end(); it++)
    {
        std::cout << it->firstName << std::endl;
    }


    return 0;
}
