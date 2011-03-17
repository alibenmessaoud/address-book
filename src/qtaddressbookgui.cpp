#include "qtaddressbookgui.h"
#include "addressbookcontroller.h"

QtAddressBookGUI::QtAddressBookGUI(AddressBookController & controller) : AddressBookView(controller)
{
    //create main window
    appWindow = new QtMainWindow(appController);

}

bool QtAddressBookGUI::updateData(void)
{
    appWindow->updateData(); 
    return true;
}


bool QtAddressBookGUI::show(void)
{
    appWindow->show();
    return true;
}

QtAddressBookGUI::~QtAddressBookGUI()
{
    //delete main window
    delete appWindow;
}

