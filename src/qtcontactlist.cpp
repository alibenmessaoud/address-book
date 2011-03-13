#include <QList>

#include "addressbookcontroller.h"
#include "contact.h"
#include "qtcontactlist.h"

#include <string>


/*
Constructor
    Populate list from passed in recordset

Populate List
    For each item in recordset
        Get the First Name & Last Name
        Create a new entry on the list with those name combined
*/

QtContactList::QtContactList(AddressBookController &controller, QWidget *parent) : 
    QListWidget(parent), appController(controller) 
{
    setSelectionMode(QAbstractItemView::SingleSelection);

    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(dispatchListItemContactId()));

    populateList();

}

void QtContactList::populateList(Contact::ContactId selected)
{

    //Get all the contacts from the data store
    Contact::ContactRecordSet allContacts;
    appController.getAllContacts(allContacts);
    
    Contact::ContactRecordSet::const_iterator it;

    std::string listTitle = "";
    QListWidgetItem *newItem;
    QListWidgetItem *selectedItem;
    
    //Create new list items for each contact
    for(it = allContacts.begin();it != allContacts.end();it++)
    {
        listTitle = it->firstName + " " +  it->lastName;
        newItem = new QListWidgetItem(tr(listTitle.c_str()), this);
        newItem->setData(Qt::UserRole, it->id);

        if(selected && (it->id == selected))
        {
            selectedItem = newItem;
            setCurrentItem(selectedItem, QItemSelectionModel::SelectCurrent);
        }
        
    } 
    
}        

void QtContactList::refreshList(void)
{
    //keep the id of the currently selected item
    QList<QListWidgetItem*> currentSelected = selectedItems();
    Contact::ContactId selectedContactId = 0;
    
    if(!currentSelected.isEmpty())
    {
        selectedContactId = currentSelected[0]->data(Qt::UserRole).toUInt();
    }

    clear();
    populateList(selectedContactId);

}

void QtContactList::dispatchListItemContactId(void)
{
    Contact::ContactId selectedItemId = currentItem()->data(Qt::UserRole).toUInt();

    emit contactSelected(selectedItemId);
}

