#ifndef UI_CONTACT_LIST
#define UI_CONTACT_LIST

#include <QListWidget>

#include "addressbookcontroller.h"
#include "contact.h"

/*
Widget displaying list of contacts

Should it be aware of the addressbookcontroller? No, it should just deal with a record set.  

If an item is added or deleted from the addressbook, what happens?
    List must be refreshed to reflect the state of the address book
        List interface should provide a way to update the list from a new recordset


*/

class ContactList : public QListWidget
{
    Q_OBJECT

    public:
        ContactList(AddressBookController &book, QWidget *parent=0); 


    signals:
        void contactSelected(Contact::ContactId selectedId);

    private slots:
        void dispatchListItemContactId(QListWidgetItem *item);

    private:
        void populateList(AddressBookController &book);
}; 

#endif
