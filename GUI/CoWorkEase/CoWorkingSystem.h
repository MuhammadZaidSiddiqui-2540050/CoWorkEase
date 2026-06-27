#ifndef COWORKING_SYSTEM_H
#define COWORKING_SYSTEM_H

#include <vector>
#include <string>
#include "Booking.h"
#include "Space.h"
#include "PrivateOffice.h"
#include "HotDesk.h"
#include "MeetingRoom.h"
#include "Member.h"
#include "DailyMember.h"
#include "MonthlyMember.h"
#include "CorporateMember.h"

using namespace std;

class CoWorkingSystem {
public:
    vector<Space*> spaces;
    vector<Member*> members;
    vector<Booking> bookings;
    
    int nextSpaceID;
    int nextMemberID;
    int nextBookingID;
    
    void loadSpacesFromFile();
    void loadMembersFromFile();
    void loadBookingsFromFile();
    
    void saveSpacesToFile();
    void saveMembersToFile();
    void saveBookingsToFile();
    
    Space* findSpaceByID(int id);
    Member* findMemberByID(int id);
    Booking* findBookingByID(int id);
    bool isTimeSlotAvailable(int spaceID, string date, int startHour, int duration);
    double calculateHoursUntilBooking(string bookingDate, int startHour);
    void generateRefundReceipt(int bookingID, double refundAmount);
    
public:
    CoWorkingSystem();
    ~CoWorkingSystem();
    
    void loadAllData();
    void saveAllData();
    void run();
    void addSampleData();
    
    void showMainMenu();
    void handleMenuChoice(int choice);

    void viewAllSpaces();
    void bookSpace();
    void cancelBooking();
    void addMember();
    void viewMemberHistory();
    void generateRevenueReport();
};

#endif