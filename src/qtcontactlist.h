#ifndef UI_CONTACT_LIST
#define UI_CONTACT_LIST

#include <QListWidget>

#include "addressbookcontroller.h"
#include "contact.h"

/***********************************************************************
    Class: QtContactList

    Author: Phil Grohe

    List widget that displays the full contact book. Selecting a widget
    
    When a contact is selected will emit the contactSelected signal
    with the id of the contact.  The widget where the contact details
    will be displayed should have this signal connected to one if it's
    slots.
***********************************************************************/


/*
If an item is added or deleted from the addressbook, what happens?
    List must be refreshed to reflect the state of the address book
        List interface should provide a way to update the list from a new recordset

*/

class QtContactList : public QListWidget
{
    Q_OBJECT

    public:
        QtContactList(AddressBookController &controller, QWidget *parent=0); 

    public slots:
        void refreshList(void); 

    signals:
        void contactSelected(Contact::ContactId selectedId);

    private slots:
        void dispatchListItemContactId(void);
        void populateList(Contact::ContactId selected=0);

    private:
        AddressBookController &appController;
}; 

#endif
