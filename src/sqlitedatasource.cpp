#include "sqlitedatasource.h"
#include <sqlite3.h>

SQLiteDataSource::SQLiteDataSource(const std::string &filename)
{
    sqlite3_open(filename.c_str(), &databaseHandle);
}   

SQLiteDataSource::~SQLiteDataSource()
{
    sqlite3_close(databaseHandle);
}
