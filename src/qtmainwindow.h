#ifndef UI_MAINWINDOW
#define UI_MAINWINDOW

#include <QMainWindow>   
#include <QPushButton>
#include "addressbookcontroller.h"
#include "qtcontactlist.h"
#include "qtcontactdetailform.h"

/***********************************************************************
    Class: QtMainWindow

    Author: Phil Grohe

    Top level application window.  Instantiates sub widgets and connects
    their signals and slots.
***********************************************************************/

class QtMainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        QtMainWindow(AddressBookController &controller, QWidget *parent=0, 
                    Qt::WindowFlags flags=0);

        bool updateData(void);

    private:
        void createWidgets(void);

        QtContactList *list;
        QtContactDetailForm *detailView;
        QPushButton *addButton;

        AddressBookController& appController;

    private slots:
        void addContact(void);

    signals:
        void updateDataFromModel();
}; 

#endif
