#ifndef MONTHLY_MEMBER_H
#define MONTHLY_MEMBER_H

#include "Member.h"

class MonthlyMember : public Member {
    private:
        double monthlyFee;
    public: 
        MonthlyMember();
        MonthlyMember(int memberID, string name, string phone, string joinDate, double monthlyFee);

        double getMonthlyFee() const;

        void setMonthlyFee(double fee);

        virtual double applyDiscount(double amount) const override;
        virtual string getMemberType() const override;
        virtual void displayInfo() const override;

         virtual ~MonthlyMember();
};

#endif