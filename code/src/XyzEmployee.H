#ifndef XYZEMPLOYEE_H
#define XYZEMPLOYEE_H

#include "XyzEmployeeIF.H"
#include "Utils.H"
#include <string>

class XyzEmployee : public XyzEmployeeIF
{
protected:
    std::string mEmployeeId;
    std::string mName;
    std::string mGender;
    xyz::EmployeeType mType;
    xyz::EmployeeStatus mStatus;
    std::string mDob;
    std::string mDoj;
    std::string mDol; // set by manager

public:
    XyzEmployee();
    XyzEmployee(const std::string& idParm, const std::string& nameParm, const std::string& genderParm,
                xyz::EmployeeType typeParm, xyz::EmployeeStatus statusParm,
                const std::string& dobParm, const std::string& dojParm, const std::string& dolParm = "NA");
    virtual ~XyzEmployee();

    // XyzEmployeeIF
    std::string getName() const override;
    std::string getId() const override;
    xyz::EmployeeType getType() const override;
    xyz::EmployeeStatus getStatus() const override;
    std::string getGender() const override;
    std::string getDob() const override;
    std::string getDoj() const override;
    std::string getDol() const override;

    void setStatus(xyz::EmployeeStatus statusParm) override;
    void setDol(const std::string& dolParm) override;

    virtual std::string getDetails() const override = 0;
};

#endif // XYZEMPLOYEE_H
