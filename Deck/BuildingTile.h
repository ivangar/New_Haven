//
// Created by Zachary Hynes on 2020-02-07.
//

#ifndef COMP345_NEWHAVENPROJECT_BUILDINGTILE_H
#define COMP345_NEWHAVENPROJECT_BUILDINGTILE_H
#include <string>
#include "../Abstract Classes/AbstractGameTile.h"
#include "Building.h"

class BuildingTile: public AbstractGameTile {
public:
    //=========================
    // CONSTRUCTORS & DESTRUCTORS
    //=========================
    BuildingTile(int cost);

    ~BuildingTile();


    //=========================
    // GETTERS & SETTERS
    //=========================
    int *getBuildingCost() const {
        return buildingCost;
    }

    void setBuildingCost(int *buildingCost) {
        BuildingTile::buildingCost = buildingCost;
    }

    Building *getBuilding() const {
        return building;
    }

    void setBuilding(Building *building) {
        BuildingTile::building = building;
    }


    //=========================
    // FUNCTIONS
    //=========================
    void printTile() override;


private:
    //=========================
    // CLASS PROPERTIES
    //=========================
    int* buildingCost;
    Building* building;
};


#endif //COMP345_NEWHAVENPROJECT_BUILDINGTILE_H
