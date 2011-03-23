#include "qtaddcontactdialog.h"
#include <QDialog>
#include <QWidget>

QtAddContactDialog::QtAddContactDialog(QWidget *parent, Qt::WindowFlags f) :
            QDialog(parent, f), contactForm(new QtContactForm(this))
{
    setLayout(contactForm);
}
