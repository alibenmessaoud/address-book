#include <string>
#include <exception>
#include <iostream>
#include "addressbookcontroller.h"
#include "dummydatasource.h"
#include <QApplication>

#include "sqlitedatasource.h"
#include "errorinfo.h"
#include "contact.h"

int main(int argc, char *argv[])
{
/*
    QApplication app(argc, argv);

    DummyDataSource dSrc;  
    AddressBookController myBook(dSrc);
    myBook.start();
    return app.exec();
*/

    std::string filename = "foo.db";

    SQLiteDataSource *myDB;
    try
    {
         myDB = new SQLiteDataSource(filename, false);
    }
    catch(const std::exception &e)
    {
        std::cout << "Couldn't open database " << filename << "." << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "Creating new database." << std::endl;

        try
        {
            myDB = new SQLiteDataSource(filename, true);
        }
        catch(const std::exception &e)
        {
            std::cout << "Couldn't create a new database." << std::endl;
            std::cout << "Exiting." << std::endl;
            return -1;
        }

    }

    Contact c;
    c.firstName = "A";
    c.lastName = "A";
    c.phoneNumber = "A";
    c.address = "A";
    c.email = "A";

    ErrorInfo e = myDB->addContact(c);

    if(e.code != ERR_OK)
    {
        std::cout << e.msg <<std::endl;
    }

    Contact x;

    myDB->getContact(1, x);

    std::cout << x.firstName << std::endl;
    std::cout << x.lastName << std::endl;

    delete myDB;
}

