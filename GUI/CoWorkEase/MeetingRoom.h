#ifndef MEETING_ROOM_H
#define MEETING_ROOM_H

#include "Space.h"

class MeetingRoom : public Space{
    private:
        bool hasProjector;
        bool hasWhiteBoard;
        int maxSeats;
    public:
        MeetingRoom();
        MeetingRoom(int spaceID, string name, double hourlyRate, int capacity, bool hasProjector, bool hasWhiteBoard, int maxSeats);

        bool getHasProjector() const;
        bool getHasWhiteBoard() const;
        int getMaxSeats() const;

        void setHasProjector(bool projector);
        void setHasWhiteBoard(bool WhiteBoard);
        void setMaxSeats(int seats);

        virtual string getType() const override;
        virtual double calculatePrice(int hours) const override;
        virtual void displayInfo() const override;

        virtual ~MeetingRoom();

};

#endif