#ifndef CONTACT_H
#define CONTACT_H

//contact.h
//All the information of any given contact in the address book
//grouped into one class

//No methods, equivalent to a struct

//TODO
//Still very early prototyping code. This might all be refactored.


#include <string>
#include <vector>

class Contact 
{
    public:
        typedef std::vector<Contact> ContactRecordSet;
        typedef unsigned int ContactId;

        std::string firstName;
        std::string lastName;
        std::string phoneNumber;
        std::string address;
        std::string email;
        ContactId id;
        bool isValidToAdd(void) const;
        bool isEmpty(void) const;
        Contact():firstName(), lastName(), phoneNumber(), email(), id(0) { }

};

#endif
