#ifndef XYZFULLTIMEEMPLOYEE_H
#define XYZFULLTIMEEMPLOYEE_H

#include "XyzEmployee.H"
#include "EmployeeDetailBuilder.H"
#include <string>

class XyzFullTimeEmployee : public XyzEmployee
{
private:
    int mLeavesAvailed;

public:
    XyzFullTimeEmployee();
    XyzFullTimeEmployee(const std::string& idParm, const std::string& nameParm, const std::string& genderParm,
                        xyz::EmployeeStatus statusParm, const std::string& dobParm, const std::string& dojParm,
                        int leavesParm);
    ~XyzFullTimeEmployee();

    int getLeavesAvailed() const;
    void addLeaves(int leavesParm);
    void setLeaves(int leavesParm);

    std::string getDetails() const override;
};

#endif // XYZFULLTIMEEMPLOYEE_H
