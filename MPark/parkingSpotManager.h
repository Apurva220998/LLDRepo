
#ifndef PARKINGSPOTMANAGER_H
#define PARKINGSPOTMANAGER_H

#include "parkingSpot.h"
#include <vector>
#include <memory>

class parkingSpotManager {
    protected:
        std::vector<std::shared_ptr<parkingSpot>> spots;
    public:
      virtual ~parkingSpotManager() = default;

    // Common interface
    virtual parkingSpot* getAvailableSpot() = 0;

};




#endif