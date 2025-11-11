#ifndef XYZCONTRACTOREMPLOYEE_H
#define XYZCONTRACTOREMPLOYEE_H

#include "XyzEmployee.H"
#include "EmployeeDetailBuilder.H"
#include <string>

class XyzContractorEmployee : public XyzEmployee
{
private:
    xyz::ContractorAgency mAgency;

public:
    XyzContractorEmployee();
    XyzContractorEmployee(const std::string& idParm,
                          const std::string& nameParm,
                          const std::string& genderParm,
                          xyz::EmployeeStatus statusParm,
                          const std::string& dobParm,
                          const std::string& dojParm,
                          xyz::ContractorAgency agencyParm);
    ~XyzContractorEmployee();

    xyz::ContractorAgency getAgency() const;
    void setAgency(xyz::ContractorAgency agencyParm);

    std::string getDetails() const override;
};

#endif // XYZCONTRACTOREMPLOYEE_H
