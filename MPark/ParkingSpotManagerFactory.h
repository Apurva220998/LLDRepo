
#ifndef PARKINGSPOTMANAGERFACTORY_H
#define PARKINGSPOTMANAGERFACTORY_H 
#include "parkingSpotManager.h"
#include "Vehicle.h"
#include <memory>

class parkingSpotManagerFactory {
    public:
         static std::unique_ptr<parkingSpotManager> createManager(const Vehicle& vehicle);
         
};
#endif