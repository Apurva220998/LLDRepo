
#ifndef FOUR_WHEELER_PARKING_SPOT_MNGR_H
#define FOUR_WHEELER_PARKING_SPOT_MNGR_H
#include "parkingSpot.h"
#include "parkingSpotManager.h" 
class fourWheelerParkingSpotMngr : public parkingSpotManager {
    public:
        fourWheelerParkingSpotMngr();
        parkingSpot* getAvailableSpot() override;
};
#endif
