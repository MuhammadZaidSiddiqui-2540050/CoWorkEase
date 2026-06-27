#ifndef SPACE_H
#define SPACE_H

#include <string>
using namespace std;

class Space{
    protected:
        int spaceID;
        string name;
        double hourlyRate;
        int capacity;
        bool isBooked;
    public:
        Space();
        Space(int spaceID, string name, double hourlyRate, int capacity);

        int getSpaceID() const;
        string getName() const;
        double getHourlyRate() const;
        int getCapacity() const;
        bool getIsBooked() const;
    
        void setSpaceID(int id);
        void setName(string n);
        void setHourlyRate( double rate);
        void setCapacity(int cap);
        void setIsBooked(bool booked);

        virtual double calculatePrice(int hours) const;
        virtual string getType() const=0;
        virtual void displayInfo() const;

        bool isAvailable(string date, int startHour, int duration);
        void markBooked(bool booked);

        virtual ~Space();
};

#endif