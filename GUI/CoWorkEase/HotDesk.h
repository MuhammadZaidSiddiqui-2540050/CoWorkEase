#ifndef HOT_DESK_H
#define HOT_DESK_H

#include "Space.h"

class HotDesk : public Space{
    private:
        bool hasPowerOutlet;
        int deskNumber;
    public:
        HotDesk();
        HotDesk(int spaceID, string name, double hourlyRate, int capacity, bool hasPowerOutlet, int deskNumber);

        bool getHasPowerOutlet() const;
        int getDeskNumber() const;

        void setHasPowerOutlet(bool outlet);
        void setDeskNumber(int number);

        virtual string getType() const override;
        virtual double calculatePrice(int hours) const override;
        virtual void displayInfo() const override;

        virtual ~HotDesk();
};
#endif