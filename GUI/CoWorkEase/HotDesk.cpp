#include "HotDesk.h"
#include <iostream>
using namespace std;

HotDesk :: HotDesk() {
    hasPowerOutlet = false;
    deskNumber = 0;
}
HotDesk :: HotDesk(int id, string n, double rate, int cap, bool outlet, int num) : Space (id, n, rate, cap) {
    hasPowerOutlet = outlet;
    deskNumber = num;
}

bool HotDesk :: getHasPowerOutlet() const {
    return hasPowerOutlet;
}
int HotDesk :: getDeskNumber() const {
    return deskNumber;
}

void HotDesk :: setHasPowerOutlet( bool outlet ) {
    hasPowerOutlet = outlet;
}
void HotDesk :: setDeskNumber( int num ) {
    if( num > 1 ) deskNumber = num;
    else deskNumber = 1;
}

string HotDesk :: getType() const {
    return "Hot Desk";
}
double HotDesk :: calculatePrice(int hours)  const {
    return Space :: calculatePrice(hours);
}

void HotDesk :: displayInfo() const {
    cout << "ID: " << getSpaceID() << " | Name: " << getName() << " | Type: Hot Desk" << " | Rate: Rs." << getHourlyRate() << "/hr"
        << " | Capacity: " << getCapacity() << " | Power Outlet: " << (hasPowerOutlet ? "Yes" : "No") << " | Desk #: " << deskNumber
        << " | Status: " << (getIsBooked() ? "Booked" : "Available") << endl;
}

HotDesk :: ~HotDesk(){

}

