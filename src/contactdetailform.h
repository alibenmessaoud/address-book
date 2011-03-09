#ifndef UI_CONTACT_DETAIL_FORM
#define UI_CONTACT_DETAIL_FORM

#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include "contact.h"
#include "addressbookcontroller.h"

class ContactDetailForm : public QFrame
{
    Q_OBJECT

    public:
        ContactDetailForm(AddressBookController &b, QWidget *parent=0);

    private:
        void createFormWidgets(void);

        AddressBookController &appController;
        QLineEdit *nameField;
        QLineEdit *addressField;
        QLineEdit *phoneNumberField;
        QLineEdit *emailField;
        QLabel *errorMsg;

    private slots:
        void displayContact(Contact::ContactId id);



};
#endif
