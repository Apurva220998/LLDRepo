
#include "parkingSpot.h"
#include "parkingSpotManager.h"
#include "twoWheelerParkingSpotMngr.h"
#include <iostream>

twoWheelerParkingSpotMngr::twoWheelerParkingSpotMngr() {
    // Initialize with some two-wheeler parking spots
    spots.push_back(std::make_shared<parkingSpot>(1, true, spotType::Compact));
    spots.push_back(std::make_shared<parkingSpot>(2, true, spotType::Compact));
    spots.push_back(std::make_shared<parkingSpot>(3, true, spotType::Compact));
}    
parkingSpot* twoWheelerParkingSpotMngr::getAvailableSpot() {
    for (auto spot : spots) {
        if (spot->getIsAvailable() && spot->getType() == spotType::Compact)
            return spot.get();
    }
    return nullptr;
}   

