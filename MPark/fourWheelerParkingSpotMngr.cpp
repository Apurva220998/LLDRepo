
#include "parkingSpot.h"
#include "parkingSpotManager.h"
#include "fourWheelerParkingSpotMngr.h"
#include <iostream>  
   
fourWheelerParkingSpotMngr::fourWheelerParkingSpotMngr() {
    // Initialize with some four-wheeler parking spots
    spots.push_back(std::make_shared<parkingSpot>(1, true, spotType::Large));
    spots.push_back(std::make_shared<parkingSpot>(2, true, spotType::Large));
    spots.push_back(std::make_shared<parkingSpot>(3, true, spotType::Large));
}    
parkingSpot* fourWheelerParkingSpotMngr::getAvailableSpot() {
    for (auto spot : spots) {
        if (spot->getIsAvailable() && spot->getType() == spotType::Large)
            return spot.get();
    }
    return nullptr;
}       