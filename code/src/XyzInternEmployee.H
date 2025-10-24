#ifndef XYZINTERNEMPLOYEE_H
#define XYZINTERNEMPLOYEE_H

#include "XyzEmployee.H"
#include "EmployeeDetailBuilder.H"
#include <string>

class XyzInternEmployee : public XyzEmployee
{
private:
    xyz::InternCollege mCollege;
    xyz::InternBranch mBranch;

public:
    XyzInternEmployee();
    XyzInternEmployee(const std::string& idParm, const std::string& nameParm, const std::string& genderParm,
                      xyz::EmployeeStatus statusParm, const std::string& dobParm, const std::string& dojParm,
                      xyz::InternCollege collegeParm, xyz::InternBranch branchParm);
    ~XyzInternEmployee();

    xyz::InternCollege getCollege() const;
    xyz::InternBranch getBranch() const;
    void setCollege(xyz::InternCollege collegeParm);
    void setBranch(xyz::InternBranch branchParm);

    std::string getDetails() const override;
};

#endif // XYZINTERNEMPLOYEE_H
