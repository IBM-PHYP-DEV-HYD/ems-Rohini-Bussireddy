#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace xyz
{
    // Menu choices
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
        SpecificEmployee        = 2,        // (kept for completeness; demo uses random to avoid extra inputs)
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

    // Core types
    enum EmployeeType
    {
        FullTime   = 0,
        Contractor = 1,
        Intern     = 2,
    };

    enum EmployeeStatus
    {
        Active    = 0,
        Inactive  = 1,
        Resigned  = 2,
    };

    enum ContractorAgency
    {
        Avengers       = 0,
        JusticeLeague  = 1,
        XMen           = 2,
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
    };

    enum InternBranch
    {
        Cse  = 0,
        Csit = 1,
        Ece  = 2,
    };

    // Print column sizes (single professional 9-column layout used everywhere)
    enum ColumnWidth
    {
        NameWidth   = 20,
        IdWidth     = 10,
        TypeWidth   = 12,
        StatusWidth = 12,
        GenderWidth = 8,
        DobWidth    = 12,
        DojWidth    = 12,
        DolWidth    = 12,
        ExtraWidth  = 25
    };
}

#endif // UTILS_H
