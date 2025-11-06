#ifndef XYZEMPLOYEEMANAGER_H
#define XYZEMPLOYEEMANAGER_H

#include "EDLL.H"
#include "XyzFullTimeEmployee.H"
#include "XyzContractorEmployee.H"
#include "XyzInternEmployee.H"
#include "Utils.H"
#include <string>
#include <ctime>
#include <sstream>

struct EmployeeFilter
{
    bool mEnableType = false;
    xyz::EmployeeType mType = xyz::FullTime;

    bool mEnableGender = false;
    std::string mGender;

    bool mEnableStatus = false;
    xyz::EmployeeStatus mStatus = xyz::Active;

    bool mEnableId = false;
    std::string mId;

    bool mEnableNameSearch = false;
    std::string mNameSearch;
};

class XyzEmployeeManager
{
private:
    Edll<XyzEmployee*> mActiveInactiveDeque;
    Edll<XyzEmployee*> mResignedDeque;
    int mNextIdCounter;

    // Helpers (private)
    std::string pGenerateId(xyz::EmployeeType typeParm);
    int pFindIndexById(const std::string& idParm) const;

    // Date helpers
    static bool pParseYmd(const std::string& ymdParm, int& sY, int& sM, int& sD);
    static bool pIsLeap(int sY);
    static int  pDaysInMonth(int sY, int sM);
    static std::string pYmd(int sY, int sM, int sD);
    static std::string pAddMonths(const std::string& ymdParm, int monthsParm);
    static std::string pAddYears(const std::string& ymdParm, int yearsParm);
    static std::string pTodayYmd();

    // DOL rules
    static std::string pCalculateDol(const std::string& dojParm, xyz::EmployeeType typeParm);

    // Printing
    static std::string pPad(const std::string& s, int widthParm);
    void pPrintHeader() const;
    void pPrintRow(const XyzEmployee* sEmp) const;

    // Random helpers
    std::string pGenerateRandomName(const std::string& genderParm);

public:
    XyzEmployeeManager();
    ~XyzEmployeeManager();

void addFullTime(const std::string& nameParm,
                 const std::string& genderParm,
                 const std::string& dobParm,
                 const std::string& dojParm,
                 int leavesAvailedParm,
                 int leavesAppliedParm = 0,
                 const std::string& idParm = "");

    void addContractor(const std::string& nameParm, const std::string& genderParm, const std::string& dobParm,
                       const std::string& dojParm, xyz::ContractorAgency agencyParm, const std::string& idParm = "");
    void addIntern(const std::string& nameParm, const std::string& genderParm, const std::string& dobParm,
                   const std::string& dojParm, xyz::InternCollege collegeParm, xyz::InternBranch branchParm, const std::string& idParm = "");
    void addRandomEmployee(const std::string& idParm = "");

    bool removeEmployeeById(const std::string& idParm);
    void addLeavesToFullTime(int nParm);
    void convertInternToFullTime(const std::string& idParm);

    void print(const EmployeeFilter& filterParm) const;

    bool isEmpty() const
    {
        return mActiveInactiveDeque.isEmpty() && mResignedDeque.isEmpty();
    }
};

#endif // XYZEMPLOYEEMANAGER_H
