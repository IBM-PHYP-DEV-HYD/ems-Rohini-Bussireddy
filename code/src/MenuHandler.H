#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include "XyzEmployeeManager.H"
#include "Utils.H"
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

class MenuHandler
{
private:
    XyzEmployeeManager mManager;

    void pPrintMainMenu() const;
    void pHandleAddEmployee();
    void pHandleRemoveEmployee();
    void pHandleGetEmpDetails();
    void pHandleOthers();

public:
    void start();
};

#endif // MENUHANDLER_H
