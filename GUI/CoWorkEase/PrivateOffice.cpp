#include "PrivateOffice.h"
#include <iostream>
using namespace std;

PrivateOffice :: PrivateOffice(){
    hasLock = false;
    hasWindow = false;
}
PrivateOffice :: PrivateOffice( int id, string n, double rate, int cap, bool lock, bool window) : Space( id, n, rate, cap) {
    hasLock = lock;
    hasWindow = window;
}

bool PrivateOffice :: getHasLock() const {
    return hasLock;
}
bool PrivateOffice :: getHasWindow() const {
    return hasWindow;
}

void PrivateOffice :: setHasLock( bool lock ) {
    hasLock = lock;
}
void PrivateOffice :: setHasWindow( bool window ) {
    hasWindow = window;
}

string PrivateOffice :: getType() const {
    return "Private Office";
}

double PrivateOffice :: calculatePrice( int hours ) const {
    double basePrice = Space :: calculatePrice(hours);
    return (basePrice + basePrice*0.1);
}

void PrivateOffice::displayInfo() const {
    cout << "ID: " << getSpaceID() << " | Name: " << getName() << " | Type: Private Office"
         << " | Rate: Rs." << getHourlyRate() << "/hr (10% premium applied)" << " | Capacity: " << getCapacity()
         << " | Lock: " << (hasLock ? "Yes" : "No") << " | Window: " << (hasWindow ? "Yes" : "No")
         << " | Status: " << (getIsBooked() ? "Booked" : "Available") << endl;
}

PrivateOffice :: ~PrivateOffice(){
    
}