#include "XyzFullTimeEmployee.H"
#include "EmployeeDetailBuilder.H"
#include <sstream>
#include <iostream>

XyzFullTimeEmployee::XyzFullTimeEmployee() {
}

XyzFullTimeEmployee::XyzFullTimeEmployee(const std::string& idParm,
                                         const std::string& nameParm,
                                         const std::string& genderParm,
                                         xyz::EmployeeStatus statusParm,
                                         const std::string& dobParm,
                                         const std::string& dojParm,
                                         int leavesAvailedParm,
                                         int leavesAppliedParm)
    : XyzEmployee(idParm, nameParm, genderParm, xyz::FullTime, statusParm, dobParm, dojParm, "NA"),
      mLeavesAvailed(leavesAvailedParm),
      mLeavesApplied(leavesAppliedParm)
{
}

XyzFullTimeEmployee::~XyzFullTimeEmployee() {}

int XyzFullTimeEmployee::getLeavesAvailed() const
{
    return mLeavesAvailed;
}

int XyzFullTimeEmployee::getLeavesApplied() const
{
    return mLeavesApplied;
}

void XyzFullTimeEmployee::addLeaves(int leavesParm)
{
    mLeavesAvailed += leavesParm;
    if (mLeavesAvailed < 0) mLeavesAvailed = 0;
    if (mLeavesAvailed > 100) mLeavesAvailed = 100;
}

void XyzFullTimeEmployee::applyLeaves(int leavesParm)
{
    mLeavesApplied += leavesParm;
    if (mLeavesApplied < 0) mLeavesApplied = 0;
    if (mLeavesApplied > 30) mLeavesApplied = 30; // you can cap applied leaves to 30 if desired
}

void XyzFullTimeEmployee::setLeavesAvailed(int leavesParm)
{
    mLeavesAvailed = (leavesParm < 0 ? 0 : leavesParm);
}

void XyzFullTimeEmployee::setLeavesApplied(int leavesParm)
{
    mLeavesApplied = (leavesParm < 0 ? 0 : leavesParm);
}

std::string XyzFullTimeEmployee::getDetails() const
{
    EmployeeDetailBuilder sBuilder;
    sBuilder.addId(mEmployeeId)
            .addName(mName)
            .addType(mType)
            .addStatus(mStatus)
            .addGender(mGender)
            .addDob(mDob)
            .addDoj(mDoj)
            .addDol(mDol)
            .addLeaves(mLeavesAvailed)
            .addLeavesApplied(mLeavesApplied);
    return sBuilder.build();
}
