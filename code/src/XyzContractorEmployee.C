#include "XyzContractorEmployee.H"

XyzContractorEmployee::XyzContractorEmployee() : XyzEmployee(), mAgency(xyz::Avengers)
{
    mType = xyz::Contractor;
}

XyzContractorEmployee::XyzContractorEmployee(const std::string& idParm, const std::string& nameParm, const std::string& genderParm,
                                             xyz::EmployeeStatus statusParm, const std::string& dobParm, const std::string& dojParm,
                                             xyz::ContractorAgency agencyParm)
    : XyzEmployee(idParm, nameParm, genderParm, xyz::Contractor, statusParm, dobParm, dojParm, "NA"),
      mAgency(agencyParm) {}

XyzContractorEmployee::~XyzContractorEmployee() {}

xyz::ContractorAgency XyzContractorEmployee::getAgency() const
{
    return mAgency;
}
void XyzContractorEmployee::setAgency(xyz::ContractorAgency agencyParm)
{
    mAgency = agencyParm;
}

std::string XyzContractorEmployee::getDetails() const
{
    EmployeeDetailBuilder sBuilder;
    sBuilder.addId(mEmployeeId).addName(mName).addType(mType).addStatus(mStatus)
      .addGender(mGender).addDob(mDob).addDoj(mDoj).addDol(mDol)
      .addAgency(mAgency);
    return sBuilder.build();
}
