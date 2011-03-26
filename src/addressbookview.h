#ifndef VIEW_ADDRESSBOOKVIEW_H
#define VIEW_ADDRESSBOOKVIEW_H

/***********************************************************************
    Class: AddressBookView

    Author: Phil Grohe

    Interface for the application's views to implement.

    This class is the View in our MVC architecture.  It is the Observer
    to AddressBookModel's Subject.
***********************************************************************/
class AddressBookView
{
    public:
        
        virtual bool enableEditMode()=0;
        virtual bool disableEditMode()=0;
        virtual void showUI()=0; 

        //Model has changed, update info in UI
        virtual void updateView() = 0;
        virtual ~AddressBookView() {};        
        
};

#endif
