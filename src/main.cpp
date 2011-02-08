#include <iostream>
#include <string>
#include "dummydatasource.h"

int main()
{
    DummyDataSource myDataSource;

    Contact x = myDataSource.getContact(1);

    std::cout << x.firstName << std::endl;
    std::cout << x.lastName << std::endl;
    std::cout << x.phoneNumber << std::endl;

    return 0;
}
