#ifndef XYZEMPLOYEEIF_H
#define XYZEMPLOYEEIF_H

#include "Utils.H"
#include <string>

class XyzEmployeeIF
{
public:
    virtual ~XyzEmployeeIF() {}

    // accessors
    virtual std::string getName() const = 0;
    virtual std::string getId() const = 0;
    virtual xyz::EmployeeType getType() const = 0;
    virtual xyz::EmployeeStatus getStatus() const = 0;
    virtual std::string getGender() const = 0;
    virtual std::string getDob() const = 0;
    virtual std::string getDoj() const = 0;
    virtual std::string getDol() const = 0;

    // mutators
    virtual void setStatus(xyz::EmployeeStatus statusParm) = 0;
    virtual void setDol(const std::string& dolParm) = 0;

    // details
    virtual std::string getDetails() const = 0;
};

#endif // XYZEMPLOYEEIF_H
