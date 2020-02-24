//
// Created by Zachary Hynes on 2020-02-09.
//

#ifndef COMP345_NEWHAVENPROJECT_BUILDING_H
#define COMP345_NEWHAVENPROJECT_BUILDING_H
#include "../Enums/ResourceTypes.h"
#include "../Enums/ResourceTypes.h"

class Building {
public:
    //=========================
    // CONSTRUCTORS & DESTRUCTORS
    //=========================
    Building();

    Building(ResourceTypes resourceType, int cost);

    ~Building();

    //=========================
    // GETTERS & SETTERS
    //=========================
    ResourceTypes getResourceType() const {
        return resourceType;
    }

    void setResourceType(ResourceTypes resourceType) {
        this->resourceType = resourceType;
    }

    int *getCost() const {
        return cost;
    }

    void setCost(int *cost) {
        Building::cost = cost;
    }

    bool *getIsFaceUp() const {
        return isFaceUp;
    }

    void setIsFaceUp(bool isFaceUp) {
        Building::isFaceUp = new bool(isFaceUp);
    }


    //=========================
    // FUNCTIONS
    //=========================
    virtual void printBuilding();

    virtual void debugBuilding();


private:
    //=========================
    // CLASS PROPERTIES
    //=========================
    ResourceTypes resourceType;
    int* cost;
    bool* isFaceUp;
};


#endif //COMP345_NEWHAVENPROJECT_BUILDING_H
