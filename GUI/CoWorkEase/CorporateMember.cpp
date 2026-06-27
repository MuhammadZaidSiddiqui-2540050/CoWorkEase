#include "CorporateMember.h"
#include <iostream>
using namespace std;

CorporateMember::CorporateMember() : Member() {
    companyName = "";
    includedSeats = 0;
}

CorporateMember::CorporateMember(int id, string n, string p, string date, string company, int seats)
    : Member(id, n, p, date) {
    companyName = company;
    includedSeats = seats;
}

CorporateMember::~CorporateMember() {
}

string CorporateMember::getCompanyName() const {
    return companyName;
}

int CorporateMember::getIncludedSeats() const {
    return includedSeats;
}

void CorporateMember::setCompanyName(string company) {
    if (!company.empty()) {
        companyName = company;
    } else {
        companyName = "Unknown";
    }
}

void CorporateMember::setIncludedSeats(int seats) {
    if (seats > 0) {
        includedSeats = seats;
    } else {
        includedSeats = 1;
    }
}

double CorporateMember::applyDiscount(double amount) const {
    return amount * 0.70;   
}

string CorporateMember::getMemberType() const {
    return "Corporate";
}

void CorporateMember::displayInfo() const {
    cout << "ID: " << getMemberID()
         << " | Name: " << getName()
         << " | Phone: " << getPhone()
         << " | Type: Corporate (30% discount)"
         << " | Company: " << companyName
         << " | Included Seats: " << includedSeats
         << " | Join Date: " << getJoinDate()
         << " | Total Spent: Rs." << getTotalSpent() << endl;
}