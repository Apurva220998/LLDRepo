
#include "parkingSpot.h"

parkingSpot::parkingSpot(int spotId, bool isAvailable, spotType type)
    : spotId(spotId), isAvailable(isAvailable), type(type) {}

int parkingSpot::getSpotId() const {
    return spotId;
}
bool parkingSpot::getIsAvailable() const {
    return isAvailable;                        
}
spotType parkingSpot::getType() const {
    return type;
}           
void parkingSpot::setIsAvailable(bool availability) {
    isAvailable = availability;
}
