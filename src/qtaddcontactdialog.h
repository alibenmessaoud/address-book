#ifndef VIEW_QTADDCONTACTDIALOG_H
#define VIEW_QTADDCONTACTDIALOG_H

#include <QDialog>
#include <QWidget>
#include "qtcontactform.h"

/***********************************************************************
    Class: QtAddContactDialog

    Author: Phil Grohe

    Qt Dialog presenting a form to add a new contact.    
***********************************************************************/

class QtAddContactDialog : public QDialog
{
    public:
        QtAddContactDialog(QWidget* parent=0, Qt::WindowFlags f=0);

    private:
        QtContactForm *contactForm;
};

#endif
