

#include <QPushButton>
#include <QHBoxLayout>
#include <QFrame>

#include "qtmainwindow.h"
#include "addressbookcontroller.h"
#include "qtcontactlist.h"
#include "qtcontactdetailform.h"
#include "contact.h"

QtMainWindow::QtMainWindow(AddressBookController &controller, QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), appController(controller)
{
    createWidgets();
    setMinimumSize(640,480);

}

bool QtMainWindow::updateData(void)
{
    emit updateDataFromModel();
    return true;
}

void QtMainWindow::createWidgets(void)
{
    
    detailView = new QtContactDetailForm(appController);

    list = new QtContactList(appController);
    list->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    addButton = new QPushButton("Add Contact");

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(list);
    mainLayout->addWidget(detailView);
    mainLayout->addWidget(addButton);
    
    connect(list, 
            SIGNAL(contactSelected(Contact::ContactId)),
            detailView,
            SLOT(displayContact(Contact::ContactId)));

    connect(this, SIGNAL(updateDataFromModel()), list,
            SLOT(refreshList())); 

    connect(addButton, SIGNAL(clicked()), this, SLOT(addContact()));

    QFrame *mainWidget = new QFrame();
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
}

void QtMainWindow::addContact(void)
{
    Contact c;

    c.firstName = "Slurm";
    c.lastName = "McSlurm";
    c.email = "s.mcslurm@slurm.abc";
    c.phoneNumber = "12332534";
    c.address = "Slurmsville";

    appController.submitContact(c);
}
    


 
