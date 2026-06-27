#ifndef BOOKING_H
#define BOOKING_H

#include <string>
using namespace std;

class Booking{
    private:
        int bookingID;
        int spaceID;
        int memberID;
        string date;
        int startHours;
        int durationHours;
        double totalPrice;
        string status;
        bool refundIssued;
        string cancellationDate;
    public:
        Booking();
        Booking(int bID, int sID, int mID, string date, int startHours, int durationHours, double totalPrice);  

        int getBookingID() const; 
        int getSpaceID() const;
        int getMemberID() const;
        string getDate() const;
        int getStartHours() const;
        int getDurationHours() const;
        double getTotalPrice() const;
        string getStatus() const;
        bool getRefundIssued() const;
        string getCancellationDate() const;

        void setStatus(string status);
        void setRefundIssued(bool issued);
        void setCancellationDate(string date);
        void setTotalPrice(double price);

        void displayInfo() const;
        bool conflictsWith(const Booking& other) const;
};

#endif