

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>

#include "mainwindow.h"
#include "addressbookcontroller.h"
#include "contactlist.h"
#include "contactdetailform.h"
#include "contact.h"

MainWindow::MainWindow(AddressBookController &b, QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags), addrBook(b)
{
    ContactList *list = new ContactList(addrBook);
    list->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    ContactDetailForm *detailView = new ContactDetailForm(addrBook);
    


    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(list);
    mainLayout->addWidget(detailView);
    
    connect(list, 
            SIGNAL(contactSelected(Contact::ContactId)),
            detailView,
            SLOT(displayContact(Contact::ContactId)));

    QFrame *mainWidget = new QFrame();
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
    setMinimumSize(640,480);

}
