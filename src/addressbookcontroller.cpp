#include "addressbookview.h"
#include "addressbookmodel.h"
#include "addressbookcontroller.h"
#include "qtaddressbookgui.h"
#include "errorinfo.h"
#include "contact.h"

AddressBookController::AddressBookController(AddressBookModel &d) : dataStore(d)
{
    frontEnd = new QtAddressBookGUI(*this, dataStore);
    dataStore.registerView(frontEnd);

}

void AddressBookController::start()
{
    frontEnd->showUI();
}

AddressBookController::~AddressBookController()
{
    delete frontEnd;
}

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

ErrorInfo AddressBookController::deleteContact(const Contact::ContactId id)
{
    if(dataStore.deleteContact(id))
    {
        return ErrorInfo(ERR_OK, "OK");
    }
    else
    {
        return ErrorInfo(ERR_UNKNOWN_ERROR, "Unknown Error. Could not delete contact");
    }
}

ErrorInfo AddressBookController::editContact(const Contact::ContactId id, const Contact &c)
{
    if(!c.isValidToAdd())
    {
        return ErrorInfo(ERR_CONTACT_NOT_VALID, "Invalid Contact. Make sure \
        all required fields are filled.");
    }

    if(dataStore.updateContact(id, c))
    {
        return ErrorInfo(ERR_OK, "OK");
    }
    else
    {
        return ErrorInfo(ERR_UNKNOWN_ERROR, "Unknown Error. Could not update contact");
    }
}

