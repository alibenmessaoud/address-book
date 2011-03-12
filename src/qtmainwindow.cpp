

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>

#include "qtmainwindow.h"
#include "addressbookcontroller.h"
#include "qtcontactlist.h"
#include "qtcontactdetailform.h"
#include "contact.h"

QtMainWindow::QtMainWindow(AddressBookController &b, QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags), addrBook(b)
{
    QtContactList *list = new QtContactList(addrBook);
    list->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QtContactDetailForm *detailView = new QtContactDetailForm(addrBook);
    


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
