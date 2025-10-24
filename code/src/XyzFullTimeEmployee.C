#include "XyzFullTimeEmployee.H"

XyzFullTimeEmployee::XyzFullTimeEmployee() : XyzEmployee(), mLeavesAvailed(0)
{
    mType = xyz::FullTime;
}

XyzFullTimeEmployee::XyzFullTimeEmployee(const std::string& idParm, const std::string& nameParm, const std::string& genderParm,
                                         xyz::EmployeeStatus statusParm, const std::string& dobParm, const std::string& dojParm,
                                         int leavesParm)
    : XyzEmployee(idParm, nameParm, genderParm, xyz::FullTime, statusParm, dobParm, dojParm, "NA"),
      mLeavesAvailed(leavesParm) {}

XyzFullTimeEmployee::~XyzFullTimeEmployee() {}

int XyzFullTimeEmployee::getLeavesAvailed() const
{
    return mLeavesAvailed;
}

void XyzFullTimeEmployee::addLeaves(int leavesParm)
{
    mLeavesAvailed += leavesParm;
    if (mLeavesAvailed < 0)
    {
        mLeavesAvailed = 0;
    }
    if (mLeavesAvailed > 100)
    {
        mLeavesAvailed = 100;
    }
}
void XyzFullTimeEmployee::setLeaves(int leavesParm)
{
    mLeavesAvailed = (leavesParm < 0 ? 0 : leavesParm);
}

std::string XyzFullTimeEmployee::getDetails() const
{
    EmployeeDetailBuilder sBuilder;
    sBuilder.addId(mEmployeeId).addName(mName).addType(mType).addStatus(mStatus)
      .addGender(mGender).addDob(mDob).addDoj(mDoj).addDol(mDol).addLeaves(mLeavesAvailed);
    return sBuilder.build();
}
