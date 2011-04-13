#include <string>
#include <exception>
#include <iostream>
#include "addressbookcontroller.h"
#include "dummydatasource.h"
#include <QApplication>

#include "sqlitedatasource.h"

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
    
}

