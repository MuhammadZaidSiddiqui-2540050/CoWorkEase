#include "Member.h"
#include <iostream>
using namespace std;

Member::Member() {
    memberID = 0;
    name = "";
    phone = "";
    joinDate = "";
    totalSpent = 0.0;
}

Member::Member(int id, string n, string p, string date) {
    memberID = id;
    name = n;
    phone = p;
    joinDate = date;
    totalSpent = 0.0;
}

Member::~Member() {}

int Member::getMemberID() const { return memberID; }
string Member::getName() const { return name; }
string Member::getPhone() const { return phone; }
string Member::getJoinDate() const { return joinDate; }
double Member::getTotalSpent() const { return totalSpent; }

void Member::setMemberID(int id) {
    if (id > 0) memberID = id;
    else memberID = 0;
}

void Member::setName(string n) {
    if (!n.empty()) name = n;
    else name = "Unknown";
}

void Member::setPhone(string p) {
    if (!p.empty()) phone = p;
    else phone = "00000000000";
}

void Member::setJoinDate(string date) {
    if (!date.empty()) joinDate = date;
    else joinDate = "2000-01-01";
}

void Member::addToSpent(double amount) {
    if (amount >= 0) totalSpent += amount;
}

void Member::displayInfo() const {
    cout << "ID: " << memberID
         << " | Name: " << name
         << " | Phone: " << phone
         << " | Join Date: " << joinDate
         << " | Total Spent: Rs." << totalSpent << endl;
}