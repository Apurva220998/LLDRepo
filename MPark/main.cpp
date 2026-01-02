
#include "parkingSpot.h"
#include "parkingSpotManager.h"     
#include "fourWheelerParkingSpotMngr.h"
#include "twoWheelerParkingSpotMngr.h"
#include "entryGate.h"
#include "exitGate.h"
#include "Vehicle.h"
#include "ticket.h"
#include "ParkingSpotManagerFactory.h"
#include "parkingSpotManager.h"
#include <iostream>

int main(){
    entryGate egate;
    exitGate xgate;

    Vehicle car1(1, VehicleType::Car);
    Vehicle bike1(2, VehicleType::Motorcycle);

    ticket* tkt1 = egate.assignSpot(car1);
    if(tkt1) {
        std::cout << "Car parked with Ticket ID: " << tkt1->getTicketId() << std::endl;
    } else {
        std::cout << "No parking spot available for Car." << std::endl;
    }

    ticket* tkt2 = egate.assignSpot(bike1);
    if(tkt2) {
        std::cout << "Motorcycle parked with Ticket ID: " << tkt2->getTicketId() << std::endl;
    } else {
        std::cout << "No parking spot available for Motorcycle." << std::endl;
    }

    // Simulate exit after some time
    double fee1 = xgate.releaseSpot(tkt1);
    std::cout << "Car exited. Parking Fee: " << fee1 << std::endl;

    double fee2 = xgate.releaseSpot(tkt2);
    std::cout << "Motorcycle exited. Parking Fee: " << fee2 << std::endl;

    return 0;
}