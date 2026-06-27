#include "MonthlyMember.h"
#include <iostream>
using namespace std;

MonthlyMember::MonthlyMember() : Member() {
    monthlyFee = 0.0;
}

MonthlyMember::MonthlyMember(int id, string n, string p, string date, double fee)
    : Member(id, n, p, date) {
    monthlyFee = fee;
}

MonthlyMember::~MonthlyMember() {
}

double MonthlyMember::getMonthlyFee() const {
    return monthlyFee;
}

void MonthlyMember::setMonthlyFee(double fee) {
    if (fee >= 0) {
        monthlyFee = fee;
    } else {
        monthlyFee = 0.0;
    }
}

double MonthlyMember::applyDiscount(double amount) const {
    return amount * 0.80;   
}

string MonthlyMember::getMemberType() const {
    return "Monthly";
}

void MonthlyMember::displayInfo() const {
    cout << "ID: " << getMemberID()
         << " | Name: " << getName()
         << " | Phone: " << getPhone()
         << " | Type: Monthly (20% discount)"
         << " | Monthly Fee: Rs." << monthlyFee
         << " | Join Date: " << getJoinDate()
         << " | Total Spent: Rs." << getTotalSpent() << endl;
}