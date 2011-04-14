#include <algorithm>
#include <sqlite3.h>
#include <string>
#include <stdexcept>
#include <vector>
#include "addressbookview.h"
#include "contact.h"
#include "errorinfo.h"
#include "sqlitedatasource.h"


SQLiteDataSource::SQLiteDataSource(const std::string &filename, bool createDB):
                                    dbFilename(filename)
{
    //Do we want to create a new DB if the specified DB doesn't exist? 
    int flags = createDB ? (SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE) :
                            SQLITE_OPEN_READWRITE;

    try
    {
        openDatabase(flags);

        if(createDB)
        {
            createTable();
        }
    }
    catch(std::runtime_error &e)
    {
        sqlite3_close(databaseHandle);
        throw;
    }
}   

SQLiteDataSource::~SQLiteDataSource()
{
    sqlite3_close(databaseHandle);
}


void SQLiteDataSource::openDatabase(int openFlags)
{
    
    int openResult = sqlite3_open_v2(dbFilename.c_str(),
                                    &databaseHandle,
                                    openFlags,
                                    0);

    if(openResult != SQLITE_OK)
    {
        std::string errMsg = sqlite3_errmsg(databaseHandle);
        throw std::runtime_error(errMsg);
    }        
        
}

void SQLiteDataSource::createTable()
{
    //Prepare the SQLite statement
    std::string createTableStatementString = "CREATE TABLE Contacts"
                                            "(id INTEGER PRIMARY KEY,"
                                            "firstname TEXT NOT NULL,"
                                            "lastname TEXT NOT NULL,"
                                            "phonenum TEXT NOT NULL,"
                                            "address TEXT,"
                                            "email TEXT);";

    sqlite3_stmt *compiledStatement;

    int result = sqlite3_prepare_v2(databaseHandle, createTableStatementString.c_str(),
                    -1, &compiledStatement, NULL);

    if(result != SQLITE_OK)
    {
        //destroy compiled statement
        std::string errMsg = sqlite3_errmsg(databaseHandle);
        sqlite3_finalize(compiledStatement);
        
        throw std::runtime_error(errMsg);
    }

    //Execute the SQLite statement
    result = sqlite3_step(compiledStatement);

    if(result != SQLITE_DONE)
    {
        std::string errMsg = sqlite3_errmsg(databaseHandle);
        sqlite3_finalize(compiledStatement);
        throw std::runtime_error(errMsg);
    }

    sqlite3_finalize(compiledStatement);
 
}

bool SQLiteDataSource::isViewRegistered(AddressBookView *viewToCheck)
{
    std::vector<AddressBookView*>::const_iterator it;
    it = std::find(observerList.begin(), observerList.end(), viewToCheck);

    if(it == observerList.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void SQLiteDataSource::registerView(AddressBookView *viewToRegister)
{
    
    if(viewToRegister && !isViewRegistered(viewToRegister))
    {
        observerList.push_back(viewToRegister);
    }

}

void SQLiteDataSource::removeView(AddressBookView *viewToRemove)
{
    if(viewToRemove)
    {
        //Find the view in the list and remove it
        std::vector<AddressBookView*>::iterator it;
        it = std::find(observerList.begin(), observerList.end(), viewToRemove);

        if(it != observerList.end())
            observerList.erase(it);

    }
 
}

void SQLiteDataSource::notifyViews()
{
    std::vector<AddressBookView*>::iterator it;

    for(it = observerList.begin(); it != observerList.end(); it++)
    {
        (*it)->updateView();
    }

}

ErrorInfo SQLiteDataSource::getContact(Contact::ContactId id, Contact& c)
{
    //create sql prepared statement
    std::string sqlStatement = "SELECT * FROM Contacts WHERE id=?;"; 

    sqlite3_stmt *preparedStatement;

    int prepareResult = sqlite3_prepare_v2(databaseHandle,
                                            sqlStatement.c_str(),
                                            -1,
                                            &preparedStatement,
                                            NULL);

    if(prepareResult != SQLITE_OK)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not retrieve contact.");
    }


    //bind parameters to SQL statement
    sqlite3_bind_int(preparedStatement, 1, id);

    //execute statement & check result
    int stepResult = sqlite3_step(preparedStatement);
    
    if(stepResult != SQLITE_ROW)
    {
        sqlite3_finalize(preparedStatement);
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not retrieve contact.");
    }

    //package column values into Contact object
    Contact retrieved;

    retrieved.id = sqlite3_column_int(preparedStatement, 0);
    retrieved.firstName = reinterpret_cast<const char*>(sqlite3_column_text(preparedStatement, 1));
    retrieved.lastName = reinterpret_cast<const char*>(sqlite3_column_text(preparedStatement, 2));
    retrieved.phoneNumber = reinterpret_cast<const char*>(sqlite3_column_text(preparedStatement, 3));
    retrieved.address = reinterpret_cast<const char*>(sqlite3_column_text(preparedStatement, 4));
    retrieved.email = reinterpret_cast<const char*>(sqlite3_column_text(preparedStatement, 5));


    //assign Contact object to OUT parameter
    c = retrieved;    

    //finalize prepared statement
    sqlite3_finalize(preparedStatement);

    return ErrorInfo(ERR_OK, "OK");
}

ErrorInfo SQLiteDataSource::getAllContacts(Contact::ContactRecordSet &rs)
{
    return ErrorInfo(ERR_UNKNOWN_ERROR, "Not yet implemented");
}


ErrorInfo SQLiteDataSource::addContact(const Contact& c)
{
    //create sql prepared statement
    std::string insertStatement =   "INSERT INTO Contacts VALUES("
                                    "NULL,?,?,?,?,?);";

    sqlite3_stmt *compiledStatement;

    int prepareResult = sqlite3_prepare_v2(databaseHandle, insertStatement.c_str(),
                                    -1, &compiledStatement, NULL);


    if(prepareResult != SQLITE_OK)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not add contact.");
    }

    //bind contact fields to variables in SQL statement
    sqlite3_bind_text(compiledStatement, 1, c.firstName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(compiledStatement, 2, c.lastName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(compiledStatement, 3, c.phoneNumber.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(compiledStatement, 4, c.address.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(compiledStatement, 5, c.email.c_str(), -1, SQLITE_STATIC);

    //execute SQL statement & check results
    int stepResult = sqlite3_step(compiledStatement);
    sqlite3_finalize(compiledStatement);
    
    if(stepResult != SQLITE_DONE)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not add contact");
    }

    return ErrorInfo(ERR_OK, "OK");
}

ErrorInfo SQLiteDataSource::updateContact(Contact::ContactId id, const Contact&)
{
    return ErrorInfo(ERR_UNKNOWN_ERROR, "Not yet implemented");
}

ErrorInfo SQLiteDataSource::deleteContact(Contact::ContactId id)
{
    return ErrorInfo(ERR_UNKNOWN_ERROR, "Not yet implemented");
}


ErrorInfo SQLiteDataSource::deleteAllContacts()
{
    return ErrorInfo(ERR_UNKNOWN_ERROR, "Not yet implemented");
}

