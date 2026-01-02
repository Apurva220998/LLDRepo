
#ifndef TWO_WHEELER_PARKING_SPOT_MNGR_H 
#define TWO_WHEELER_PARKING_SPOT_MNGR_H

#include "parkingSpot.h"
#include "parkingSpotManager.h"

class twoWheelerParkingSpotMngr : public parkingSpotManager {
    public:
        twoWheelerParkingSpotMngr();
        parkingSpot* getAvailableSpot() override;
};
#endif