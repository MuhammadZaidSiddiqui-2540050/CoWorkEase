#ifndef CORPORATE_MEMBER_H
#define CORPORATE_MEMBER_H

#include "Member.h"

class CorporateMember : public Member {
private:
    string companyName;
    int includedSeats;  
    
public:
    CorporateMember();
    CorporateMember(int memberID, string Name, string phone, string joinDate, string companyName, int seatsIncluded);

    string getCompanyName() const;        
    int getIncludedSeats() const;        

    void setCompanyName(string name);
    void setIncludedSeats(int seats);     

    virtual double applyDiscount(double amount) const override;
    virtual string getMemberType() const override;
    virtual void displayInfo() const override;

    virtual ~CorporateMember();
};

#endif