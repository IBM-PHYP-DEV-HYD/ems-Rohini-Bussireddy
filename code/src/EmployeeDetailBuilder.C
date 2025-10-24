#include "EmployeeDetailBuilder.H"

EmployeeDetailBuilder& EmployeeDetailBuilder::addId(const std::string& idParm)
{
    mStream << "ID: " << idParm << " | ";
    return *this;
}
EmployeeDetailBuilder& EmployeeDetailBuilder::addName(const std::string& nameParm)
{
    mStream << "Name: " << nameParm << " | ";
    return *this;
}
EmployeeDetailBuilder& EmployeeDetailBuilder::addType(xyz::EmployeeType typeParm)
{
    std::string sTypeStr = (typeParm == xyz::FullTime ? "FullTime" :
                           (typeParm == xyz::Contractor ? "Contractor" : "Intern"));
    mStream << "Type: " << sTypeStr << " | ";
    return *this;
}
EmployeeDetailBuilder& EmployeeDetailBuilder::addStatus(xyz::EmployeeStatus statusParm)
{
    std::string sStatusStr = (statusParm == xyz::Active ? "Active" :
                             (statusParm == xyz::Inactive ? "Inactive" : "Resigned"));
    mStream << "Status: " << sStatusStr << " | ";
    return *this;
}
EmployeeDetailBuilder& EmployeeDetailBuilder::addGender(const std::string& genderParm)
{
    mStream << "Gender: " << genderParm << " | ";
    return *this;
}
EmployeeDetailBuilder& EmployeeDetailBuilder::addDob(const std::string& dobParm)
{
    mStream << "DOB: " << dobParm << " | ";
    return *this;
}
EmployeeDetailBuilder& EmployeeDetailBuilder::addDoj(const std::string& dojParm)
{
    mStream << "DOJ: " << dojParm << " | ";
    return *this;
}
EmployeeDetailBuilder& EmployeeDetailBuilder::addDol(const std::string& dolParm)
{
    mStream << "DOL: " << dolParm << " | ";
    return *this;
}
EmployeeDetailBuilder& EmployeeDetailBuilder::addLeaves(int leavesParm)
{
    mStream << "LeavesAvailed: " << leavesParm << " | ";
    return *this;
}
EmployeeDetailBuilder& EmployeeDetailBuilder::addAgency(xyz::ContractorAgency agencyParm)
{
    std::string sAgencyStr = (agencyParm == xyz::Avengers ? "Avengers" :
                             (agencyParm == xyz::JusticeLeague ? "JusticeLeague" : "XMen"));
    mStream << "Agency: " << sAgencyStr << " | ";
    return *this;
}
EmployeeDetailBuilder& EmployeeDetailBuilder::addCollege(xyz::InternCollege collegeParm)
{
    std::string sCollegeStr;
    switch (collegeParm)
    {
        case xyz::IitDelhi:
            sCollegeStr = "IIT Delhi";
            break;
        case xyz::IitMumbai:
            sCollegeStr = "IIT Mumbai";
            break;
        case xyz::IitKanpur:
            sCollegeStr = "IIT Kanpur";
            break;
        case xyz::IitHyderabad:
            sCollegeStr = "IIT Hyderabad";
            break;
        case xyz::NitWarangal:
            sCollegeStr = "NIT Warangal";
            break;
        case xyz::NitTiruchi:
            sCollegeStr = "NIT Tiruchi";
            break;
        case xyz::IiitHyderabad:
            sCollegeStr = "IIIT Hyderabad";
            break;
        default:
            sCollegeStr = "Unknown";
            break;
    }
    mStream << "College: " << sCollegeStr << " | ";
    return *this;
}
EmployeeDetailBuilder& EmployeeDetailBuilder::addBranch(xyz::InternBranch branchParm)
{
    std::string sBranchStr = (branchParm == xyz::Cse ? "CSE" : (branchParm == xyz::Csit ? "CSIT" : "ECE"));
    mStream << "Branch: " << sBranchStr << " | ";
    return *this;
}
std::string EmployeeDetailBuilder::build() const
{
    std::string sResult = mStream.str();
    const std::string sSuffix = " | ";
    if (!sResult.empty() && sResult.size() >= sSuffix.size())
    {
        if (sResult.substr(sResult.size() - sSuffix.size()) == sSuffix)
        {
            sResult.erase(sResult.size() - sSuffix.size());
        }
    }
    return sResult;
}
void EmployeeDetailBuilder::clear()
{
    mStream.str("");
    mStream.clear();
}
