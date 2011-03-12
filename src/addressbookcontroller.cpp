#include "addressbookcontroller.h"
#include "errorinfo.h"
#include "contact.h"

ErrorInfo AddressBookController::submitContact(const Contact &c)
{    
    if(!c.isValidToAdd())
    {
        return ErrorInfo(ERR_CONTACT_NOT_VALID, "Invalid Contact. Make sure \
                            all required fields are filled.");
    }

    if(dataStore.addContact(c))
    {
        return ErrorInfo(ERR_OK, "OK");
    }
    else
    {
        return ErrorInfo(ERR_UNKNOWN_ERROR, "Unknown Error. Could not add contact.");
    }
}


ErrorInfo AddressBookController::deleteContact(Contact::ContactId id)
{
    if(dataStore.deleteContact(id))
        return ErrorInfo(ERR_OK, "OK");
    else
        return ErrorInfo(ERR_UNKNOWN_ERROR, "Unknown Error. Could not delete contact");
}


ErrorInfo AddressBookController::getContact(Contact::ContactId id, Contact &c)
{
    if(dataStore.getContact(id, c))
    {
        return ErrorInfo(ERR_OK, "OK");
    }
    else
    {
        return ErrorInfo(ERR_CONTACT_NOT_FOUND, "No contact with that id was found");
    }


}


ErrorInfo AddressBookController::getAllContacts(Contact::ContactRecordSet &rs)
{
    
    if(dataStore.getAllContacts(rs))  
    {
        return ErrorInfo(ERR_OK, "OK");
    }
    else
    {
        return ErrorInfo(ERR_UNKNOWN_ERROR, "Unknown Error. Could Not retrieve contacts.");
    }
}

