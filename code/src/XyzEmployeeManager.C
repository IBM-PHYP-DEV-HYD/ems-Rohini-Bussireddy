#include "XyzEmployeeManager.H"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>

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

std::string XyzEmployeeManager::pGenerateId(xyz::EmployeeType typeParm)
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
    int sN = mActiveInactiveDeque.getSize();
    for (int sI = 0; sI < sN; ++sI)
    {
        XyzEmployee* sEmp = mActiveInactiveDeque[sI];
        if (sEmp && sEmp->getId() == idParm)
        {
            return sI;
        }
    }
    return -1;
}

// ---------- Date helpers ----------
bool XyzEmployeeManager::pParseYmd(const std::string& ymdParm, int& sY, int& sM, int& sD)
{
    if (ymdParm.size() < 10) return false;
    sY = (ymdParm[0]-'0')*1000 + (ymdParm[1]-'0')*100 + (ymdParm[2]-'0')*10 + (ymdParm[3]-'0');
    sM = (ymdParm[5]-'0')*10 + (ymdParm[6]-'0');
    sD = (ymdParm[8]-'0')*10 + (ymdParm[9]-'0');
    return true;
}
bool XyzEmployeeManager::pIsLeap(int sY)
{
    return ( (sY%4==0 && sY%100!=0) || (sY%400==0) );
}
int XyzEmployeeManager::pDaysInMonth(int sY, int sM)
{
    static const int sDm[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (sM==2)
    {
        return pIsLeap(sY) ? 29 : 28;
    }
    return sDm[sM-1];
}
std::string XyzEmployeeManager::pYmd(int sY, int sM, int sD)
{
    // zero pad with string logic
    std::string sYStr, sMStr, sDStr;
    {
        std::ostringstream sO; sO<<sY; sYStr=sO.str();
    }
    {
        sMStr = (sM<10? "0":""); std::ostringstream sO; sO<<sM; sMStr += sO.str();
    }
    {
        sDStr = (sD<10? "0":""); std::ostringstream sO; sO<<sD; sDStr += sO.str();
    }
    return sYStr + "-" + sMStr + "-" + sDStr;
}
std::string XyzEmployeeManager::pAddMonths(const std::string& ymdParm, int monthsParm)
{
    int sY, sM, sD; if (!pParseYmd(ymdParm, sY, sM, sD))
    {
        return "NA";
    }
    int sTot = sM - 1 + monthsParm;
    int sNY = sY + sTot/12;
    int sNM = (sTot%12 + 12)%12 + 1;
    if (sTot < 0 && (sTot % 12))
    {
        --sNY;   // safety for negatives (not used here)
    }
    int sMaxD = pDaysInMonth(sNY, sNM);
    if (sD > sMaxD) sD = sMaxD;
    {
        return pYmd(sNY, sNM, sD);
    }
}
std::string XyzEmployeeManager::pAddYears(const std::string& ymdParm, int yearsParm)
{
    int sY, sM, sD; if (!pParseYmd(ymdParm, sY, sM, sD))
    {
        return "NA";
    }
    int sNY = sY + yearsParm;
    int sMaxD = pDaysInMonth(sNY, sM);
    if (sD > sMaxD) sD = sMaxD;
    {
        return pYmd(sNY, sM, sD);
    }
}
std::string XyzEmployeeManager::pTodayYmd()
{
    std::time_t sNow = std::time(nullptr);
    std::tm* sLt = std::localtime(&sNow);
    int sY = sLt->tm_year + 1900;
    int sM = sLt->tm_mon + 1;
    int sD = sLt->tm_mday;
    return pYmd(sY, sM, sD);
}
std::string XyzEmployeeManager::pProjectedDol(const std::string& dojParm, xyz::EmployeeType typeParm)
{
    if (typeParm == xyz::Contractor)
    {
        return pAddYears(dojParm, 1);
    }
    if (typeParm == xyz::Intern)
    {
        return pAddMonths(dojParm, 6);
    }
    return "NA";
}

// ---------- Printing helpers ----------
std::string XyzEmployeeManager::pPad(const std::string& s, int widthParm)
{
    if ((int)s.size() >= widthParm) return s.substr(0, widthParm);
    return s + std::string(static_cast<size_t>(widthParm - static_cast<int>(s.size())), ' ');
}
void XyzEmployeeManager::pPrintHeader() const
{
    using namespace xyz;
    std::cout << "----------------------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "| " << pPad("Name", NameWidth)
              << "| " << pPad("ID", IdWidth)
              << "| " << pPad("Type", TypeWidth)
              << "| " << pPad("Status", StatusWidth)
              << "| " << pPad("Gender", GenderWidth)
              << "| " << pPad("DOB", DobWidth)
              << "| " << pPad("DOJ", DojWidth)
              << "| " << pPad("DOL", DolWidth)
              << "| " << pPad("Extra", ExtraWidth) << "|\n";
    std::cout << "----------------------------------------------------------------------------------------------------------------------------------------\n";
}
void XyzEmployeeManager::pPrintRow(const XyzEmployee* sEmp) const
{
    using namespace xyz;

    std::string sTypeStr  = (sEmp->getType() == FullTime ? "FullTime" :
                            (sEmp->getType() == Contractor ? "Contractor" : "Intern"));
    std::string sStatusStr = (sEmp->getStatus() == Active ? "Active" :
                             (sEmp->getStatus() == Inactive ? "Inactive" : "Resigned"));

    // Extra
    std::string sExtra = "NA";
    if (sEmp->getType() == FullTime)
    {
        const XyzFullTimeEmployee* sF = (const XyzFullTimeEmployee*)sEmp;
        std::ostringstream sO; sO << "Leaves: " << sF->getLeavesAvailed();
        sExtra = sO.str();
    }
    else if (sEmp->getType() == Contractor)
    {
        const XyzContractorEmployee* sC = (const XyzContractorEmployee*)sEmp;
        xyz::ContractorAgency sAg = sC->getAgency();
        sExtra = (sAg == Avengers ? "Avengers" : (sAg == JusticeLeague ? "JusticeLeague" : "XMen"));
    }
    else
    {
        const XyzInternEmployee* sI = (const XyzInternEmployee*)sEmp;
        std::string sCol = (sI->getCollege() == IitDelhi ? "IIT Delhi" :
                           sI->getCollege() == IitMumbai ? "IIT Mumbai" :
                           sI->getCollege() == IitKanpur ? "IIT Kanpur" :
                           sI->getCollege() == IitHyderabad ? "IIT Hyderabad" :
                           sI->getCollege() == NitWarangal ? "NIT Warangal" :
                           sI->getCollege() == NitTiruchi ? "NIT Tiruchi" : "IIIT Hyderabad");
        std::string sBr  = (sI->getBranch() == Cse ? "CSE" : (sI->getBranch() == Csit ? "CSIT" : "ECE"));
        sExtra = sCol + " (" + sBr + ")";
    }

    // Always 9 columns
    std::cout << "| " << pPad(sEmp->getName(), NameWidth)
              << "| " << pPad(sEmp->getId(), IdWidth)
              << "| " << pPad(sTypeStr, TypeWidth)
              << "| " << pPad(sStatusStr, StatusWidth)
              << "| " << pPad(sEmp->getGender(), GenderWidth)
              << "| " << pPad(sEmp->getDob(), DobWidth)
              << "| " << pPad(sEmp->getDoj(), DojWidth)
              << "| " << pPad(sEmp->getDol(), DolWidth)
              << "| " << pPad(sExtra, ExtraWidth) << "|\n";
}

// ---------- Add / Random ----------
void XyzEmployeeManager::addFullTime(const std::string& nameParm, const std::string& genderParm, const std::string& dobParm,
                                     const std::string& dojParm, int leavesParm, const std::string& idParm)
{
    std::string sId = (idParm.empty()) ? pGenerateId(xyz::FullTime) : idParm;
    XyzEmployee* sEmp = new XyzFullTimeEmployee(sId, nameParm, genderParm, xyz::Active, dobParm, dojParm, leavesParm);
    // DOL for FullTime remains NA
    sEmp->setDol("NA");
    mActiveInactiveDeque.pushBack(sEmp);
    std::cout << "Added FullTime with ID: " << sId << std::endl;
}

void XyzEmployeeManager::addContractor(const std::string& nameParm, const std::string& genderParm, const std::string& dobParm,
                                       const std::string& dojParm, xyz::ContractorAgency agencyParm, const std::string& idParm)
{
    std::string sId = (idParm.empty()) ? pGenerateId(xyz::Contractor) : idParm;
    XyzEmployee* sEmp = new XyzContractorEmployee(sId, nameParm, genderParm, xyz::Active, dobParm, dojParm, agencyParm);
    sEmp->setDol(pProjectedDol(dojParm, xyz::Contractor));
    mActiveInactiveDeque.pushBack(sEmp);
    std::cout << "Added Contractor with ID: " << sId << std::endl;
}

void XyzEmployeeManager::addIntern(const std::string& nameParm, const std::string& genderParm, const std::string& dobParm,
                                   const std::string& dojParm, xyz::InternCollege collegeParm, xyz::InternBranch branchParm, const std::string& idParm)
{
    std::string sId = (idParm.empty()) ? pGenerateId(xyz::Intern) : idParm;
    XyzEmployee* sEmp = new XyzInternEmployee(sId, nameParm, genderParm, xyz::Active, dobParm, dojParm, collegeParm, branchParm);
    sEmp->setDol(pProjectedDol(dojParm, xyz::Intern));
    mActiveInactiveDeque.pushBack(sEmp);
    std::cout << "Added Intern with ID: " << sId << std::endl;
}

std::string XyzEmployeeManager::pGenerateRandomName(const std::string& genderParm) const
{
    static const char* sMaleFirstNames[] = {
        "Aarav","Vivaan","Aditya","Rohan","Ishaan","Arjun","Karthik","Nikhil","Krishna","Ayan",
        "Hriday","Manav","Dhruv","Reyansh","Siddharth"
    };
    static const char* sFemaleFirstNames[] = {
        "Ananya","Diya","Aditi","Kavya","Riya","Ira","Saanvi","Aarohi","Priya","Sneha",
        "Tanya","Nisha","Meera","Aishwarya","Ishita"
    };
    static const char* sLastNames[] = {
        "Sharma","Verma","Patel","Mehta","Reddy","Nair","Kumar","Singh","Das","Chopra",
        "Gupta","Bhat","Joshi","Rao","Iyer","Menon","Naidu","Pillai","Agarwal","Mukherjee"
    };
    bool sIsMale = (genderParm=="M" || genderParm=="m");
    const char** sFirstList = sIsMale ? sMaleFirstNames : sFemaleFirstNames;
    int sFirstCount = 15;
    int sLastCount = 20;
    const std::string sFirst = sFirstList[std::rand() % sFirstCount];
    const std::string sLast  = sLastNames[std::rand() % sLastCount];
    return sFirst + " " + sLast;
}

void XyzEmployeeManager::addRandomEmployee(const std::string& idParm)
{
    int sTypeInt = std::rand() % 3;
    xyz::EmployeeType sTypeEnum = (sTypeInt == 0 ? xyz::FullTime : (sTypeInt == 1 ? xyz::Contractor : xyz::Intern));
    std::string sId = (idParm.empty()) ? pGenerateId(sTypeEnum) : idParm;

    std::string sGender = (std::rand() % 2 == 0) ? "M" : "F";
    std::string sName = pGenerateRandomName(sGender);

    int sYear = 1980 + (std::rand() % 25);
    int sMonth = 1 + (std::rand() % 12);
    int sDay = 1 + (std::rand() % 28);
    std::string sDob = pYmd(sYear, sMonth, sDay);

    int sJoinYear = sYear + 18 + (std::rand() % 30);
    int sJoinMonth = 1 + (std::rand() % 12);
    int sJoinDay = 1 + (std::rand() % 28);
    std::string sDoj = pYmd(sJoinYear, sJoinMonth, sJoinDay);

    if (sTypeEnum == xyz::FullTime)
    {
        int sLeaves = std::rand() % 25;
        XyzEmployee* sE = new XyzFullTimeEmployee(sId, sName, sGender, xyz::Active, sDob, sDoj, sLeaves);
        sE->setDol("NA");
        mActiveInactiveDeque.pushBack(sE);
    }
    else if (sTypeEnum == xyz::Contractor)
    {
        int sAgIdx = std::rand() % 3;
        XyzEmployee* sE = new XyzContractorEmployee(sId, sName, sGender, xyz::Active, sDob, sDoj, (xyz::ContractorAgency)sAgIdx);
        sE->setDol(pProjectedDol(sDoj, xyz::Contractor));
        mActiveInactiveDeque.pushBack(sE);
    }
    else
    {
        int sColIdx = std::rand() % 7;
        int sBrIdx  = std::rand() % 3;
        XyzEmployee* sE = new XyzInternEmployee(sId, sName, sGender, xyz::Active, sDob, sDoj, (xyz::InternCollege)sColIdx, (xyz::InternBranch)sBrIdx);
        sE->setDol(pProjectedDol(sDoj, xyz::Intern));
        mActiveInactiveDeque.pushBack(sE);
    }

    std::string sTypeStr = (sTypeEnum == xyz::FullTime ? "FullTime" : (sTypeEnum == xyz::Contractor ? "Contractor" : "Intern"));
    std::cout << "Added Random Employee → " << sName << " | ID: " << sId
              << " | Gender: " << sGender << " | Type: " << sTypeStr
              << " | DOB: " << sDob << " | DOJ: " << sDoj << std::endl;
}

bool XyzEmployeeManager::removeEmployeeById(const std::string& idParm)
{
    int sIdx = pFindIndexById(idParm);
    if (sIdx < 0) return false;

    XyzEmployee* sEmp = mActiveInactiveDeque[sIdx];
    if (!sEmp) return false;

    sEmp->setStatus(xyz::Resigned);

    // Capture type-specific info when moving to resigned
    XyzEmployee* sResigned = nullptr;

    if (sEmp->getType() == xyz::FullTime)
    {
        XyzFullTimeEmployee* sF = (XyzFullTimeEmployee*)sEmp;
        sResigned = new XyzFullTimeEmployee(sF->getId(), sF->getName(), sF->getGender(), xyz::Resigned, sF->getDob(), sF->getDoj(), sF->getLeavesAvailed());
        sResigned->setDol("NA");
    }
    else if (sEmp->getType() == xyz::Contractor)
    {
        XyzContractorEmployee* sC = (XyzContractorEmployee*)sEmp;
        sResigned = new XyzContractorEmployee(sC->getId(), sC->getName(), sC->getGender(), xyz::Resigned, sC->getDob(), sC->getDoj(), sC->getAgency());
        sResigned->setDol(pProjectedDol(sC->getDoj(), xyz::Contractor));
    }
    else
    {
        XyzInternEmployee* sI = (XyzInternEmployee*)sEmp;
        sResigned = new XyzInternEmployee(sI->getId(), sI->getName(), sI->getGender(), xyz::Resigned, sI->getDob(), sI->getDoj(), sI->getCollege(), sI->getBranch());
        sResigned->setDol(pProjectedDol(sI->getDoj(), xyz::Intern));
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
    std::string sToday = pTodayYmd();

    int dY, dM, dD; pParseYmd(sDoj, dY, dM, dD);
    int tY, tM, tD; pParseYmd(sToday, tY, tM, tD);

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
    std::string sNewId = pGenerateId(xyz::FullTime);

    XyzEmployee* sNew = new XyzFullTimeEmployee(sNewId, sName, sGender, xyz::Active, sDob, sDoj, 0);
    sNew->setDol("NA");

    mActiveInactiveDeque.removeAtMiddle(sIdx);
    delete sEmp;
    mActiveInactiveDeque.pushBack(sNew);

    std::cout << "Converted Intern to FullTime. New ID: " << sNewId << std::endl;
}


void XyzEmployeeManager::print(const EmployeeFilter& filterParm) const
{
    pPrintHeader();
    // Active/Inactive pool
    int sN = mActiveInactiveDeque.getSize();
    for (int sI = 0; sI < sN; ++sI)
    {
        XyzEmployee* sEmp = mActiveInactiveDeque[sI];
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

        pPrintRow(sEmp);
    }
    // Resigned pool
    int sR = mResignedDeque.getSize();
    for (int sIdx = 0; sIdx < sR; ++sIdx)
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

        pPrintRow(sEmp);
    }
    std::cout << "----------------------------------------------------------------------------------------------------------------------------------------\n";
}
