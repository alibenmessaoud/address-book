

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFrame>

#include "addressbookview.h"
#include "addressbookcontroller.h"
#include "addressbookmodel.h"
#include "qtaddressbookgui.h"
#include "qtaddcontactdialog.h"
#include "qtcontactlist.h"
#include "qtcontactdetailview.h"
#include "contact.h"

QtAddressBookGUI::QtAddressBookGUI(AddressBookController &controller, AddressBookModel &model,
    QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags),
    appController(controller), dataSource(model)
{
    createWidgets();
    setMinimumSize(640,480);
}

QtAddressBookGUI::~QtAddressBookGUI()
{

}
void QtAddressBookGUI::updateView()
{
    emit pullDataFromModel();
}


void QtAddressBookGUI::createWidgets()
{
    detailView = new QtContactDetailView(dataSource);

    list = new QtContactList(dataSource);
    list->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    newContactButton = new QPushButton("New Contact");
    editContactButton = new QPushButton("Edit");
    deleteContactButton = new QPushButton("Delete");

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(newContactButton);
    buttonLayout->addWidget(editContactButton);
    buttonLayout->addWidget(deleteContactButton);

    QVBoxLayout *rightSideLayout = new QVBoxLayout();
    rightSideLayout->addWidget(detailView);
    rightSideLayout->addLayout(buttonLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(list);
    mainLayout->addLayout(rightSideLayout);
    
    //Connect contact list to the detail form
    connect(list, 
            SIGNAL(contactSelected(Contact::ContactId)),
            detailView,
            SLOT(displayContact(Contact::ContactId)));

    connect(newContactButton, SIGNAL(clicked()),
            this, SLOT(addContact()));

    connect(deleteContactButton, SIGNAL(clicked()),
            this, SLOT(deleteContact()));

    //tell the sub-widgets to refresh their data from
    //
    //Will be emitted when the view is notified by
    //the model that the data has changed
    connect(this, SIGNAL(pullDataFromModel()), list,
            SLOT(getContactList())); 

    

    QFrame *mainWidget = new QFrame();
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
}

bool QtAddressBookGUI::enableEditMode()
{
    return true;
}

bool QtAddressBookGUI::disableEditMode()
{
    return true;
}

void QtAddressBookGUI::showUI()
{
    QMainWindow::show();
}

void QtAddressBookGUI::addContact()
{
    Contact newContact;
    QtAddContactDialog *addDialog = new QtAddContactDialog(newContact, this);

    if(addDialog->exec())
    {
        appController.submitContact(newContact);
    }
}

void QtAddressBookGUI::deleteContact()
{
    Contact::ContactId idToDelete = list->getSelectedContactId();

    if(idToDelete)
    {
        bool firstRow  = list->currentRow() == 0;
        bool onlyRowLeft = list->count() == 1;
        
        if(!onlyRowLeft)
        {
            if(firstRow)
            {
                list->setCurrentRow(list->currentRow()+1,QItemSelectionModel::SelectCurrent);
            }
            else
            {
                //It is NOT the only row left AND it is not the first row.
                //So in this case, selection moves to the previous row.
                list->setCurrentRow(list->currentRow()-1,QItemSelectionModel::SelectCurrent);
            }
        }
        else
        {
            //only row left, clear the contact detail view so it doesn't display the last
            //Contact selected before deletion
            detailView->clear();
        }
        
            appController.deleteContact(idToDelete);
    }
}

