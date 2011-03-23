#ifndef UI_MAINWINDOW
#define UI_MAINWINDOW

#include <QMainWindow>   
#include <QPushButton>
#include "addressbookcontroller.h"
#include "addressbookmodel.h"
#include "addressbookview.h"
#include "qtcontactlist.h"
#include "qtcontactdetailview.h"

/***********************************************************************
    Class: QtAddressBookGUI

    Author: Phil Grohe

    Top level application window.  Instantiates sub widgets and connects
    their signals and slots.
***********************************************************************/

class QtAddressBookGUI : private QMainWindow, public AddressBookView
{
    Q_OBJECT

    public:
        QtAddressBookGUI(AddressBookController &controller, AddressBookModel &model, 
        QWidget *parent=0, Qt::WindowFlags flags=0);


        //AddressBookView interface
        virtual void updateView(void);
        virtual bool enableEditMode(void);
        virtual bool disableEditMode(void);
        virtual void showUI(void);
        virtual ~QtAddressBookGUI();

    signals:
        void pullDataFromModel(void);

    public slots:
        void addContact(void);

    private:
        void createWidgets(void);

        QtContactList *list;
        QtContactDetailView *detailView;
        QPushButton *addButton;

        AddressBookController& appController;
        AddressBookModel& dataSource;
}; 

#endif
