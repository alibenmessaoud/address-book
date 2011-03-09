#include "contactdetailform.h"
#include "errorinfo.h"

#include <string>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>

ContactDetailForm::ContactDetailForm(AddressBookController &b,
    QWidget *parent) : QFrame(parent), appController(b)
{
    createFormWidgets();
}

void ContactDetailForm::createFormWidgets(void)
{
    QFormLayout *layout = new QFormLayout(this);
    
    nameField = new QLineEdit();
    addressField = new QLineEdit();
    phoneNumberField = new QLineEdit();
    emailField = new QLineEdit();

    errorMsg = new QLabel("");

    layout->addRow("Name", nameField);
    layout->addRow("Address", addressField);
    layout->addRow("Phone Number", phoneNumberField);
    layout->addRow("Email", emailField);
    layout->addRow("", errorMsg);
    
}


void ContactDetailForm::displayContact(Contact::ContactId id)
{
    Contact c;

    ErrorInfo e = appController.getContact(id, c);

    if(e.code == ERR_OK)
    {
        std::string fullName = c.firstName + " " + c.lastName;

        nameField->setText(fullName.c_str());
        addressField->setText(c.address.c_str());
        phoneNumberField->setText(c.phoneNumber.c_str());
        emailField->setText(c.email.c_str());
    }
    else
    {
        errorMsg->setText(e.msg.c_str());
    }
}

