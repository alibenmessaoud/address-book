#include "contact.h"

bool Contact::isValidToAdd() const
{
    /*
    Adding a new contact requires:
    -first name
    -last name
    -at least one contact method (phone or email)
    */

    bool hasNames = !(firstName.empty() || lastName.empty());
    bool hasAContact = !(email.empty() && phoneNumber.empty());

    if(hasNames && hasAContact)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Contact::isEmpty() const
{
    if(firstName.empty() && 
        lastName.empty() &&
        phoneNumber.empty() && 
        address.empty() && 
        email.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
