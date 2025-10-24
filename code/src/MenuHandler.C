#include "MenuHandler.H"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

// ====================== Validation Utils ======================

template <typename T>
T safeInput(const string& prompt)
{
    T value;
    bool isValid = false;
    while (!isValid)
    {
        cout << prompt;
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

bool validateGender(const string& g)
{
    bool isValid = true;

    if (g.size() != 1)
    {
        isValid = false;
    }
    else
    {
        char c = g[0];
        if (!(c == 'M' || c == 'm' || c == 'F' || c == 'f'))
        {
            isValid = false;
        }
    }

    return isValid;
}

bool validateDate(const string& d)
{
    bool isValid = true;

    if (d.size() != 10)
    {
        isValid = false;
    }
    else if (d[4] != '-' || d[7] != '-')
    {
        isValid = false;
    }
    else
    {
        string sYearStr = d.substr(0, 4);
        string sMonthStr = d.substr(5, 2);
        string sDayStr = d.substr(8, 2);

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

void MenuHandler::pPrintMainMenu() const
{
    cout << "--------------------------------------------------\n";
    cout << "|           Employee Management System           |\n";
    cout << "--------------------------------------------------\n";
    cout << "| 1. Add an Employee                             |\n";
    cout << "| 2. Remove an Employee                          |\n";
    cout << "| 3. Get Employee Details                        |\n";
    cout << "| 4. Others                                      |\n";
    cout << "| (-1 to Exit)                                   |\n";
    cout << "--------------------------------------------------\n";
}

void MenuHandler::pHandleAddEmployee()
{
    cout << "---------------------------------------------------------\n";
    cout << "|                Add Employee Menu                      |\n";
    cout << "---------------------------------------------------------\n";
    cout << "| 1. Add Random Employee                                |\n";
    cout << "| 2. Add Specific Employee (FullTime/Contractor/Intern) |\n";
    cout << "| 3. Add Multiple Random Employees                      |\n";
    cout << "| (-1 to Go Back)                                       |\n";
    cout << "---------------------------------------------------------\n";

    int sChoice = safeInput<int>("Your Choice: ");

    if (sChoice == xyz::RandomEmployee)
    {
        string sId;
        cout << "Enter ID (blank for auto): ";
        getline(cin, sId);
        while (!validateEmployeeID(sId))
        {
            cout << "Invalid ID format! Try again: ";
            getline(cin, sId);
        }
        mManager.addRandomEmployee(sId);
    }
    else if (sChoice == xyz::SpecificEmployee)
    {
        int sType;
        bool validType = false;
        while (!validType)
        {
            sType = safeInput<int>("Type (0=FullTime,1=Contractor,2=Intern): ");
            if (sType >= 0 && sType <= 2)
            {
                validType = true;
            }
            else
            {
                cout << "Invalid type!" << endl;
            }
        }

        string sId;
        bool validID = false;
        while (!validID)
        {
            cout << "Enter ID (blank for auto): ";
            getline(cin, sId);
            if (validateEmployeeID(sId))
            {
                validID = true;
            }
            else
            {
                cout << "Invalid ID format!" << endl;
            }
        }

        string sName;
        bool validName = false;
        while (!validName)
        {
            cout << "Enter Name: ";
            getline(cin, sName);
            if (validateName(sName))
            {
                validName = true;
            }
            else
            {
                cout << "Invalid name!" << endl;
            }
        }

        string sGender;
        bool validGender = false;
        while (!validGender)
        {
            cout << "Enter Gender (M/F): ";
            getline(cin, sGender);
            if (validateGender(sGender))
            {
                validGender = true;
            }
            else
            {
                cout << "Invalid gender!" << endl;
            }
        }

        string sDob;
        bool validDOB = false;
        while (!validDOB)
        {
            cout << "Enter DOB (YYYY-MM-DD): ";
            getline(cin, sDob);
            if (validateDate(sDob))
            {
                validDOB = true;
            }
            else
            {
                cout << "Invalid date format!" << endl;
            }
        }

        string sDoj;
        bool validDOJ = false;
        while (!validDOJ)
        {
            cout << "Enter DOJ (YYYY-MM-DD): ";
            getline(cin, sDoj);
            if (validateDate(sDoj))
            {
                validDOJ = true;
            }
            else
            {
                cout << "Invalid date format!" << endl;
            }
        }

        if (sType == xyz::FullTime)
        {
            int sLeaves = safeInput<int>("Leaves Used: ");
            mManager.addFullTime(sName, sGender, sDob, sDoj, sLeaves, sId);
        }
        else if (sType == xyz::Contractor)
        {
            int sAgency;
            bool validAgency = false;
            while (!validAgency)
            {
                sAgency = safeInput<int>("Agency (0-2): ");
                if (sAgency >= 0 && sAgency <= 2)
                {
                    validAgency = true;
                }
                else
                {
                    cout << "Invalid!\n";
                }
            }
            mManager.addContractor(sName, sGender, sDob, sDoj, (xyz::ContractorAgency)sAgency, sId);
        }
        else
        {
            int sCollege;
            int sBranch;
            bool validCollege = false;
            bool validBranch = false;

            while (!validCollege)
            {
                sCollege = safeInput<int>("College (0-6): ");
                if (sCollege >= 0 && sCollege <= 6)
                {
                    validCollege = true;
                }
                else
                {
                    cout << "Invalid!\n";
                }
            }

            while (!validBranch)
            {
                sBranch = safeInput<int>("Branch (0-2): ");
                if (sBranch >= 0 && sBranch <= 2)
                {
                    validBranch = true;
                }
                else
                {
                    cout << "Invalid!\n";
                }
            }

            mManager.addIntern(sName, sGender, sDob, sDoj, (xyz::InternCollege)sCollege, (xyz::InternBranch)sBranch, sId);
        }
    }
    else if (sChoice == xyz::MultipleRandomEmployees)
    {
        int count = safeInput<int>("How many? ");
        for (int sIdx = 0; sIdx < count; ++sIdx)
        {
            mManager.addRandomEmployee();
        }
    }
    else
    {
        // go back
    }
}

void MenuHandler::pHandleRemoveEmployee()
{
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
    cout << "--------------------------------------------------\n";
    cout << "|             Employee Details Menu              |\n";
    cout << "--------------------------------------------------\n";
    cout << "| 1. All Employees Summary                       |\n";
    cout << "| 2. By Type (FullTime/Contractor/Intern)        |\n";
    cout << "| 3. By Gender                                   |\n";
    cout << "| 4. By Status (Active/Inactive/Resigned)        |\n";
    cout << "| 5. By Employee ID                              |\n";
    cout << "| (-1 to Go Back)                                |\n";
    cout << "--------------------------------------------------\n";

    int sChoice = safeInput<int>("Your Choice: ");
    EmployeeFilter sFilter;

    if (sChoice == xyz::AllEmployees)
    {
        mManager.print(sFilter);
    }
    else if (sChoice == xyz::ByType)
    {
        int sType = safeInput<int>("Type (0-2): ");
        sFilter.mEnableType = true;
        sFilter.mType = (xyz::EmployeeType)sType;
        mManager.print(sFilter);
    }
    else if (sChoice == xyz::ByGender)
    {
        string sGender;
        cout << "Gender (M/F): ";
        cin >> sGender;

        if (validateGender(sGender))
        {
            sFilter.mEnableGender = true;
            sFilter.mGender = sGender;
            mManager.print(sFilter);
        }
        else
        {
            cout << "Invalid gender!\n";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else if (sChoice == xyz::ByStatus)
    {
        int sStatus = safeInput<int>("Status (0-2): ");
        sFilter.mEnableStatus = true;
        sFilter.mStatus = (xyz::EmployeeStatus)sStatus;
        mManager.print(sFilter);
    }
    else if (sChoice == xyz::ByID)
    {
        string sId;
        cout << "Enter ID: ";
        cin >> sId;
        sFilter.mEnableId = true;
        sFilter.mId = sId;
        mManager.print(sFilter);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {
        // back
    }
}

void MenuHandler::pHandleOthers()
{
    cout << "---------------------------------------------------\n";
    cout << "|             Other Operations Menu               |\n";
    cout << "---------------------------------------------------\n";
    cout << "| 1. Add 'n' Leaves to Full-Time Employees        |\n";
    cout << "| 2. Convert an Intern to Full-Time               |\n";
    cout << "| 3. Search Employee by ID                        |\n";
    cout << "| 4. Search Employee by Name                      |\n";
    cout << "| (-1 to Go Back)                                 |\n";
    cout << "---------------------------------------------------\n";

    int sChoice = safeInput<int>("Your Choice: ");

    if (sChoice == xyz::AddLeaves)
    {
        int sLeaves = safeInput<int>("Leaves to add: ");
        mManager.addLeavesToFullTime(sLeaves);
    }
    else if (sChoice == xyz::ConvertIntern)
    {
        string sId;
        cout << "Intern ID: ";
        cin >> sId;
        mManager.convertInternToFullTime(sId);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else if (sChoice == xyz::SearchByID)
    {
        string sId;
        cout << "Enter ID: ";
        cin >> sId;
        EmployeeFilter sFilter;
        sFilter.mEnableId = true;
        sFilter.mId = sId;
        mManager.print(sFilter);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else if (sChoice == xyz::SearchByName)
    {
        string sName;
        cout << "Enter name: ";
        cin >> sName;
        EmployeeFilter sFilter;
        sFilter.mEnableNameSearch = true;
        sFilter.mNameSearch = sName;
        mManager.print(sFilter);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {
        // back
    }
}

void MenuHandler::start()
{
    bool sRun = true;

    while (sRun)
    {
        pPrintMainMenu();
        int sChoice = safeInput<int>("Your Choice: ");

        if (sChoice == xyz::AddEmployee)
        {
            pHandleAddEmployee();
        }
        else if (sChoice == xyz::RemoveEmployee)
        {
            pHandleRemoveEmployee();
        }
        else if (sChoice == xyz::GetEmpDetails)
        {
            pHandleGetEmpDetails();
        }
        else if (sChoice == xyz::Others)
        {
            pHandleOthers();
        }
        else if (sChoice == xyz::Exit)
        {
            sRun = false;
        }
        else
        {
            cout << "Invalid!\n";
        }
    }
}
