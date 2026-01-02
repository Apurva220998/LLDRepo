
#ifndef PARKINGSPOT_H
#define PARKINGSPOT_H
enum class spotType {
    Compact,
    Large
};
class parkingSpot {

    int spotId;
    bool isAvailable;
    spotType type;
    public:
        parkingSpot(int spotId, bool isAvailable, spotType type);
        int getSpotId() const;
        bool getIsAvailable() const;
        void setIsAvailable(bool availability);
        spotType getType() const;
};
#endif