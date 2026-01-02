
#include "ticket.h"
#include "Vehicle.h"
#include "parkingSpot.h"
#include <chrono>   


int ticket::getTicketId() const {
    return ticketId;
}
Vehicle ticket::getVehicle() const {
    return vehicle;         
}
parkingSpot* ticket::getParkingSpot() const {
    return spot;
}
std::chrono::time_point<std::chrono::system_clock> ticket::getEntryTime() const {
    return entryTime;
}       
