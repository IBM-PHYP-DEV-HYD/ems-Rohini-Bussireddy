#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace xyz
{
    enum MainMenuChoice
    {
        AddEmployee    = 1,
        RemoveEmployee = 2,
        GetEmpDetails  = 3,
        Others         = 4,
        Exit           = -1,
    };

    enum AddEmployeeChoice
    {
        RandomEmployee          = 1,
        SpecificEmployee        = 2,
        MultipleRandomEmployees = 3,
        BackMenu1               = -1,
    };

    enum DetailsMenuChoice
    {
        AllEmployees    = 1,
        ByType          = 2,
        ByGender        = 3,
        ByStatus        = 4,
        ByID            = 5,
        BackMenu2       = -1,
    };

    enum OtherMenuChoice
    {
        AddLeaves        = 1,
        ConvertIntern    = 2,
        SearchByID       = 3,
        SearchByName     = 4,
        BackMenu3        = -1,
    };

    enum EmployeeType
    {
        FullTime   = 0,
        Contractor = 1,
        Intern     = 2,
        EmployeeTypeCount // total number of employee types
    };

    enum EmployeeStatus
    {
        Active    = 0,
        Inactive  = 1,
        Resigned  = 2,
        EmployeeStatusCount // total number of statuses
    };

    enum ContractorAgency
    {
        Avengers       = 0,
        JusticeLeague  = 1,
        XMen           = 2,
        ContractorAgencyCount // total number of agencies
    };

    enum InternCollege
    {
        IitDelhi       = 0,
        IitMumbai      = 1,
        IitKanpur      = 2,
        IitHyderabad   = 3,
        NitWarangal    = 4,
        NitTiruchi     = 5,
        IiitHyderabad  = 6,
        InternCollegeCount // total number of colleges
    };

    enum InternBranch
    {
        Cse  = 0,
        Csit = 1,
        Ece  = 2,
        InternBranchCount // total number of branches
    };

    enum Leaves
    {
        MinLeaves    = 0,
        MaxLeaves    = 22,
        InvalidLeaves
    };

    enum EmployeeDateLimits
    {
        MinMonth = 1,
        MaxMonth = 12,
        MinDay   = 1,
        MaxDay   = 28
    };

    enum EmployeeAgeLimits
    {
        MinWorkAge   = 18,   // Minimum age at joining
        MaxWorkAge   = 60,   // Retirement age
        MinBirthYear = 1965,
        MaxBirthYear = 2005
    };

    // Print column sizes (single professional 9-column layout used everywhere)
    enum ColumnWidth
    {
        NameWidth          = 18,
        IdWidth            = 10,
        GenderWidth        = 8,
        DobWidth           = 12,
        DojWidth           = 12,
        DolWidth           = 12,
        TypeWidth          = 12,
        StatusWidth        = 10,
        CollegeWidth       = 16,
        BranchWidth        = 10,
        CurrLeavesWidth    = 16,
        LeavesAppliedWidth = 16,
        AgencyWidth        = 12
    };
    enum EmployeeFirstName
    {
        Aarav, Vivaan, Aditya, Rohan, Ishaan, Arjun, Karthik, Nikhil, Krishna, Ayan,
        Hriday, Manav, Dhruv, Reyansh, Siddharth,
        Ananya, Diya, Aditi, Kavya, Riya, Ira, Saanvi, Aarohi, Priya, Sneha,
        Tanya, Nisha, Meera, Aishwarya, Ishita,
        EmployeeFirstNameCount
    };

    enum EmployeeLastName
    {
        Sharma, Verma, Patel, Mehta, Reddy, Nair, Kumar, Singh, Das, Chopra,
        Gupta, Bhat, Joshi, Rao, Iyer, Menon, Naidu, Pillai, Agarwal, Mukherjee,
        EmployeeLastNameCount
    };

    inline const char* sEmpFirstNames[EmployeeFirstNameCount] = {
        "Aarav","Vivaan","Aditya","Rohan","Ishaan","Arjun","Karthik","Nikhil","Krishna","Ayan",
        "Hriday","Manav","Dhruv","Reyansh","Siddharth",
        "Ananya","Diya","Aditi","Kavya","Riya","Ira","Saanvi","Aarohi","Priya","Sneha",
        "Tanya","Nisha","Meera","Aishwarya","Ishita"
    };

    inline const char* sEmpLastNames[EmployeeLastNameCount] = {
        "Sharma","Verma","Patel","Mehta","Reddy","Nair","Kumar","Singh","Das","Chopra",
        "Gupta","Bhat","Joshi","Rao","Iyer","Menon","Naidu","Pillai","Agarwal","Mukherjee"
    };
}

#endif // UTILS_H
