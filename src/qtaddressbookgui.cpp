

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
#include "qteditcontactdialog.h"
#include "qterrordialog.h"
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

    connect(editContactButton, SIGNAL(clicked()),
            this, SLOT(editContact()));

    //tell the sub-widgets to refresh their data from
    //
    //Will be emitted when the view is notified by
    //the model that the data has changed
    connect(this, SIGNAL(pullDataFromModel()), list,
            SLOT(refreshContactList())); 

    QFrame *mainWidget = new QFrame();
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);

    //Needed to get the detail view form to display
    //the initial selection at startup.
    //When the list object is first created the signals / slots
    //arent yet connected so the initial selection isn't shown
    //This manual call will cause it to update
    list->refreshContactList();
}

void QtAddressBookGUI::showUI()
{
    QMainWindow::show();
}

void QtAddressBookGUI::addContact()
{
    Contact newContact;
    QtAddContactDialog *addDialog = new QtAddContactDialog(newContact, this);

    while(addDialog->exec())
    {
        ErrorInfo e = appController.submitContact(newContact);

        if(e.code == ERR_OK)
        {
            break;
        }
    
        //display error dialog
        QtErrorDialog *errDialog = new QtErrorDialog(e.msg, this);
        errDialog->exec();
    
    }
}

void QtAddressBookGUI::editContact()
{
    Contact::ContactId idToEdit = list->getSelectedContactId();
    
    Contact editingContact;
    ErrorInfo getContactErrorStatus = dataSource.getContact(idToEdit, editingContact);

    if(getContactErrorStatus.code != ERR_OK)
    {
        //The id of the Contact user wants to edit doesn't exist
        //Should never happen since they are selecting it from a list
        //of existing id
        //display error dialog
        QtErrorDialog *errDialog = new QtErrorDialog(getContactErrorStatus.msg, this);
        errDialog->exec();
        return;
    }
   
    QtEditContactDialog *editDialog = new QtEditContactDialog(editingContact, this);

    while(editDialog->exec())
    {
        ErrorInfo editErrorStatus = appController.editContact(idToEdit, editingContact);

        if(editErrorStatus.code == ERR_OK)
        {
            break;
        }

        //display error dialog
        QtErrorDialog *errDialog = new QtErrorDialog(editErrorStatus.msg, this);
        errDialog->exec();
    }
}

void QtAddressBookGUI::deleteContact()
{
    Contact::ContactId idToDelete = list->getSelectedContactId();

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
    
    ErrorInfo deleteErrorStatus = appController.deleteContact(idToDelete);
    if(deleteErrorStatus.code != ERR_OK)
    {
        //display error dialog
        QtErrorDialog *errDialog = new QtErrorDialog(deleteErrorStatus.msg, this);
        errDialog->exec();
        return;
    }
}

