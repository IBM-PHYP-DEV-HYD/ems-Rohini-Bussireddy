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
    unsigned mEnableType       : 1;
    unsigned mEnableGender     : 1;
    unsigned mEnableStatus     : 1;
    unsigned mEnableId         : 1;
    unsigned mEnableNameSearch : 1;

    xyz::EmployeeType mType;
    std::string mGender;
    xyz::EmployeeStatus mStatus;
    std::string mId;
    std::string mNameSearch;

    EmployeeFilter()
        : mEnableType(0),
          mEnableGender(0),
          mEnableStatus(0),
          mEnableId(0),
          mEnableNameSearch(0) {}
};


class XyzEmployeeManager
{
private:
    Edll<XyzEmployee*> mActiveInactiveDeque;
    Edll<XyzEmployee*> mResignedDeque;
    int mNextIdCounter;

    std::string pGenerateId(xyz::EmployeeType typeParm);
    int pFindIndexById(const std::string& idParm) const;

    static bool pParseYmd(const std::string& ymdParm, int& sY, int& sM, int& sD);
    static bool pIsLeap(int sY);
    static int  pDaysInMonth(int sY, int sM);
    static std::string pYmd(int sY, int sM, int sD);
    static std::string pAddMonths(const std::string& ymdParm, int monthsParm);
    static std::string pAddYears(const std::string& ymdParm, int yearsParm);
    static std::string pTodayYmd();
    static std::string pCalculateDol(const std::string& dojParm, xyz::EmployeeType typeParm);

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

    void pPrintHeader() const;
    void pPrintRow(const XyzEmployee* sEmp) const;
    void print(const EmployeeFilter& filterParm) const;

    bool isEmpty() const
    {
        return mActiveInactiveDeque.isEmpty() && mResignedDeque.isEmpty();
    }
};

#endif // XYZEMPLOYEEMANAGER_H
