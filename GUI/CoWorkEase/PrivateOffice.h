#ifndef PRIVATE_OFFICE_H
#define PRIVATE_OFFICE_H

#include "Space.h"

class PrivateOffice : public Space{
    private:
        bool hasLock;
        bool hasWindow;
    public:
        PrivateOffice();
        PrivateOffice(int spaceID, string name, double hourlyRate, int capacity, bool hasLock, bool hasWindow);

        bool getHasLock() const;
        bool getHasWindow() const;

        void setHasLock(bool hasLock);
        void setHasWindow(bool hasWindow);

        virtual string getType() const override;
        virtual double calculatePrice(int hours) const override;
        virtual void displayInfo() const override;

        virtual ~PrivateOffice();
};

#endif