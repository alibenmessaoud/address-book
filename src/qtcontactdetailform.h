#ifndef UI_QTCONTACTDETAIL_FORM
#define UI_QTCONTACTDETAIL_FORM

#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include "contact.h"
#include "addressbookmodel.h"

/***********************************************************************
Class: QtContactDetailForm

Author: Phil Grohe

Qt widget for displaying all the fields of a Contact.

Slot displayContact(Contact::ContactId id) receives the contact to
be displayed and 
***********************************************************************/

class QtContactDetailForm : public QFrame
{
    Q_OBJECT

    public:
        QtContactDetailForm(AddressBookModel &model, QWidget *parent=0);

    private slots:
        void displayContact(Contact::ContactId id);

    private:
        void createFormWidgets(void);

        QLineEdit *nameField;
        QLineEdit *addressField;
        QLineEdit *phoneNumberField;
        QLineEdit *emailField;
        QLabel *errorMsg;

        AddressBookModel &dataSource;
};
#endif
