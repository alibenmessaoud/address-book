#ifndef UI_MAINWINDOW
#define UI_MAINWINDOW

//Main application window for address book 

/*
Build window
    Store reference to the addressbook controller 
    Build left side list of contacts
    Build right form with contact details
    Build buttons Actions
    Connect buttons to actions

    Actions
        -click list entry, update form with that contact
        -Edit
        -Add

*/
    
#include <QMainWindow>   

#include "addressbookcontroller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(AddressBookController &b, QWidget *parent=0, 
                    Qt::WindowFlags flags=0);

    private:
        AddressBookController &addrBook;
}; 

#endif
