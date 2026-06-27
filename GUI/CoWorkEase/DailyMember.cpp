#include "DailyMember.h"
#include <iostream>
using namespace std;

DailyMember::DailyMember() : Member() {
}

DailyMember::DailyMember(int id, string n, string p, string date)
    : Member(id, n, p, date) {
}

DailyMember::~DailyMember() {
}

double DailyMember::applyDiscount(double amount) const {
    return amount;
}

string DailyMember::getMemberType() const {
    return "Daily";
}

void DailyMember::displayInfo() const {
    cout << "ID: " << getMemberID()
         << " | Name: " << getName()
         << " | Phone: " << getPhone()
         << " | Type: Daily (0% discount)"
         << " | Join Date: " << getJoinDate()
         << " | Total Spent: Rs." << getTotalSpent() << endl;
}