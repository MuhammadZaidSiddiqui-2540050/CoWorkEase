#include "space.h"
#include <iostream>
#include <string>
using namespace std;

Space :: Space() {
    spaceID = 0;
    name = "";
    hourlyRate = 0.0;
    capacity = 0;
    isBooked = false;
}
Space :: Space(int id, string n, double hRate, int cap ) {
    spaceID = id;
    name = n;
    hourlyRate = hRate;
    capacity = cap;
    isBooked = false;
}


int Space :: getSpaceID() const {
    return spaceID;
}
string Space :: getName() const {
    return name;
}
double Space :: getHourlyRate() const {
    return hourlyRate;
}
int Space :: getCapacity() const {
    return capacity;
} 
bool Space :: getIsBooked() const {
    return isBooked;
}

void Space :: setSpaceID( int id ) {
    if( id > 0 ) {
        spaceID = id;
    } 
    else spaceID = 0;
}
void Space :: setName( string n) {
    if (!n.empty()) {
        name = n;
    }
    else name = "Unknown";
}
void Space :: setHourlyRate( double rate ) {
    if( rate > 0) {
        hourlyRate = rate;
    }
    else hourlyRate = 0.0;
}
void Space :: setCapacity( int cap ) {
    if( cap > 0 ) {
        capacity = cap;
    }
    else capacity = 1;
}
void Space :: setIsBooked( bool booked ) {
    isBooked = booked;
}

double Space :: calculatePrice (int hours ) const {
    if ( hours < 1 ) return 0;
    if ( hours > 8 ) hours = 8;
    return hourlyRate*hours;
}

void Space :: displayInfo() const {
    cout << "ID: " << spaceID << " | Name: " << name << " | Rate: Rs." << hourlyRate << "/hr"
         << " | Capacity: " << capacity << " | Status: " << (isBooked ? "Booked" : "Available") << endl;
}

bool Space::isAvailable(string, int, int) {
    return !isBooked;
}
void Space :: markBooked(bool booked) {
    isBooked = booked;
}

Space :: ~Space(){

}