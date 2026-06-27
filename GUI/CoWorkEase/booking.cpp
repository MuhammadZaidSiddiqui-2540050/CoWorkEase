#include "booking.h"
#include<iostream>
#include <cctype>
using namespace std;

Booking :: Booking() {
    bookingID = 0;
    spaceID = 0;
    memberID = 0;
    date = "";
    startHours = 0;
    durationHours = 0;
    totalPrice = 0.0;
    status = "active";
    refundIssued = false;
    cancellationDate = "";
}


Booking::Booking(int bID, int sID, int mID, string d, int sHour, int dHour, double price) {
    bookingID = bID;
    spaceID = sID;
    memberID = mID;
    date = d;             
    startHours = sHour;
    durationHours = dHour; 
    totalPrice = price;    
    status = "active";
    refundIssued = false;
    cancellationDate = "";
}


int Booking :: getBookingID() const {
    return bookingID;
}
int Booking :: getSpaceID() const {
    return spaceID;
}
int Booking :: getMemberID() const {
    return memberID;
}
string Booking :: getDate() const {
    return date;
}
int Booking :: getStartHours() const {
    return startHours;
}
int Booking :: getDurationHours() const {
    return durationHours;
}
double Booking :: getTotalPrice() const {
    return totalPrice;
}
string Booking :: getStatus() const {
    return status;
}
bool Booking :: getRefundIssued() const {
    return refundIssued;
}
string Booking :: getCancellationDate() const {
    return cancellationDate;
}

void Booking :: setStatus(string s) {
    for(char &c : s) {
        c = tolower(c);
    }
    if( s == "active" || s == "cancelled" ){
        status = s;
    }
    else{
        status = "active";
    }
}
void Booking :: setRefundIssued(bool issued) {
    refundIssued = issued;
}
void Booking :: setTotalPrice(double total) {
    if(total >= 0)
        totalPrice = total;
}
void Booking :: setCancellationDate(string date){
    cancellationDate = date;
}


void Booking :: displayInfo() const {
    cout<<"ID: " <<bookingID <<" | Space: " <<spaceID <<" | Member: " <<memberID 
    <<" | Date: " <<date <<" | Start: " <<startHours <<":00 | Duration: " <<durationHours
    <<"h | Price: Rs. " <<totalPrice <<" | Status: " <<status <<endl;
}

bool Booking :: conflictsWith(const Booking& other) const {

    if( spaceID != other.spaceID) {
        return false;
    }
    if( date != other.date) {
        return false;
    }
    if (status == "cancelled" || other.status == "cancelled"){
        return false;
    }

    int thisStart = startHours;
    int thisEnd = startHours + durationHours;

    int otherStart = other.startHours;
    int otherEnd = other.startHours + other.durationHours;

    bool overlaps = (thisStart < otherEnd) && (thisEnd > otherStart);
    return overlaps;
}