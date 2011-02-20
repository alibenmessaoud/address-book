#include <iostream>
#include "addressbookcontroller.h"
#include "dummydatasource.h"
#include "contact.h"
#include "errorinfo.h"


void printAllRecords(const ContactRecordSet &rs)
{
    ContactRecordSet::const_iterator it;

    for(it=rs.begin(); it!=rs.end(); it++)
    {
        std::cout << "First Name: " << it->firstName << std::endl;
        std::cout << "Phone Number: " << it->phoneNumber << std::endl;
        std::cout << std::endl;
    }
}

void printErrorDetails(const ErrorInfo &err)
{
    std::cout << "Error Code: " << err.code << std::endl;
    std::cout << "Error Message: " << err.msg << std::endl;
}
int main()
{

    DummyDataSource *dSrc = new DummyDataSource;  
    AddressBookController myBook(dSrc);
    
    std::cout << std::endl << std::endl;
    std::cout << "Attempt to add empty contact." << std::endl;
    Contact myContact;
    ErrorInfo e = myBook.submitContact(myContact); 
    printErrorDetails(e);
     
    std::cout << std::endl; 
    
    std::cout << "Get all the contacts & print them." << std::endl;
    ContactRecordSet myContactList; 
    e = myBook.getAllContacts(myContactList);
    printErrorDetails(e);
    printAllRecords(myContactList);

    return 0;
}
