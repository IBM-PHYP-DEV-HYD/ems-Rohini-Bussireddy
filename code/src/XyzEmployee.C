#include "XyzEmployee.H"

XyzEmployee::XyzEmployee()
    : mEmployeeId(""), mName(""), mGender(""), mType(xyz::FullTime), mStatus(xyz::Active),
      mDob(""), mDoj(""), mDol("NA") {}

XyzEmployee::XyzEmployee(const std::string& idParm, const std::string& nameParm, const std::string& genderParm,
                         xyz::EmployeeType typeParm, xyz::EmployeeStatus statusParm,
                         const std::string& dobParm, const std::string& dojParm, const std::string& dolParm)
    : mEmployeeId(idParm), mName(nameParm), mGender(genderParm), mType(typeParm),
      mStatus(statusParm), mDob(dobParm), mDoj(dojParm), mDol(dolParm) {}

XyzEmployee::~XyzEmployee() {}

std::string XyzEmployee::getName() const
{
    return mName;
}
std::string XyzEmployee::getId() const
{
    return mEmployeeId;
}
xyz::EmployeeType XyzEmployee::getType() const
{
    return mType;
}
xyz::EmployeeStatus XyzEmployee::getStatus() const
{
    return mStatus;
}
std::string XyzEmployee::getGender() const
{
    return mGender;
}
std::string XyzEmployee::getDob() const
{
    return mDob;
}
std::string XyzEmployee::getDoj() const
{
    return mDoj;
}
std::string XyzEmployee::getDol() const
{
    return mDol;
}

void XyzEmployee::setStatus(xyz::EmployeeStatus statusParm)
{
    mStatus = statusParm;
}
void XyzEmployee::setDol(const std::string& dolParm)
{
    mDol = dolParm;
}
