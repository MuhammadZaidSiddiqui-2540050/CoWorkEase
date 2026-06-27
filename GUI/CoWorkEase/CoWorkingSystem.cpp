#include "CoWorkingSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdio>
#include <iomanip>
#include <algorithm>
using namespace std;

CoWorkingSystem::CoWorkingSystem() {
    nextSpaceID = 100;
    nextMemberID = 1000;
    nextBookingID = 5000;
}

CoWorkingSystem::~CoWorkingSystem() {
    for (auto space : spaces) {
        delete space;
    }
    for (auto member : members) {
        delete member;
    }
}

void CoWorkingSystem::loadAllData() {
    loadSpacesFromFile();
    loadMembersFromFile();
    loadBookingsFromFile();
    
    if (spaces.empty() && members.empty()) {
        addSampleData();
    }
}

void CoWorkingSystem::saveAllData() {
    saveSpacesToFile();
    saveMembersToFile();
    saveBookingsToFile();
    cout << "\nAll data saved successfully!" << endl;
}

void CoWorkingSystem::run() {
    loadAllData();
    
    int choice;
    do {
        showMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }
        
        handleMenuChoice(choice);
        
    } while (choice != 8);
    
    saveAllData();
    cout << "Thank you for using CoWorkEase!" << endl;
}

void CoWorkingSystem::showMainMenu() {
    cout << "\n========================================" << endl;
    cout << "     CoWorkEase - Main Menu" << endl;
    cout << "========================================" << endl;
    cout << "1. View All Spaces" << endl;
    cout << "2. Book a Space" << endl;
    cout << "3. Cancel a Booking" << endl;
    cout << "4. Add New Member" << endl;
    cout << "5. View Member Booking History" << endl;
    cout << "6. Generate Revenue Report" << endl;
    cout << "7. Add Sample Data" << endl;
    cout << "8. Save & Exit" << endl;
    cout << "========================================" << endl;
}

void CoWorkingSystem::handleMenuChoice(int choice) {
    switch (choice) {
        case 1: viewAllSpaces(); break;
        case 2: bookSpace(); break;
        case 3: cancelBooking(); break;
        case 4: addMember(); break;
        case 5: viewMemberHistory(); break;
        case 6: generateRevenueReport(); break;
        case 7: addSampleData(); break;
        case 8: cout << "Exiting..." << endl; break;
        default: cout << "Invalid choice! Try again." << endl;
    }
}

void CoWorkingSystem::viewAllSpaces() {
    cout << "\n========== ALL SPACES ==========" << endl;
    cout << "ID | Name | Type | Rate/hr | Capacity | Status" << endl;
    cout << "----------------------------------------" << endl;
    
    for (auto space : spaces) {
        cout << space->getSpaceID() << " | "
             << space->getName() << " | "
             << space->getType() << " | Rs."
             << space->getHourlyRate() << " | "
             << space->getCapacity() << " | "
             << (space->getIsBooked() ? "Booked" : "Available") << endl;
    }
}

void CoWorkingSystem::bookSpace() {
    cout << "\n========== BOOK A SPACE ==========" << endl;
    
    viewAllSpaces();
    
    int spaceID, memberID, startHour, duration;
    string date;
    
    cout << "\nEnter Space ID: ";
    cin >> spaceID;
    
    Space* space = findSpaceByID(spaceID);
    if (!space) {
        cout << "Invalid Space ID!" << endl;
        return;
    }
    
    cout << "Enter Member ID: ";
    cin >> memberID;
    
    Member* member = findMemberByID(memberID);
    if (!member) {
        cout << "Invalid Member ID!" << endl;
        return;
    }
    
    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> date;
    
    cout << "Enter Start Hour (9-21): ";
    cin >> startHour;
    
    if (startHour < 9 || startHour > 21) {
        cout << "Invalid hour! Booking allowed only between 9 AM and 9 PM." << endl;
        return;
    }
    
    cout << "Enter Duration (1-8 hours): ";
    cin >> duration;
    
    if (duration < 1 || duration > 8) {
        cout << "Invalid duration! Maximum 8 hours per booking." << endl;
        return;
    }
    
    if (!isTimeSlotAvailable(spaceID, date, startHour, duration)) {
        cout << "Sorry, this space is already booked for the selected time!" << endl;
        return;
    }
    
    double basePrice = space->calculatePrice(duration);
    double finalPrice = member->applyDiscount(basePrice);
    
    Booking newBooking(nextBookingID++, spaceID, memberID, date, startHour, duration, finalPrice);
    bookings.push_back(newBooking);
    
    space->markBooked(true);
    member->addToSpent(finalPrice);
    
    cout << "\nBooking Successful!" << endl;
    cout << "Booking ID: " << newBooking.getBookingID() << endl;
    cout << "Total Price (after discount): Rs. " << finalPrice << endl;
}

void CoWorkingSystem::cancelBooking() {
    cout << "\n========== CANCEL BOOKING ==========" << endl;
    
    int bookingID;
    cout << "Enter Booking ID to cancel: ";
    cin >> bookingID;
    
    Booking* booking = findBookingByID(bookingID);
    if (!booking) {
        cout << "Booking not found!" << endl;
        return;
    }
    
    if (booking->getStatus() == "cancelled") {
        cout << "This booking is already cancelled." << endl;
        return;
    }
    
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    
    int year, month, day;
    sscanf(booking->getDate().c_str(), "%d-%d-%d", &year, &month, &day);
    
    tm bookingTm = {};
    bookingTm.tm_year = year - 1900;
    bookingTm.tm_mon = month - 1;
    bookingTm.tm_mday = day;
    bookingTm.tm_hour = booking->getStartHours();
    bookingTm.tm_min = 0;
    bookingTm.tm_sec = 0;
    
    time_t bookingTime = mktime(&bookingTm);
    double secondsDiff = difftime(bookingTime, now);
    double hoursUntilBooking = secondsDiff / 3600.0;
    
    bool refundApplicable = false;
    double refundAmount = 0;
    
    if (hoursUntilBooking > 24) {
        refundApplicable = true;
        refundAmount = booking->getTotalPrice();
        cout << "\nCancellation confirmed! (" << hoursUntilBooking << " hours until booking)" << endl;
        cout << "Refund eligible: Rs. " << refundAmount << " will be credited." << endl;
    } else if (hoursUntilBooking > 0 && hoursUntilBooking <= 24) {
        cout << "\nCancellation confirmed but NO REFUND." << endl;
        cout << " (Only " << hoursUntilBooking << " hours until booking - less than 24-hour notice)" << endl;
    } else {
        cout << "\nCannot cancel past bookings!" << endl;
        return;
    }
    
    booking->setStatus("cancelled");
    
    Space* space = findSpaceByID(booking->getSpaceID());
    if (space) space->markBooked(false);
    
    if (refundApplicable) {
        Member* member = findMemberByID(booking->getMemberID());
        if (member) {
            member->addToSpent(-refundAmount);
        }
    }
    
    cout << "\nBooking #" << bookingID << " cancelled successfully!" << endl;
    
    if (refundApplicable) {
        char generateReceipt;
        cout << "\nGenerate refund receipt? (y/n): ";
        cin >> generateReceipt;
        if (generateReceipt == 'y' || generateReceipt == 'Y') {
            generateRefundReceipt(booking->getBookingID(), refundAmount);
        }
    }
}

void CoWorkingSystem::addMember() {
    cout << "\n========== ADD NEW MEMBER ==========" << endl;
    cout << "Member Types:" << endl;
    cout << "1. Daily (0% discount)" << endl;
    cout << "2. Monthly (20% discount)" << endl;
    cout << "3. Corporate (30% discount)" << endl;
    cout << "Select type: ";
    
    int type;
    cin >> type;
    
    string name, phone, joinDate;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Phone: ";
    getline(cin, phone);
    cout << "Enter Join Date (YYYY-MM-DD): ";
    getline(cin, joinDate);
    
    Member* newMember = nullptr;
    
    switch (type) {
        case 1:
            newMember = new DailyMember(nextMemberID++, name, phone, joinDate);
            break;
        case 2: {
            double monthlyFee;
            cout << "Enter Monthly Fee: ";
            cin >> monthlyFee;
            newMember = new MonthlyMember(nextMemberID++, name, phone, joinDate, monthlyFee);
            break;
        }
        case 3: {
            string companyName;
            int seats;
            cout << "Enter Company Name: ";
            cin.ignore();
            getline(cin, companyName);
            cout << "Enter Number of Included Seats: ";
            cin >> seats;
            newMember = new CorporateMember(nextMemberID++, name, phone, joinDate, companyName, seats);
            break;
        }
        default:
            cout << "Invalid type!" << endl;
            return;
    }
    
    members.push_back(newMember);
    cout << "\nMember added successfully! Member ID: " << newMember->getMemberID() << endl;
}

void CoWorkingSystem::viewMemberHistory() {
    cout << "\n========== MEMBER BOOKING HISTORY ==========" << endl;
    
    int memberID;
    cout << "Enter Member ID: ";
    cin >> memberID;
    
    Member* member = findMemberByID(memberID);
    if (!member) {
        cout << "Member not found!" << endl;
        return;
    }
    
    cout << "\nMember: " << member->getName() << " (" << member->getMemberType() << ")" << endl;
    cout << "Total Spent: Rs. " << member->getTotalSpent() << "\n" << endl;
    
    cout << "Booking ID | Space ID | Date | Start | Hours | Price | Status" << endl;
    cout << "------------------------------------------------" << endl;
    
    for (auto& booking : bookings) {
        if (booking.getMemberID() == memberID) {
            cout << booking.getBookingID() << " | "
                 << booking.getSpaceID() << " | "
                 << booking.getDate() << " | "
                 << booking.getStartHours() << ":00 | "
                 << booking.getDurationHours() << " | Rs."
                 << booking.getTotalPrice() << " | "
                 << booking.getStatus() << endl;
        }
    }
}

void CoWorkingSystem::generateRevenueReport() {
    cout << "\n========== REVENUE REPORT ==========" << endl;
    
    double totalRevenue = 0;
    int activeBookings = 0;
    int cancelledBookings = 0;
    
    for (auto& booking : bookings) {
        if (booking.getStatus() == "active") {
            totalRevenue += booking.getTotalPrice();
            activeBookings++;
        } else {
            cancelledBookings++;
        }
    }
    
    cout << "Total Bookings: " << bookings.size() << endl;
    cout << "Active Bookings: " << activeBookings << endl;
    cout << "Cancelled Bookings: " << cancelledBookings << endl;
    cout << "Total Revenue: Rs. " << totalRevenue << endl;
    cout << "Average Booking Value: Rs. " 
         << (activeBookings > 0 ? totalRevenue / activeBookings : 0) << endl;
}

void CoWorkingSystem::addSampleData() {
    spaces.push_back(new PrivateOffice(1, "Executive Suite", 500, 1, true, true));
    spaces.push_back(new HotDesk(2, "Open Desk A", 200, 1, true, 101));
    spaces.push_back(new HotDesk(3, "Open Desk B", 200, 1, true, 102));
    spaces.push_back(new MeetingRoom(4, "Board Room", 800, 8, true, true, 10));
    spaces.push_back(new MeetingRoom(5, "Small Huddle", 400, 4, true, false, 6));
    
    members.push_back(new DailyMember(1001, "Ali Khan", "0300-1234567", "2025-01-15"));
    members.push_back(new MonthlyMember(1002, "Sara Ahmed", "0301-2345678", "2025-01-10", 5000));
    members.push_back(new CorporateMember(1003, "Tech Solutions", "0302-3456789", "2025-01-01", "TechCorp", 5));
    
    nextSpaceID = 6;
    nextMemberID = 1004;
    nextBookingID = 5001;
    
    cout << "Sample data added successfully!" << endl;
}

Space* CoWorkingSystem::findSpaceByID(int id) {
    for (auto space : spaces) {
        if (space->getSpaceID() == id) return space;
    }
    return nullptr;
}

Member* CoWorkingSystem::findMemberByID(int id) {
    for (auto member : members) {
        if (member->getMemberID() == id) return member;
    }
    return nullptr;
}

Booking* CoWorkingSystem::findBookingByID(int id) {
    for (auto& booking : bookings) {
        if (booking.getBookingID() == id) return &booking;
    }
    return nullptr;
}

bool CoWorkingSystem::isTimeSlotAvailable(int spaceID, string date, int startHour, int duration) {
    for (auto& booking : bookings) {
        if (booking.getStatus() != "cancelled" && 
            booking.getSpaceID() == spaceID && 
            booking.getDate() == date) {
            
            int bookedStart = booking.getStartHours();
            int bookedEnd = bookedStart + booking.getDurationHours();
            int newEnd = startHour + duration;
            
            if ((startHour < bookedEnd && newEnd > bookedStart)) {
                return false;
            }
        }
    }
    return true;
}

double CoWorkingSystem::calculateHoursUntilBooking(string bookingDate, int startHour) {
    time_t now = time(nullptr);
    tm* local = localtime(&now);
    
    int year, month, day;
    sscanf(bookingDate.c_str(), "%d-%d-%d", &year, &month, &day);
    
    tm bookingTm = {};
    bookingTm.tm_year = year - 1900;
    bookingTm.tm_mon = month - 1;
    bookingTm.tm_mday = day;
    bookingTm.tm_hour = startHour;
    
    time_t bookingTime = mktime(&bookingTm);
    return difftime(bookingTime, now) / 3600.0;
}

void CoWorkingSystem::generateRefundReceipt(int bookingID, double refundAmount) {
    ofstream receipt(("refund_receipt_" + to_string(bookingID) + ".txt").c_str());
    
    time_t now = time(nullptr);
    char* dateTime = ctime(&now);
    
    receipt << "========================================" << endl;
    receipt << "        COWORKEASE - REFUND RECEIPT" << endl;
    receipt << "========================================" << endl;
    receipt << "Receipt Date: " << dateTime;
    receipt << "Booking ID: " << bookingID << endl;
    receipt << "Refund Amount: Rs. " << refundAmount << endl;
    receipt << "Reason: Cancellation > 24 hours before booking" << endl;
    receipt << "========================================" << endl;
    receipt << "Thank you for using CoWorkEase!" << endl;
    
    receipt.close();
    cout << "Refund receipt saved to refund_receipt_" << bookingID << ".txt" << endl;
}

void CoWorkingSystem::loadSpacesFromFile() {
    ifstream file("spaces.txt");
    if (!file.is_open()) return;
    
    string line;
    while (getline(file, line)) {
        // Parse and create spaces
        // Format: ID|Type|Name|Rate|Capacity|Extra1|Extra2|Extra3
    }
    file.close();
}

void CoWorkingSystem::saveSpacesToFile() {
    ofstream file("spaces.txt");
    if (!file.is_open()) return;
    
    for (auto space : spaces) {
        file << space->getSpaceID() << "|"
             << space->getType() << "|"
             << space->getName() << "|"
             << space->getHourlyRate() << "|"
             << space->getCapacity() << endl;
    }
    file.close();
}

void CoWorkingSystem::loadMembersFromFile() {
    ifstream file("members.txt");
    if (!file.is_open()) return;
    file.close();
}

void CoWorkingSystem::saveMembersToFile() {
    ofstream file("members.txt");
    if (!file.is_open()) return;
    
    for (auto member : members) {
        file << member->getMemberID() << "|"
             << member->getMemberType() << "|"
             << member->getName() << "|"
             << member->getPhone() << "|"
             << member->getJoinDate() << "|"
             << member->getTotalSpent() << endl;
    }
    file.close();
}

void CoWorkingSystem::loadBookingsFromFile() {
    ifstream file("bookings.txt");
    if (!file.is_open()) return;
    file.close();
}

void CoWorkingSystem::saveBookingsToFile() {
    ofstream file("bookings.txt");
    if (!file.is_open()) return;
    
    for (auto& booking : bookings) {
        file << booking.getBookingID() << "|"
             << booking.getSpaceID() << "|"
             << booking.getMemberID() << "|"
             << booking.getDate() << "|"
             << booking.getStartHours() << "|"
             << booking.getDurationHours() << "|"
             << booking.getTotalPrice() << "|"
             << booking.getStatus() << endl;
    }
    file.close();
}