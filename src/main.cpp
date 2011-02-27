#include <iostream>
#include "addressbookcontroller.h"
#include "dummydatasource.h"
#include "contact.h"
#include "errorinfo.h"



void printErrorDetails(const ErrorInfo &err)
{
    std::cout << "Error Code: " << err.code << std::endl;
    std::cout << "Error Message: " << err.msg << std::endl;
}

void printAllRecords(AddressBookController &book)
{
    std::cout << "Get all the contacts & print them." << std::endl;

    Contact::ContactRecordSet rs;
    ErrorInfo e = book.getAllContacts(rs);
    if(e.code != ERR_OK)
    {
        printErrorDetails(e);
        return;
    }
    
    if(rs.empty())
    {
        std::cout << "No records to print, book is empty!" << std::endl;

        return;
    }
    
    Contact::ContactRecordSet::const_iterator it;

    for(it=rs.begin(); it!=rs.end(); it++)
    {
        std::cout << "Id: " << it->id << std::endl;
        std::cout << "First Name: " << it->firstName << std::endl;
        std::cout << "Phone Number: " << it->phoneNumber << std::endl;
    }
}

void addValidContact(AddressBookController &book)
{
    std::cout << "Add an valid contact to the AddressBookController" << std::endl;

    Contact c;
    c.firstName = "New Contact";
    c.lastName = "New Contact";
    c.phoneNumber = "New Contact";
    c.email = "New Contact";
    c.address = "New Contact";

    ErrorInfo e = book.submitContact(c);
    if(e.code != ERR_OK)
        printErrorDetails(e);
}

void addInvalidContact(AddressBookController &book)
{
    
    std::cout << "Attempt to add empty contact." << std::endl;

    //Creates a blank contact
    //Valid contact must have names & either a
    //phone number or email
    Contact myContact;
    ErrorInfo e = book.submitContact(myContact); 
    if(e.code != ERR_OK)
        printErrorDetails(e);
     

}

void deleteAContact(AddressBookController &book, Contact::ContactId idToDelete)
{
    std::cout << "Delete an existing contact" << std::endl;
    Contact::ContactRecordSet rs;
    ErrorInfo e = book.getAllContacts(rs);

    if(e.code != ERR_OK)
    {
        printErrorDetails(e);
        return;
    }
    
    if(!rs.empty())
    {
        e = book.deleteContact(idToDelete);
        if(e.code != ERR_OK)
            printErrorDetails(e);

        return;
    }
    else
    {
        std::cout << "No records to delete, book is empty!" << std::endl;

        return;
    }
}


int main()
{

    DummyDataSource *dSrc = new DummyDataSource;  
    AddressBookController myBook(dSrc);
    std::cout << std::endl; 
    
    printAllRecords(myBook);

    //delete 2 contacts with non-contiguous ids
    deleteAContact(myBook, 3);
    printAllRecords(myBook);

    deleteAContact(myBook, 1);
    printAllRecords(myBook);

    //try to delete a contact with an id that doesn't exist
    deleteAContact(myBook, 57);
    printAllRecords(myBook);



    return 0;
}
