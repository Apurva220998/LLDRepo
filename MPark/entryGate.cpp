
#include "entryGate.h"
#include "parkingSpot.h"
#include "ticket.h"
#include <chrono>

ticket* entryGate::assignSpot(const Vehicle& vehicle) {
    static int ticketCounter = 0;
    auto manager = spotManagerFactory.createManager(vehicle);
    parkingSpot* spot = manager->getAvailableSpot();
    if(!spot) return nullptr; // No spot available
    spot->setIsAvailable(false); // Mark spot as occupied
    return new ticket(
        ++ticketCounter,           
        vehicle,
        spot
    );
    
}
