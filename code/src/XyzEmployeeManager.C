#include "XyzEmployeeManager.H"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iomanip>

XyzEmployeeManager::XyzEmployeeManager() : mNextIdCounter(1) {}

XyzEmployeeManager::~XyzEmployeeManager()
{
    while (!mActiveInactiveDeque.isEmpty())
    {
        XyzEmployee* sEmp = mActiveInactiveDeque.getFront();
        mActiveInactiveDeque.popFront();
        delete sEmp;
    }
    while (!mResignedDeque.isEmpty())
    {
        XyzEmployee* sEmp = mResignedDeque.getFront();
        mResignedDeque.popFront();
        delete sEmp;
    }
}

std::string XyzEmployeeManager::pGenerateRandomId(xyz::EmployeeType typeParm)
{
    int sNum = mNextIdCounter++;
    std::ostringstream sOss;
    sOss << sNum;
    std::string sNumStr = sOss.str();
    while ((int)sNumStr.size() < 4)
    {
        sNumStr = "0" + sNumStr;
    }
    std::string sId = "XYZ" + sNumStr;
    sId += (typeParm == xyz::FullTime ? "F" : (typeParm == xyz::Contractor ? "C" : "I"));
    return sId;
}

int XyzEmployeeManager::pFindIndexById(const std::string& idParm) const
{
    int sSize = mActiveInactiveDeque.getSize();
    for (int sIdx = 0; sIdx < sSize; ++sIdx)
    {
        XyzEmployee* sEmp = mActiveInactiveDeque[sIdx];
        if (sEmp && sEmp->getId() == idParm)
        {
            return sIdx;
        }
    }
    return -1;
}

// ---------- Date helpers ----------
bool XyzEmployeeManager::pParseDate(const std::string& ymdParm, int& yearParm, int& monthParm, int& dayParm)
{
    if (ymdParm.size() < 10)
    {
        return false;
    }
    yearParm = (ymdParm[0]-'0')*1000 + (ymdParm[1]-'0')*100 + (ymdParm[2]-'0')*10 + (ymdParm[3]-'0');
    monthParm = (ymdParm[5]-'0')*10 + (ymdParm[6]-'0');
    dayParm = (ymdParm[8]-'0')*10 + (ymdParm[9]-'0');
    return true;
}
bool XyzEmployeeManager::pIsLeapYear(int yearParm)
{
    return ((yearParm % 4 == 0 && yearParm % 100 != 0) || (yearParm % 400 == 0));
}
int XyzEmployeeManager::pGetDaysInMonth(int yearParm, int monthParm)
{
    static const int sDaysPerMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (monthParm == 2)
    {
        return pIsLeapYear(yearParm) ? 29 : 28;
    }
    return sDaysPerMonth[monthParm - 1];
}
std::string XyzEmployeeManager::pFormatDate(int yearParm, int monthParm, int dayParm)
{
    std::ostringstream sStream;
    sStream << std::setfill('0')
            << std::setw(4) << yearParm << "-"
            << std::setw(2) << monthParm << "-"
            << std::setw(2) << dayParm;
    return sStream.str();
}

std::string XyzEmployeeManager::pAddMonthsToDate(const std::string& ymdParm, int monthsParm)
{
    int sYear, sMonth, sDay;
    if (!pParseDate(ymdParm, sYear, sMonth, sDay))
    {
        return "NA";
    }
    int sTotalMonths = sMonth - 1 + monthsParm;
    int sNewYear  = sYear + sTotalMonths / 12;
    int sNewMonth = (sTotalMonths % 12 + 12) % 12 + 1;

    if (sTotalMonths < 0 && (sTotalMonths % 12))
    {
        --sNewYear;
    }
    int sMaxDay = pGetDaysInMonth(sNewYear, sNewMonth);
    if (sDay > sMaxDay)
    {
        sDay = sMaxDay;
    }
    return pFormatDate(sNewYear, sNewMonth, sDay);
}
std::string XyzEmployeeManager::pAddYearsToDate(const std::string& ymdParm, int yearsParm)
{
    int sYear, sMonth, sDay;
    if (!pParseDate(ymdParm, sYear, sMonth, sDay))
    {
        return "NA";
    }
    int sNewYear = sYear + yearsParm;
    int sMaxDay = pGetDaysInMonth(sNewYear, sMonth);

    if (sDay > sMaxDay)
    {
        sDay = sMaxDay;
    }
    return pFormatDate(sNewYear, sMonth, sDay);
}
std::string XyzEmployeeManager::pGetCurrentDate()
{
    std::time_t sNow = std::time(nullptr);
    std::tm* sLt = std::localtime(&sNow);
    return pFormatDate(sLt->tm_year + 1900, sLt->tm_mon + 1, sLt->tm_mday);
}
std::string XyzEmployeeManager::pComputeDolFromDoj(const std::string& dojParm, xyz::EmployeeType typeParm)
{
    if (typeParm == xyz::Contractor)
    {
        return pAddYearsToDate(dojParm, 1);
    }
    if (typeParm == xyz::Intern)
    {
        return pAddMonthsToDate(dojParm, 6);
    }
    return "NA";
}

void XyzEmployeeManager::addFullTime(const std::string& nameParm,
                                     const std::string& genderParm,
                                     const std::string& dobParm,
                                     const std::string& dojParm,
                                     int leavesAvailedParm,
                                     int leavesAppliedParm,
                                     const std::string& idParm)
{
    std::string sId = (idParm.empty()) ? pGenerateRandomId(xyz::FullTime) : idParm;
    XyzEmployee* sEmp = new XyzFullTimeEmployee(
        sId,
        nameParm,
        genderParm,
        xyz::Active,
        dobParm,
        dojParm,
        leavesAvailedParm,
        leavesAppliedParm
    );
    sEmp->setDol("NA");
    mActiveInactiveDeque.pushBack(sEmp);
    std::cout << "Added FullTime with ID: " << sId << std::endl;
}


void XyzEmployeeManager::addContractor(const std::string& nameParm,
                                       const std::string& genderParm,
                                       const std::string& dobParm,
                                       const std::string& dojParm,
                                       xyz::ContractorAgency agencyParm,
                                       const std::string& idParm)
{
    std::string sId = (idParm.empty()) ? pGenerateRandomId(xyz::Contractor) : idParm;
    XyzEmployee* sEmp = new XyzContractorEmployee(
        sId,
        nameParm,
        genderParm,
        xyz::Active,
        dobParm,
        dojParm,
        agencyParm
    );
    sEmp->setDol(pComputeDolFromDoj(dojParm, xyz::Contractor));
    mActiveInactiveDeque.pushBack(sEmp);
    std::cout << "Added Contractor with ID: " << sId << std::endl;
}

void XyzEmployeeManager::addIntern(const std::string& nameParm,
                                   const std::string& genderParm,
                                   const std::string& dobParm,
                                   const std::string& dojParm,
                                   xyz::InternCollege collegeParm,
                                   xyz::InternBranch branchParm,
                                   const std::string& idParm)
{
    std::string sId = (idParm.empty()) ? pGenerateRandomId(xyz::Intern) : idParm;
    XyzEmployee* sEmp = new XyzInternEmployee(
        sId,
        nameParm,
        genderParm,
        xyz::Active,
        dobParm,
        dojParm,
        collegeParm,
        branchParm
    );
    sEmp->setDol(pComputeDolFromDoj(dojParm, xyz::Intern));
    mActiveInactiveDeque.pushBack(sEmp);
    std::cout << "Added Intern with ID: " << sId << std::endl;
}

std::string XyzEmployeeManager::pGenerateRandomName(const std::string& genderParm)
{
    int sFirstIdx = std::rand() % xyz::EmployeeFirstNameCount;
    int sLastIdx  = std::rand() % xyz::EmployeeLastNameCount;
    std::string sFirst = xyz::sEmpFirstNames[sFirstIdx];
    std::string sLast  = xyz::sEmpLastNames[sLastIdx];
    return sFirst + " " + sLast;
}

void XyzEmployeeManager::addRandomEmployee(const std::string& idParm)
{
    int sTypeInt = std::rand() % xyz::EmployeeTypeCount;
    xyz::EmployeeType sTypeEnum = xyz::EmployeeType(sTypeInt);
    std::string sId = (idParm.empty()) ? pGenerateRandomId(sTypeEnum) : idParm;

    std::string sGender = (std::rand() % 2 == 0) ? "M" : "F";
    std::string sName = pGenerateRandomName(sGender);

    // DOB + DOJ generation
    int sYear  = xyz::MinBirthYear + (std::rand() % (xyz::MaxBirthYear - xyz::MinBirthYear + 1));
    int sMonth = xyz::MinMonth + (std::rand() % (xyz::MaxMonth - xyz::MinMonth + 1));
    int sDay   = xyz::MinDay + (std::rand() % (xyz::MaxDay - xyz::MinDay + 1));
    std::string sDob = pFormatDate(sYear, sMonth, sDay);

    int sJoinYear  = sYear + xyz::MinWorkAge + (std::rand() % (xyz::MaxWorkAge - xyz::MinWorkAge + 1));
    int sJoinMonth = xyz::MinMonth + (std::rand() % (xyz::MaxMonth - xyz::MinMonth + 1));
    int sJoinDay   = xyz::MinDay + (std::rand() % (xyz::MaxDay - xyz::MinDay + 1));
    std::string sDoj = pFormatDate(sJoinYear, sJoinMonth, sJoinDay);

    std::string sToday = pGetCurrentDate();
    if (sDoj > sToday)
    {
        sDoj = sToday;
    }

    std::string sDol = pComputeDolFromDoj(sDoj, sTypeEnum);
    xyz::EmployeeStatus sStatus = xyz::Active;

    if (sDol != "NA" && sToday > sDol)
    {
        sStatus = xyz::Inactive;
    }

    // Create based on type
    if (sTypeEnum == xyz::FullTime)
    {
        int sLeavesAvailed = xyz::MinLeaves + (std::rand() % (xyz::MaxLeaves - xyz::MinLeaves + 1));
        int sLeavesApplied = xyz::MaxLeaves - sLeavesAvailed;
        XyzEmployee* sFullTimeEmp = new XyzFullTimeEmployee(sId, sName, sGender, sStatus, sDob, sDoj, sLeavesAvailed, sLeavesApplied);
        sFullTimeEmp->setDol("NA");
        mActiveInactiveDeque.pushBack(sFullTimeEmp);
    }
    else if (sTypeEnum == xyz::Contractor)
    {
        int sAgIdx = std::rand() % xyz::ContractorAgencyCount;
        XyzEmployee* sContractEmp = new XyzContractorEmployee(sId, sName, sGender, sStatus, sDob, sDoj, (xyz::ContractorAgency)sAgIdx);
        sContractEmp->setDol(sDol);
        mActiveInactiveDeque.pushBack(sContractEmp);
    }
    else
    {
        int sColIdx = std::rand() % xyz::InternCollegeCount;
        int sBrIdx  = std::rand() % xyz::InternBranchCount;
        XyzEmployee* sInternEmp = new XyzInternEmployee(sId, sName, sGender, sStatus, sDob, sDoj, (xyz::InternCollege)sColIdx, (xyz::InternBranch)sBrIdx);
        sInternEmp->setDol(sDol);
        mActiveInactiveDeque.pushBack(sInternEmp);
    }

    std::string sTypeStr = (sTypeEnum == xyz::FullTime ? "FullTime" : (sTypeEnum == xyz::Contractor ? "Contractor" : "Intern"));
    std::cout << "Added Random Employee → " << sName << " | ID: " << sId
              << " | Gender: " << sGender << " | Type: " << sTypeStr
              << " | DOB: " << sDob << " | DOJ: " << sDoj
              << " | DOL: " << sDol << " | Status: "
              << (sStatus == xyz::Active ? "Active" : "Inactive") << std::endl;
}

bool XyzEmployeeManager::removeEmployeeById(const std::string& idParm)
{
    int sIdx = pFindIndexById(idParm);
    if (sIdx < 0)
    {
        return false;
    }
    XyzEmployee* sEmp = mActiveInactiveDeque[sIdx];
    if (!sEmp)
    {
         return false;
    }
    sEmp->setStatus(xyz::Resigned);

    // Capture type-specific info when moving to resigned
    XyzEmployee* sResigned = nullptr;

    if (sEmp->getType() == xyz::FullTime)
    {
        XyzFullTimeEmployee* sFullTimeEmp = (XyzFullTimeEmployee*)sEmp;
        sResigned = new XyzFullTimeEmployee(sFullTimeEmp->getId(),
                                            sFullTimeEmp->getName(),
                                            sFullTimeEmp->getGender(),
                                            xyz::Resigned,
                                            sFullTimeEmp->getDob(),
                                            sFullTimeEmp->getDoj(),
                                            sFullTimeEmp->getLeavesAvailed());
        sResigned->setDol("NA");
    }
    else if (sEmp->getType() == xyz::Contractor)
    {
        XyzContractorEmployee* sContrEmp = (XyzContractorEmployee*)sEmp;
        sResigned = new XyzContractorEmployee(sContrEmp->getId(),
                                              sContrEmp->getName(),
                                              sContrEmp->getGender(),
                                              xyz::Resigned,
                                              sContrEmp->getDob(),
                                              sContrEmp->getDoj(),
                                              sContrEmp->getAgency());
        sResigned->setDol(pComputeDolFromDoj(sContrEmp->getDoj(), xyz::Contractor));
    }
    else
    {
        XyzInternEmployee* sInternEmp = (XyzInternEmployee*)sEmp;
        sResigned = new XyzInternEmployee(sInternEmp->getId(),
                                          sInternEmp->getName(),
                                          sInternEmp->getGender(),
                                          xyz::Resigned,
                                          sInternEmp->getDob(),
                                          sInternEmp->getDoj(),
                                          sInternEmp->getCollege(),
                                          sInternEmp->getBranch());
        sResigned->setDol(pComputeDolFromDoj(sInternEmp->getDoj(), xyz::Intern));
    }

    mResignedDeque.pushBack(sResigned);
    mActiveInactiveDeque.removeAtMiddle(sIdx);
    delete sEmp;

    std::cout << "Employee " << idParm << " marked as Resigned and moved to Resigned list.\n";
    return true;
}

void XyzEmployeeManager::addLeavesToFullTime(int nParm)
{
    int sSize = mActiveInactiveDeque.getSize();
    if(nParm <= 10)
    {
        for (int sIdx = 0; sIdx < sSize; ++sIdx)
        {
            XyzEmployee* sEmp = mActiveInactiveDeque[sIdx];
            if (sEmp && sEmp->getType() == xyz::FullTime)
            {
                XyzFullTimeEmployee* sF = (XyzFullTimeEmployee*)sEmp;
                sF->addLeaves(nParm);
            }
        }
        std::cout << "Added " << nParm << " leaves to all full-time employees." << std::endl;
    }
    else
    {
        std::cout << "Enter the Valid Number of Leaves." << std::endl;
    }
}

void XyzEmployeeManager::convertInternToFullTime(const std::string& idParm)
{
    int sIdx = pFindIndexById(idParm);
    if (sIdx < 0)
    {
        std::cout << "Intern not found.\n";
        return;
    }

    XyzEmployee* sEmp = mActiveInactiveDeque[sIdx];
    if (!sEmp || sEmp->getType() != xyz::Intern)
    {
        std::cout << "Employee is not an intern.\n";
        return;
    }

    std::string sDoj = sEmp->getDoj();
    // compute months between sDoj and today
    std::string sToday = pGetCurrentDate();

    int dY, dM, dD;
    pParseDate(sDoj, dY, dM, dD);
    int tY, tM, tD;
    pParseDate(sToday, tY, tM, tD);

    int sMonthsDiff = (tY - dY) * 12 + (tM - dM);
    if (tD < dD)
    {
        sMonthsDiff -= 1;
    }

    if (sMonthsDiff < 6)
    {
        std::cout << "Intern " << sEmp->getName() << " (ID: " << sEmp->getId()
                  << ") has not completed 6 months since DOJ (" << sDoj << "). Not eligible.\n";
        return;
    }

    std::string sName = sEmp->getName();
    std::string sGender = sEmp->getGender();
    std::string sDob = sEmp->getDob();
    std::string sNewId = pGenerateRandomId(xyz::FullTime);

    XyzEmployee* sNew = new XyzFullTimeEmployee(sNewId, sName, sGender, xyz::Active, sDob, sDoj, 0);
    sNew->setDol("NA");

    mActiveInactiveDeque.removeAtMiddle(sIdx);
    delete sEmp;
    mActiveInactiveDeque.pushBack(sNew);

    std::cout << "Converted Intern to FullTime. New ID: " << sNewId << std::endl;
}

std::string truncate(const std::string& str, size_t width)
{
    if (str.length() <= width)
        return str;
    else
        return str.substr(0, width - 3) + "...";
}

void XyzEmployeeManager::print(const EmployeeFilter& filterParm) const
{
    // Calculate the dynamic NameWidth
    int dynamicNameWidth = xyz::NameWidth;
    for (int sIdx = 0; sIdx < mActiveInactiveDeque.getSize(); ++sIdx)
    {
        const XyzEmployee* sEmp = mActiveInactiveDeque[sIdx];
        if (sEmp && (int)sEmp->getName().size() > dynamicNameWidth)
        {
            dynamicNameWidth = sEmp->getName().size();
        }
    }

    for (int sIdx = 0; sIdx < mResignedDeque.getSize(); ++sIdx)
    {
        const XyzEmployee* sEmp = mResignedDeque[sIdx];
        if (sEmp && (int)sEmp->getName().size() > dynamicNameWidth)
        {
            dynamicNameWidth = sEmp->getName().size();
        }
    }
    std::cout <<"width of the name is :" << dynamicNameWidth << std::endl;
    // Print the table header with adjusted width
    printHeader(dynamicNameWidth);

    for (int sIdx = 0; sIdx < mActiveInactiveDeque.getSize(); ++sIdx)
    {
        XyzEmployee* sEmp = mActiveInactiveDeque[sIdx];
        if (!sEmp)
        {
            continue;
        }
        if (filterParm.mEnableType && sEmp->getType() != filterParm.mType)
        {
            continue;
        }
        if (filterParm.mEnableGender && sEmp->getGender() != filterParm.mGender)
        {
            continue;
        }
        if (filterParm.mEnableStatus && sEmp->getStatus() != filterParm.mStatus)
        {
            continue;
        }
        if (filterParm.mEnableId && sEmp->getId() != filterParm.mId)
        {
            continue;
        }
        if (filterParm.mEnableNameSearch && sEmp->getName().find(filterParm.mNameSearch) == std::string::npos)
        {
            continue;
        }
        printRow(sEmp, dynamicNameWidth);
    }

    for (int sIdx = 0; sIdx < mResignedDeque.getSize(); ++sIdx)
    {
        XyzEmployee* sEmp = mResignedDeque[sIdx];
        if (!sEmp)
        {
            continue;
        }
        if (filterParm.mEnableType && sEmp->getType() != filterParm.mType)
        {
            continue;
        }
        if (filterParm.mEnableGender && sEmp->getGender() != filterParm.mGender)
        {
            continue;
        }
        if (filterParm.mEnableStatus && sEmp->getStatus() != filterParm.mStatus)
        {
            continue;
        }
        if (filterParm.mEnableId && sEmp->getId() != filterParm.mId)
        {
            continue;
        }
        if (filterParm.mEnableNameSearch && sEmp->getName().find(filterParm.mNameSearch) == std::string::npos)
        {
            continue;
        }
        printRow(sEmp, dynamicNameWidth);
    }
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

//---------- Printing helpers ----------
void XyzEmployeeManager::printHeader(int nameWidthParm) const
{
    using namespace xyz;
    std::cout << std::left;
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "| " << std::setw(nameWidthParm)      << "Name"
              << "| " << std::setw(IdWidth)            << "ID"
              << "| " << std::setw(GenderWidth)        << "Gender"
              << "| " << std::setw(DobWidth)           << "DOB"
              << "| " << std::setw(DojWidth)           << "DOJ"
              << "| " << std::setw(DolWidth)           << "DOL"
              << "| " << std::setw(TypeWidth)          << "Type"
              << "| " << std::setw(StatusWidth)        << "Status"
              << "| " << std::setw(CollegeWidth)       << "College"
              << "| " << std::setw(BranchWidth)        << "Branch"
              << "| " << std::setw(CurrLeavesWidth)    << "Leaves Availed"
              << "| " << std::setw(LeavesAppliedWidth) << "Leaves Applied"
              << "| " << std::setw(AgencyWidth)        << "Agency"
              << "|\n";
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void XyzEmployeeManager::printRow(const XyzEmployee* sEmp, int nameWidthParm) const
{
    using namespace xyz;
    std::cout << std::left;

    std::string sTypeStr   = (sEmp->getType() == FullTime ? "FullTime" :
                             (sEmp->getType() == Contractor ? "Contractor" : "Intern"));
    std::string sStatusStr = (sEmp->getStatus() == Active ? "Active" :
                             (sEmp->getStatus() == Inactive ? "Inactive" : "Resigned"));

    // Default values for all fields
    std::string sCollege = "NA";
    std::string sBranch  = "NA";
    std::string sAgency  = "NA";
    std::string sLeavesCurr = "NA";
    std::string sLeavesApplied = "NA";

    if (sEmp->getType() == xyz::FullTime)
    {
        const XyzFullTimeEmployee* sF = static_cast<const XyzFullTimeEmployee*>(sEmp);
        std::ostringstream sCurr, sApplied;
        sCurr << sF->getLeavesAvailed();
        sApplied  << sF->getLeavesApplied();
        sLeavesCurr    = sCurr.str();
        sLeavesApplied = sApplied.str();
    }

    else if (sEmp->getType() == Contractor)
    {
        const XyzContractorEmployee* sC = static_cast<const XyzContractorEmployee*>(sEmp);
        xyz::ContractorAgency sAg = sC->getAgency();
        sAgency = (sAg == Avengers ? "Avengers" :
                  (sAg == JusticeLeague ? "JusticeLeague" : "XMen"));
    }
    else if (sEmp->getType() == Intern)
    {
        const XyzInternEmployee* sI = static_cast<const XyzInternEmployee*>(sEmp);
        sCollege = (sI->getCollege() == IitDelhi ? "IIT Delhi" :
                    sI->getCollege() == IitMumbai ? "IIT Mumbai" :
                    sI->getCollege() == IitKanpur ? "IIT Kanpur" :
                    sI->getCollege() == IitHyderabad ? "IIT Hyderabad" :
                    sI->getCollege() == NitWarangal ? "NIT Warangal" :
                    sI->getCollege() == NitTiruchi ? "NIT Tiruchi" : "IIIT Hyderabad");
        sBranch = (sI->getBranch() == Cse ? "CSE" :
                  (sI->getBranch() == Csit ? "CSIT" : "ECE"));
    }

    // Print the row in a uniform format
    std::cout << "| " << std::setw(nameWidthParm)      << sEmp->getName()
              << "| " << std::setw(IdWidth)            << sEmp->getId()
              << "| " << std::setw(GenderWidth)        << sEmp->getGender()
              << "| " << std::setw(DobWidth)           << sEmp->getDob()
              << "| " << std::setw(DojWidth)           << sEmp->getDoj()
              << "| " << std::setw(DolWidth)           << sEmp->getDol()
              << "| " << std::setw(TypeWidth)          << sTypeStr
              << "| " << std::setw(StatusWidth)        << sStatusStr
              << "| " << std::setw(CollegeWidth)       << sCollege
              << "| " << std::setw(BranchWidth)        << sBranch
              << "| " << std::setw(CurrLeavesWidth)    << sLeavesCurr
              << "| " << std::setw(LeavesAppliedWidth) << sLeavesApplied
              << "| " << std::setw(AgencyWidth)        << sAgency
              << "|\n";
}