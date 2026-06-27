#include "MeetingRoom.h"
#include <iostream>
using namespace std;

MeetingRoom::MeetingRoom() : Space() {
    hasProjector = false;
    hasWhiteBoard = false;
    maxSeats = 0;
}

MeetingRoom::MeetingRoom(int id, string n, double rate, int cap, bool projector, bool whiteboard, int seats)
    : Space(id, n, rate, cap) {
    hasProjector = projector;
    hasWhiteBoard = whiteboard;
    maxSeats = seats;
}

MeetingRoom::~MeetingRoom() {
}

bool MeetingRoom::getHasProjector() const {
    return hasProjector;
}

bool MeetingRoom::getHasWhiteBoard() const {
    return hasWhiteBoard;
}

int MeetingRoom::getMaxSeats() const {
    return maxSeats;
}

void MeetingRoom::setHasProjector(bool projector) {
    hasProjector = projector;
}

void MeetingRoom::setHasWhiteBoard(bool whiteboard) {
    hasWhiteBoard = whiteboard;
}

void MeetingRoom::setMaxSeats(int seats) {
    if (seats > 0) {
        maxSeats = seats;
    } else {
        maxSeats = 2;
    }
}

string MeetingRoom::getType() const {
    return "Meeting Room";
}

double MeetingRoom::calculatePrice(int hours) const {
    double basePrice = Space::calculatePrice(hours);
    return basePrice * 1.20;
}

void MeetingRoom::displayInfo() const {
    cout << "ID: " << getSpaceID()
         << " | Name: " << getName()
         << " | Type: Meeting Room"
         << " | Rate: Rs." << getHourlyRate() << "/hr (20% premium)"
         << " | Capacity: " << getCapacity()
         << " | Projector: " << (hasProjector ? "Yes" : "No")
         << " | Whiteboard: " << (hasWhiteBoard ? "Yes" : "No")
         << " | Max Seats: " << maxSeats
         << " | Status: " << (getIsBooked() ? "Booked" : "Available") << endl;
}