
#ifndef ENTRYGATE_H
#define ENTRYGATE_H

#include "ParkingSpotManagerFactory.h"
#include "Vehicle.h"
#include "ticket.h"
#include <chrono>

class entryGate{
    parkingSpotManagerFactory spotManagerFactory;
    public:
        ticket* assignSpot(const Vehicle& vehicle);

};

#endif