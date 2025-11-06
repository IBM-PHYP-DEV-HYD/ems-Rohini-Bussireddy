#ifndef XYZFULLTIMEEMPLOYEE_H
#define XYZFULLTIMEEMPLOYEE_H

#include "XyzEmployee.H"
#include "EmployeeDetailBuilder.H"
#include <string>

class XyzFullTimeEmployee : public XyzEmployee
{
private:
    int mLeavesAvailed;
    int mLeavesApplied;

public:
    XyzFullTimeEmployee();

     XyzFullTimeEmployee(const std::string& idParm,
                        const std::string& nameParm,
                        const std::string& genderParm,
                        xyz::EmployeeStatus statusParm,
                        const std::string& dobParm,
                        const std::string& dojParm,
                        int leavesAvailedParm,
                        int leavesAppliedParm = 0);

    ~XyzFullTimeEmployee();

    int getLeavesAvailed() const;
    int getLeavesApplied() const;

    void addLeaves(int leavesParm);
    void applyLeaves(int leavesParm);

    void setLeavesAvailed(int leavesParm);
    void setLeavesApplied(int leavesParm);

    std::string getDetails() const override;
};

#endif // XYZFULLTIMEEMPLOYEE_H
