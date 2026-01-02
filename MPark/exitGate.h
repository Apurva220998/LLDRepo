
#ifndef EXITGATE_H
#define EXITGATE_H
#include "ticket.h"
#include "parkingSpot.h"
#include <chrono>
#include "Vehicle.h"
class exitGate{
    public:
        double releaseSpot(ticket* tkt);
};
#endif