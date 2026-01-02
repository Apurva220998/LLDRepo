
#include "ParkingSpotManagerFactory.h"
#include "twoWheelerParkingSpotMngr.h"
#include "fourWheelerParkingSpotMngr.h"
#include <memory>   
#include "Vehicle.h"

std::unique_ptr<parkingSpotManager> parkingSpotManagerFactory::createManager(const Vehicle& vehicle) {
    switch (vehicle.getType()) {
        case VehicleType::Motorcycle:
            return std::make_unique<twoWheelerParkingSpotMngr>();
        case VehicleType::Car:
            return std::make_unique<fourWheelerParkingSpotMngr>();
        default:
            return nullptr;
    }
}