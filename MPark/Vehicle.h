
#ifndef VEHICLE_H
#define VEHICLE_H

enum class VehicleType {
    Car,
    Truck,
    Motorcycle
};

class Vehicle {
    private:
        int id;
        VehicleType type;
    public:
        Vehicle(int id, VehicleType type) : id(id), type(type) {}
        int getId() const;
        VehicleType getType() const;
};


#endif