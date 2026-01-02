
#include "exitGate.h"
#include "ticket.h"
#include "parkingSpot.h"
#include <chrono>
#include "Vehicle.h"

double exitGate::releaseSpot(ticket* tkt) {
    auto exitTime = std::chrono::system_clock::now();
    auto entryTime = tkt->getEntryTime();
    std::chrono::duration<double> duration = exitTime - entryTime;
    double hoursParked = duration.count() / 3600.0; // Convert seconds to hours

    // Simple fee calculation: $2 per hour for cars, $1 per hour for motorcycles
    double ratePerHour = 0.0;
    switch (tkt->getVehicle().getType()) {
        case VehicleType::Car:
            ratePerHour = 2.0;
            break;
        case VehicleType::Motorcycle:
            ratePerHour = 1.0;
            break;
        default:
            ratePerHour = 2.0; // Default rate
            break;
    }

    double totalFee = hoursParked * ratePerHour;

    // Free up the parking spot
    parkingSpot* spot = tkt->getParkingSpot();
    spot->setIsAvailable(true);

    // Clean up ticket
    delete tkt;

    return totalFee;
}