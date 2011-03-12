#ifndef UI_MAINWINDOW
#define UI_MAINWINDOW

#include <QMainWindow>   
#include "addressbookcontroller.h"

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
        QtMainWindow(AddressBookController &b, QWidget *parent=0, 
                    Qt::WindowFlags flags=0);

    private:
        AddressBookController &addrBook;
}; 

#endif
