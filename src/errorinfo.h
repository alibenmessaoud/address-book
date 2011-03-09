#ifndef ERRORINFO_H
#define ERRORINFO_H
//errorcode.h - Enumeration of error codes

#include <string>

enum ErrorCode
{
    ERR_OK,
    ERR_CONTACT_NOT_VALID,
    ERR_UNKNOWN_ERROR,
    ERR_CONTACT_NOT_FOUND
};

class ErrorInfo
{
    public: 
        ErrorCode code;
        std::string msg;

        ErrorInfo() : code(ERR_OK), msg("") {};
        ErrorInfo(ErrorCode code, std::string msg) : code(code), msg(msg) {};

};
#endif
