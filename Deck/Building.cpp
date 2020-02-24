//
// Created by Zachary Hynes on 2020-02-09.
//

#include <iostream>
#include <iomanip>
#include <string>
#include "Building.h"


Building::Building() {
//    this->resourceType = null;
    this->cost = nullptr;
    this->isFaceUp = nullptr;
}

Building::Building(ResourceTypes resourceType, int cost) {
    setResourceType(resourceType);
    this->cost = new int(cost);
}

Building::~Building() {
    // TODO: Implement destructor.
}

void Building::printBuilding() {
    ResourceTypes resType = this->resourceType;
    std::string resTypeString;

    switch(resType)
    {
        case WHEATFIELD  : resTypeString = ResourceTypesStrings[0];   break;
        case MEADOW: resTypeString = ResourceTypesStrings[1]; break;
        case FOREST : resTypeString = ResourceTypesStrings[2];  break;
        case QUARRY : resTypeString = ResourceTypesStrings[3];  break;
    }

    if (*getIsFaceUp()) {
        std::cout << std::setfill(' ') << std::setw(6) << resTypeString << "-" << std::setfill('0') << std::setw(2) << *getCost() << "|" ;
    } else {
        std::cout << std::setfill(' ') << std::setw(6) << resTypeString << "-" << "XX|";
    }
}

void Building::debugBuilding() {
    // TODO: Implement debugBuilding() function.
}





