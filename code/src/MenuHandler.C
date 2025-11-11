#include "MenuHandler.H"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

template <typename T>
T safeInput(const string& promptMsg)
{
    T value;
    bool isValid = false;
    while (!isValid)
    {
        cout << promptMsg;
        cin >> value;
        if (!cin.fail())
        {
            isValid = true;
        }
        else
        {
            cout << "Invalid input! Try again." << endl;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

bool allDigits(const string& strParm)
{
    bool isValid = true;
    if (strParm.empty())
    {
        isValid = false;
    }
    else
    {
        for (size_t sIdx = 0; sIdx < strParm.size(); ++sIdx)
        {
            if (strParm[sIdx] < '0' || strParm[sIdx] > '9')
            {
                isValid = false;
                break;
            }
        }
    }
    return isValid;
}

bool validateEmployeeID(const string& idParm)
{
    bool isValid = true;
    if (idParm.empty())
    {
        isValid = true;
    }
    else if (idParm.size() != 8)
    {
        isValid = false;
    }
    else if (idParm.rfind("XYZ", 0) != 0)
    {
        isValid = false;
    }
    else
    {
        for (int sIdx = 3; sIdx < 7; ++sIdx)
        {
            if (!isdigit(idParm[sIdx]))
            {
                isValid = false;
                break;
            }
        }
        if (isValid)
        {
            char sType = idParm[7];
            if (!(sType == 'F' || sType == 'C' || sType == 'I'))
            {
                isValid = false;
            }
        }
    }
    return isValid;
}

bool validateName(const string& nameParm)
{
    bool isValid = true;
    if (nameParm.empty())
    {
        isValid = false;
    }
    else
    {
        for (size_t sIdx = 0; sIdx < nameParm.size(); ++sIdx)
        {
            char sChar = nameParm[sIdx];
            if (!isalpha(sChar) && sChar != ' ')
            {
                isValid = false;
                break;
            }
        }
    }
    return isValid;
}

bool validateGender(const string& genderParm)
{
    bool isValid = true;
    if (genderParm.size() != 1)
    {
        isValid = false;
    }
    else
    {
        char c = genderParm[0];
        if (!(c == 'M' || c == 'm' || c == 'F' || c == 'f'))
        {
            isValid = false;
        }
    }
    return isValid;
}

bool validateDate(const string& dateParm)
{
    bool isValid = true;

    if (dateParm.size() != 10)
    {
        isValid = false;
    }
    else if (dateParm[4] != '-' || dateParm[7] != '-')
    {
        isValid = false;
    }
    else
    {
        string sYearStr = dateParm.substr(0, 4);
        string sMonthStr = dateParm.substr(5, 2);
        string sDayStr = dateParm.substr(8, 2);
        if (!allDigits(sYearStr) || !allDigits(sMonthStr) || !allDigits(sDayStr))
        {
            isValid = false;
        }
        else
        {
            int sYear = stoi(sYearStr);
            int sMonth = stoi(sMonthStr);
            int sDay = stoi(sDayStr);
            if (sYear < 1900 || sYear > 2099 ||
                sMonth < 1 || sMonth > 12 ||
                sDay < 1 || sDay > 31)
            {
                isValid = false;
            }
        }
    }
    return isValid;
}

void MenuHandler::pPrintMainMenu()
{
    cout << "--------------------------------------------------\n";
    cout << "|           Employee Management System           |\n";
    cout << "--------------------------------------------------\n";
    cout << "| 1. Add an Employee                             |\n";
    cout << "| 2. Add n Number Of Random Employees            |\n";
    cout << "| 3. Remove an Employee                          |\n";
    cout << "| 4. Get Employee Details                        |\n";
    cout << "| 5. Others                                      |\n";
    cout << "| (-1 to Exit)                                   |\n";
    cout << "--------------------------------------------------\n";
}

void MenuHandler::pHandleAddRandomEmployee()
{
    mManager.addRandomEmployee(false);
}

void MenuHandler::pHandleAddSpecificEmployee()
{
    string sId;
    int sType;
    bool validType = false;
    while (!validType)
    {
        sType = safeInput<int>("Type (0=FullTime,1=Contractor,2=Intern): ");
        if (sType >= xyz::FullTime && sType <= xyz::Intern)
        {
            validType = true;
        }
        else
        {
            cout << "Invalid type! Try Again" << endl;
        }
    }
    mManager.addRandomEmployee(true, sType);
}

void MenuHandler::pHandleAddMultipleRandomEmployees()
{
    int sCount = 0;
    bool validInput = false;
    while (!validInput)
    {
        sCount = safeInput<int>("No. of random employees to add : ");
        if (sCount > 0)
        {
            validInput = true;
        }
        else
        {
            std::cout << "Invalid input! Please enter a positive number.\n";
        }
    }
    for (int sIdx = 0; sIdx < sCount; sIdx++)
    {
        mManager.addRandomEmployee();
    }

    std::cout << sCount << " random employees added successfully.\n";
}


void MenuHandler::pHandleAddEmployee()
{
    cout << "---------------------------------------------------------\n";
    cout << "|                Add Employee Menu                      |\n";
    cout << "---------------------------------------------------------\n";
    cout << "| 1. Add an Employee at Random                          |\n";
    cout << "| 2. Add an Employee (F/C/I)                            |\n";
    cout << "| (-1 to Go Back)                                       |\n";
    cout << "---------------------------------------------------------\n";

    int sChoice = safeInput<int>("Your Choice: ");

    switch (sChoice)
    {
        case xyz::RandomEmployee:
            pHandleAddRandomEmployee();
            break;

        case xyz::SpecificEmployee:
            pHandleAddSpecificEmployee();
            break;

        case xyz::BackMenu1:
            cout << "Returning to main menu..." << endl;
            return;

        default:
            cout << "Invalid Input! Try Again." << endl;
            break;
    }
}


void MenuHandler::pHandleRemoveEmployee()
{
    if (mManager.isEmpty())
    {
        std::cout << "Deque is Empty! Please add employees first." << endl;
        return;
    }
    string sId;
    cout << "Employee ID: ";
    cin >> sId;
    if (!mManager.removeEmployeeById(sId))
    {
        cout << "Not found.\n";
    }
}

void MenuHandler::pHandleGetEmpDetails()
{
    if (mManager.isEmpty())
    {
        std::cout << "Deque is Empty! Please add employees first." << endl;
        return;
    }
    std::cout << "--------------------------------------------------\n";
    std::cout << "|             Employee Details Menu              |\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "| 1. All Employees Summary                       |\n";
    std::cout << "| 2. Employee Summary (F/C/I)                    |\n";
    std::cout << "| 3. Employee Summary (M/F)                      |\n";
    std::cout << "| 4. Employee Summary (A/I/R)                    |\n";
    std::cout << "| 5. Display Employee Details                    |\n";
    std::cout << "| (-1 to Go Back)                                |\n";
    std::cout << "--------------------------------------------------\n";

    int sChoice = safeInput<int>("Your Choice: ");
    EmployeeFilter sFilter;

    switch (sChoice)
    {
        case xyz::AllEmployees:
        {
            mManager.print(sFilter);
            break;
        }
        case xyz::ByType:
        {
            int sType = safeInput<int>("Type (0=FullTime,1=Contractor,2=Intern): ");

            if (sType >= 0 && sType < xyz::EmployeeTypeCount)
            {
                sFilter.mEnableType = true;
                sFilter.mType = (xyz::EmployeeType)sType;
                mManager.print(sFilter);
            }
            else
            {
                std::cout << "Invalid employee type!" <<endl;
            }
            break;
        }
        case xyz::ByGender:
        {
            std::string sGender;
            std::cout << "Gender (M/F): ";
            std::cin >> sGender;
            if (validateGender(sGender))
            {
                sFilter.mEnableGender = true;
                sFilter.mGender = sGender;
                mManager.print(sFilter);
            }
            else
            {
                std::cout << "Invalid gender!" << endl;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }

        case xyz::ByStatus:
        {
            int sStatus = safeInput<int>("Status (0=Active,1=Inactive,2=Resigned): ");

            if (sStatus >= 0 && sStatus < xyz::EmployeeStatusCount)
            {
                sFilter.mEnableStatus = true;
                sFilter.mStatus = (xyz::EmployeeStatus)sStatus;
                mManager.print(sFilter);
            }
            else
            {
                std::cout << "Invalid status!" << endl;
            }
            break;
        }
        case xyz::ByID:
        {
            std::string sId;
            std::cout << "Enter ID: ";
            std::cin >> sId;

            sFilter.mEnableId = true;
            sFilter.mId = sId;
            mManager.print(sFilter);

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        case xyz::BackMenu2:
        {
            std::cout << "Returning to previous menu..." << endl;
            break;
        }
        default:
        {
            std::cout << "Invalid choice! Try again." << endl;
            break;
        }
    }
}

void MenuHandler::pHandleOthers()
{
    cout << "---------------------------------------------------\n";
    cout << "|             Other Operations Menu               |\n";
    cout << "---------------------------------------------------\n";
    cout << "| 1. Add 'n' Leaves to Full-Time Employees        |\n";
    cout << "| 2. Convert an Intern to Full-Time Employee      |\n";
    cout << "| 3. Search Employee by ID                        |\n";
    cout << "| 4. Search Employee by Name                      |\n";
    cout << "| (-1 to Go Back)                                 |\n";
    cout << "---------------------------------------------------\n";

    int sChoice = safeInput<int>("Your Choice: ");

    switch (sChoice)
    {
        case xyz::AddLeaves:
        {
            int sLeaves = safeInput<int>("Leaves to add: ");
            mManager.addLeavesToFullTime(sLeaves);
            break;
        }

        case xyz::ConvertIntern:
        {
            std::string sId;
            cout << "Intern ID: ";
            cin >> sId;
            mManager.convertInternToFullTime(sId);
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }

        case xyz::SearchByID:
        {
            std::string sId;
            cout << "Enter ID: ";
            cin >> sId;

            EmployeeFilter sFilter;
            sFilter.mEnableId = true;
            sFilter.mId = sId;

            mManager.print(sFilter);
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }

        case xyz::SearchByName:
        {
            std::string sName;
            cout << "Enter name: ";
            cin.ignore();
            std::getline(cin, sName);

            EmployeeFilter sFilter;
            sFilter.mEnableNameSearch = true;
            sFilter.mNameSearch = sName;

            mManager.print(sFilter);
            break;
        }

        case xyz::BackMenu3:
        {
            cout << "Returning to main menu...\n";
            break;
        }

        default:
        {
            cout << "Invalid Input! Try again." << endl;
            break;
        }
    }
}

void MenuHandler::start()
{
    bool sRun = true;
    while (sRun)
    {
        pPrintMainMenu();
        int sChoice = safeInput<int>("Your Choice: ");
        switch (sChoice)
        {
            case xyz::AddEmployee:
                pHandleAddEmployee();
                break;

            case xyz::MultipleRandomEmployees:
                pHandleAddMultipleRandomEmployees();
                break;

            case xyz::RemoveEmployee:
                pHandleRemoveEmployee();
                break;

            case xyz::GetEmpDetails:
                pHandleGetEmpDetails();
                break;

            case xyz::Others:
                pHandleOthers();
                break;

            case xyz::Exit:
                sRun = false;
                break;

            default:
                std::cout << "Invalid choice! Try again." << endl;
                break;
        }
    }
}
