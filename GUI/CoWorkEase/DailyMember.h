#ifndef DAILY_MEMBER_H
#define DAILY_MEMBER_H

#include "Member.h"

class DailyMember : public Member {
    public:
        DailyMember();
        DailyMember(int memberID, string Name, string phone, string joinDate);

        virtual double applyDiscount(double amount) const override;
        virtual string getMemberType() const override;
        virtual void displayInfo() const override;

        virtual ~DailyMember();

};

#endif