#ifndef MODEL_SQLITE_DATASOURCE_H
#define MODEL_SQLITE_DATASOURCE_H

#include <sqlite3.h>
#include <string>

/***********************************************************************
    Class: SQLiteDataSource

    Author: Phil Grohe

    A SQLite driven backend for the address book. Implements the
    AddressBookModel interface.
***********************************************************************/

class SQLiteDataSource
{
    public:
        SQLiteDataSource(const std::string& filename);
        ~SQLiteDataSource();

    private:
        sqlite3 *databaseHandle;

};

#endif
