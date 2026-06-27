#ifndef MEMBER_H
#define MEMBER_H

#include<iostream>
using namespace std;

class Member{
    protected: 
        int memberID;
        string name;
        string phone;
        string joinDate;
        double totalSpent;
    public:
        Member();
        Member(int memberID, string name, string phone, string joinDate);

        int getMemberID() const;
        string getName() const;
        string getPhone() const;
        string getJoinDate() const;
        double getTotalSpent() const;

        void setMemberID(int id);
        void setName(string n);
        void setPhone(string ph);
        void setJoinDate(string date);
        void addToSpent(double amount);

        virtual double applyDiscount(double amount) const = 0;
        virtual string getMemberType() const = 0;
        virtual void displayInfo() const;

        virtual ~Member();

};

#endif