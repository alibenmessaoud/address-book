#include "qtcontactdetailform.h"
#include "errorinfo.h"

#include <string>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>

QtContactDetailForm::QtContactDetailForm(AddressBookModel& model, 
                    QWidget *parent) : QFrame(parent), dataSource(model)
{
    createFormWidgets();
}

void QtContactDetailForm::createFormWidgets(void)
{
    QFormLayout *layout = new QFormLayout(this);
    
    nameField = new QLineEdit();
    addressField = new QLineEdit();
    phoneNumberField = new QLineEdit();
    emailField = new QLineEdit();
    

    
    nameField->setReadOnly(true);
    addressField->setReadOnly(true);
    phoneNumberField->setReadOnly(true);
    emailField->setReadOnly(true);
    
    errorMsg = new QLabel("");

    layout->addRow("Name", nameField);
    layout->addRow("Address", addressField);
    layout->addRow("Phone Number", phoneNumberField);
    layout->addRow("Email", emailField);
    layout->addRow("", errorMsg);
    
}


void QtContactDetailForm::displayContact(Contact::ContactId id)
{
    Contact c;

     bool success = dataSource.getContact(id, c);

    if(success)
    {
        std::string fullName = c.firstName + " " + c.lastName;

        nameField->setText(fullName.c_str());
        addressField->setText(c.address.c_str());
        phoneNumberField->setText(c.phoneNumber.c_str());
        emailField->setText(c.email.c_str());
    }
    else
    {
        errorMsg->setText("ERROR RETRIEVING CONTACT, FIX ERROR HANDLING");
    }
}

