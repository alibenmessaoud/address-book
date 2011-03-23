

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFrame>

#include "qtaddressbookgui.h"
#include "addressbookview.h"
#include "addressbookcontroller.h"
#include "addressbookmodel.h"
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
void QtAddressBookGUI::updateView(void)
{
    emit pullDataFromModel();
}


void QtAddressBookGUI::createWidgets(void)
{
    
    detailView = new QtContactDetailView(dataSource);

    list = new QtContactList(dataSource);
    list->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    addButton = new QPushButton("Add Contact");

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(list);
    mainLayout->addWidget(detailView);
    mainLayout->addWidget(addButton);
    
    //Connect contact list to the detail form
    connect(list, 
            SIGNAL(contactSelected(Contact::ContactId)),
            detailView,
            SLOT(displayContact(Contact::ContactId)));

    //tell the sub-widgets to refresh their data from
    //the model when the signal is emitted. 
    //
    //Will be emitted when the view is notified by
    //the model that the data has changed
    connect(this, SIGNAL(pullDataFromModel()), list,
            SLOT(getContactList())); 

    connect(addButton, SIGNAL(clicked()), this,
            SLOT(addContact()));

    QFrame *mainWidget = new QFrame();
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
}

bool QtAddressBookGUI::enableEditMode(void)
{
    return true;
}

bool QtAddressBookGUI::disableEditMode(void)
{
    return true;
}

void QtAddressBookGUI::showUI(void)
{
    QMainWindow::show();
}

void QtAddressBookGUI::addContact(void)
{
    Contact c;

    c.firstName = "Test";
    c.lastName = "Test";
    c.phoneNumber = "55555555";
    c.address = "23432 1st Ave";
    c.email = "adsf@adsf.asd";

    appController.submitContact(c);
}
