#include "XyzInternEmployee.H"

XyzInternEmployee::XyzInternEmployee() {
}

XyzInternEmployee::XyzInternEmployee(const std::string& idParm, const std::string& nameParm, const std::string& genderParm,
                                     xyz::EmployeeStatus statusParm, const std::string& dobParm, const std::string& dojParm,
                                     xyz::InternCollege collegeParm, xyz::InternBranch branchParm)
    : XyzEmployee(idParm, nameParm, genderParm, xyz::Intern, statusParm, dobParm, dojParm, "NA"),
      mCollege(collegeParm), mBranch(branchParm) {}

XyzInternEmployee::~XyzInternEmployee() {}

xyz::InternCollege XyzInternEmployee::getCollege() const
{
    return mCollege;
}
xyz::InternBranch XyzInternEmployee::getBranch() const
{
    return mBranch;
}
void XyzInternEmployee::setCollege(xyz::InternCollege collegeParm)
{
    mCollege = collegeParm;
}
void XyzInternEmployee::setBranch(xyz::InternBranch branchParm)
{
    mBranch = branchParm;
}

std::string XyzInternEmployee::getDetails() const
{
    EmployeeDetailBuilder sBuilder;
    sBuilder.addId(mEmployeeId).addName(mName).addType(mType).addStatus(mStatus)
      .addGender(mGender).addDob(mDob).addDoj(mDoj).addDol(mDol)
      .addCollege(mCollege).addBranch(mBranch);
    return sBuilder.build();
}
