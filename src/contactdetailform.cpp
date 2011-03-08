#include "contactdetailform.h"

#include <QHBoxLayout>

ContactDetailForm::ContactDetailForm(AddressBookController &b,
    QWidget *parent) : QFrame(parent), contactBook(b)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    outLabel = new QLabel("WAITING FOR SIGNAL");
    layout->addWidget(outLabel);

}

void ContactDetailForm::displayContact(Contact::ContactId id)
{
    
    outLabel->setText("RECEIVED SIGNAL");
}

