#ifndef CORE_CONTACT_H
#define CORE_CONTACT_H

/************************************************************
    Class: Contact

    Author: Phil Grohe

    Data structure to hold a single address book contact's
    info.
************************************************************/

#include <string>
#include <vector>

class Contact 
{
    public:

        typedef std::vector<Contact> ContactRecordSet;
        typedef unsigned int ContactId;

        ContactId id;
        std::string firstName;
        std::string lastName;
        std::string phoneNumber;
        std::string address;
        std::string email;

        Contact():id(0), firstName(), lastName(), phoneNumber(), email(){ }
        bool isValidToAdd(void) const;
        bool isEmpty(void) const;

};

#endif
