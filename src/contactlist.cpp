
#include "addressbookcontroller.h"
#include "contact.h"
#include "contactlist.h"

#include <string>


/*
Constructor
    Populate list from passed in recordset

Populate List
    For each item in recordset
        Get the First Name & Last Name
        Create a new entry on the list with those name combined
*/

ContactList::ContactList(AddressBookController &book, QWidget *parent) : 
    QListWidget(parent) 
{
    setSelectionMode(QAbstractItemView::SingleSelection);

    populateList(book);

    connect(this, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(dispatchListItemContactId(QListWidgetItem *)));

}

void ContactList::populateList(AddressBookController &book)
{

    Contact::ContactRecordSet allContacts;
    book.getAllContacts(allContacts);
    
    Contact::ContactRecordSet::const_iterator it;

    std::string listTitle = "";
    QListWidgetItem *newItem;
    
    for(it = allContacts.begin();it != allContacts.end();it++)
    {
        listTitle = it->firstName + " " +  it->lastName;
        newItem = new QListWidgetItem(tr(listTitle.c_str()), this);
        newItem->setData(Qt::UserRole, it->id);
    } 
}        

void ContactList::dispatchListItemContactId(QListWidgetItem *item)
{
    Contact::ContactId selectedItemId = item->data(Qt::UserRole).toUInt();

    emit contactSelected(selectedItemId);
}
