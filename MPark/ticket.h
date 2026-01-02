
#ifndef TICKET_H
#define TICKET_H
#include "Vehicle.h"
#include "parkingSpot.h"
#include <string>
#include <chrono>   
class ticket{
    private:
        int ticketId;
        Vehicle vehicle;
        parkingSpot* spot;
        std::chrono::time_point<std::chrono::system_clock> entryTime;
    public:
        ticket(int ticketId, const Vehicle& vehicle, parkingSpot* spot)
            : ticketId(ticketId), vehicle(vehicle), spot(spot), entryTime(std::chrono::system_clock::now()) {}
        
        int getTicketId() const;
        Vehicle getVehicle() const;
        parkingSpot* getParkingSpot() const;
        std::chrono::time_point<std::chrono::system_clock> getEntryTime() const;
};
#endif