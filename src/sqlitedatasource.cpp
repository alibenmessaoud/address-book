#include <algorithm>
#include <sqlite3.h>
#include <string>
#include <stdexcept>
#include <vector>
#include "addressbookview.h"
#include "contact.h"
#include "errorinfo.h"
#include "sqlitedatasource.h"

const std::string SQLiteDataSource::tableName = "Contacts";

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
    std::string createTableStatementString = 
            "CREATE TABLE " + SQLiteDataSource::tableName + "(test INTEGER PRIMARY KEY);";

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
    return ErrorInfo(ERR_UNKNOWN_ERROR, "Not yet implemented");
}

ErrorInfo SQLiteDataSource::getAllContacts(Contact::ContactRecordSet &rs)
{
    return ErrorInfo(ERR_UNKNOWN_ERROR, "Not yet implemented");
}


ErrorInfo SQLiteDataSource::addContact(const Contact& c)
{
    return ErrorInfo(ERR_UNKNOWN_ERROR, "Not yet implemented");
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

