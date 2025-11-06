#ifndef EMPLOYEEDETAILBUILDER_H
#define EMPLOYEEDETAILBUILDER_H

#include <sstream>
#include <string>
#include "Utils.H"

class EmployeeDetailBuilder
{
private:
    std::ostringstream mStream;

public:
    EmployeeDetailBuilder& addId(const std::string& idParm);
    EmployeeDetailBuilder& addName(const std::string& nameParm);
    EmployeeDetailBuilder& addType(xyz::EmployeeType typeParm);
    EmployeeDetailBuilder& addStatus(xyz::EmployeeStatus statusParm);
    EmployeeDetailBuilder& addGender(const std::string& genderParm);
    EmployeeDetailBuilder& addDob(const std::string& dobParm);
    EmployeeDetailBuilder& addDoj(const std::string& dojParm);
    EmployeeDetailBuilder& addDol(const std::string& dolParm);
    EmployeeDetailBuilder& addLeaves(int leavesParm);
    EmployeeDetailBuilder& addLeavesApplied(int leavesParm);
    EmployeeDetailBuilder& addAgency(xyz::ContractorAgency agencyParm);
    EmployeeDetailBuilder& addCollege(xyz::InternCollege collegeParm);
    EmployeeDetailBuilder& addBranch(xyz::InternBranch branchParm);

    std::string build() const;
    void clear();
};

#endif // EMPLOYEEDETAILBUILDER_H
