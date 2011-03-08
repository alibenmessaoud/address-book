#ifndef UI_CONTACT_DETAIL_FORM
#define UI_CONTACT_DETAIL_FORM

#include <QFrame>
#include <QLabel>
#include "contact.h"
#include "addressbookcontroller.h"

class ContactDetailForm : public QFrame
{
    Q_OBJECT

    public:
        ContactDetailForm(AddressBookController &b, QWidget *parent=0);

    private:
        AddressBookController &contactBook;
        QLabel *outLabel;

    private slots:
        void displayContact(Contact::ContactId id);



};
#endif
