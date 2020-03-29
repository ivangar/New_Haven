#pragma once
#include "../Deck/HarvestTile.h"
#include "../Enums/CornersTypes.h"
#include "../Enums/ResourceTypes.h"
#include <iostream>
#include <string>
#include <vector>

//enum ResourceTypes { FOREST, MEADOW, QUARRY, WHEATFIELD };
/** RESOURCE TYPES HELP FREE FUNCTION **/
inline std::string resourceTypeString(ResourceTypes resource) {
    std::string resource_string;

    switch(resource) {
        case 0: resource_string = "FOREST";
            break;
        case 1: resource_string = "MEADOW";
            break;
        case 2: resource_string = "QUARRY";
            break;
        case 3: resource_string = "WHEATFIELD";
            break;
    }

    return resource_string;
};

static const int NUMBER_OF_BUILDINGS_PER_PRICE = 6;
static const int NUMBER_OF_BUILDINGS_PER_COLOUR = 6;
static const int NUMBER_OF_DIFFERENT_BUILDING_COLOURS = 4;

static const int NUMBER_OF_HARVEST_TILES = 60;

class Buildings {
public:
    /** Constructors & Destructors **/
    Buildings();
    Buildings(ResourceTypes resource, int cost);
    Buildings(const Buildings& copy_bld);       // Copy Constructor
    Buildings(Buildings&& bld);                 // Move Constructor
    ~Buildings();

    /** Operator Overloads **/
    Buildings& operator=(const Buildings& bld);
    Buildings& operator=(Buildings&& bld);

    /** Getters & Setters **/
    inline void setCost(int cst) {
        *cost = cst;
    }

    int* getCost(){
        return cost;
    }

    void setResourceType(enum ResourceTypes* type) {
        this->resourceType = type;
    }

    ResourceTypes* getResourceType() {
        return resourceType;
    }

    /** Functionality **/
    void printBuildingTile();

private:
    /** Attributes **/
    ResourceTypes* resourceType;
    int* cost;
};

class Deck {
public:
    /** Constructors & Destructors **/
    Deck();

    /** Getters & Setters **/
    std::vector<Buildings*> getBuildingDeck() {
        std::cout << "Succesfully got Building deck.\n";
        return buildingDeck;
    };

    std::vector<HarvestTile*> getHarvestDeck() {
        std::cout << "Succesfully got Harvest deck.\n";
        return harvestDeck;
    };

    /** Functionality **/
    Buildings* drawBuildings();
    HarvestTile* drawHarvest();
    void printDeck();

private:
    const int HARVEST_DECK_SIZE = 60;
    const int BUILDING_DECK_SIZE = 144;
    std::vector<Buildings*> buildingDeck;
    std::vector<HarvestTile*> harvestDeck;
    
    // Method to create default Building deck
    void createBuildingDeck();
    // Method to create default Harvest Tile deck
    void createHarvestDeck();
};

class Hand {
public:
    /** Constructors & Destructors **/
    Hand();
    Hand(int* pid);
    Hand(const Hand& copy_hand);        // Copy Constructor
    ~Hand();

    /** Getters & Setters **/
    void setPlayer(int* player) {
        this->pid = player;
    };

    int* getPlayer() {
        return pid;
    }

    std::vector<Buildings*> getBuildingTiles() {
        //std::cout << "Succesfully got Building tiles.\n";
        return buildingTiles;
    };

    std::vector<HarvestTile*> getHarvestTiles() {
        //std::cout << "Succesfully got Harvest tiles.\n";
        return harvestTiles;
    };

    /** Functionality **/
    void addBuildingTile(Buildings* bld) {
        buildingTiles.push_back(bld);
    };

    void addHarvestTile(HarvestTile* ht) {
        harvestTiles.push_back(ht);
    };

	void addShipmentTile(HarvestTile* ht) {
		shipmentTile = ht;
	}
	
	HarvestTile* getShipmentTile() {
		return shipmentTile;
	};

    Buildings* exchangeBuildingTile(int pos);
    HarvestTile* exchangeHarvestTile(int pos);
	HarvestTile* exchangeShipmentTile();
    void printHand();

private:
    const int MAX_BT = 6;
    const int MAX_HT = 2;
    int* pid;
    std::vector<Buildings*> buildingTiles;
    std::vector<HarvestTile*> harvestTiles;
	HarvestTile* shipmentTile;
};