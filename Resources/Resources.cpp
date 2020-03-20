#include "Resources.h"
#include "../Deck/HarvestTile.h"
#include "../Enums/CornersTypes.h"
#include "../Enums/ResourceTypes.h"
#include <array>
#include <iostream>
#include <string>
#include <vector>

/**********************/
/** BUILDINGS CLASS **/
/********************/
Buildings::Buildings() : resourceType(nullptr), cost(nullptr) {
    // Initialized through initialization list
}

Buildings::Buildings(ResourceTypes resource, int cost) : resourceType(new ResourceTypes(resource)), cost(new int(cost)) {
    // Initialized through initialization list
}

Buildings::Buildings(const Buildings &copy_bld) {
    std::cout << "Copy constructor\n";
    resourceType = new ResourceTypes();
    cost = new int();

    *resourceType = *copy_bld.resourceType;
    *cost = *copy_bld.cost;
}

Buildings::Buildings(Buildings&& bld) : resourceType(bld.resourceType), cost(bld.cost) {
    std::cout << "Move constructor\n";
    bld.resourceType = nullptr;
    bld.cost = nullptr;
}

Buildings& Buildings::operator=(const Buildings& bld) {

    std::cout << "Copy assignmnent\n";
    if (&bld == this)
        return *this;

    delete resourceType;
    delete cost;

    resourceType = new ResourceTypes();
    cost = new int();

    *resourceType = *bld.resourceType;
    *cost = *bld.cost;

    return *this;
}

Buildings& Buildings::operator=(Buildings&& bld) {
    std::cout << "Move assignmnent\n";
    if (&bld == this)
        return *this;

    delete resourceType;
    delete cost;

    resourceType = bld.resourceType;
    cost = bld.cost;

    bld.resourceType = nullptr;
    bld.cost = nullptr;

    return *this;
}

Buildings::~Buildings() {
    delete resourceType;
    delete cost;
}

void Buildings::printBuildingTile() {
    std::string resStr;

    switch(*this->resourceType) {
        case 0: resStr = "FOREST";
            break;
        case 1: resStr = "MEADOW";
            break;
        case 2: resStr = "QUARRY";
            break;
        case 3: resStr = "WHEATFIELD";
            break;
    }

    std::cout << "Building Tile Type: " << resStr << " Cost: " << *cost << " \n";
}

/*****************/
/** DECK CLASS **/
/***************/
Deck::Deck() {
    std::cout << "Creating a deck...";
    // Create Buildings Deck

    Buildings* bld = nullptr;

    for (int i = 1; i <= NUMBER_OF_BUILDINGS_PER_PRICE; i++) {
        for (int j = 0; j < NUMBER_OF_DIFFERENT_BUILDING_COLOURS; ++j) {
            for (int k = 0; k < NUMBER_OF_BUILDINGS_PER_COLOUR; ++k) {
                bld = new Buildings(static_cast<ResourceTypes>(j), i);
                buildingDeck.push_back(bld);
//                 bld->printBuildingTile();
            }
        }
    }
    std::cout << "\nBuilding deck created. \n Size: " << buildingDeck.size() << ". \n\n";

    // Create Harvest Tile Deck

    HarvestTile* ht = nullptr;

    for (int i = 0; i < NUMBER_OF_HARVEST_TILES; i++) {
        ht = new HarvestTile();
//        ht = new HarvestTile(ResourceTypes::FOREST, ResourceTypes::FOREST,
//                             ResourceTypes::MEADOW, ResourceTypes::QUARRY);                // Create same tile for now
		ht->setRandomHarvestTile();
        harvestDeck.push_back(ht);
        // ht->printHarvestTile();
    }
    std::cout << "\nHarvest deck created. \n Size: " << harvestDeck.size() << ". \n\n";

    std::cout << "Deck created. \n\n";
}

Buildings* Deck::drawBuildings() {
    std::cout << "Drawing a building tile from the deck.\n";

    
    Buildings* drawn_building = std::move(buildingDeck[0]);         // Draw the 'top' Building tile

    // Handle the drawing of this top tile
    buildingDeck[0] = nullptr;    // Dereference the Building removed
    buildingDeck.erase(buildingDeck.begin());          // Erase the first Building 

    return drawn_building;
}

HarvestTile* Deck::drawHarvest() {
    std::cout << "Drawing a harvest tile from the deck.\n";

    HarvestTile* drawn_ht = std::move(harvestDeck[0]);          // Draw the 'top' Harvest tile

    // Handle the consequences of drawing this top tile
    harvestDeck[0] = nullptr;
    harvestDeck.erase(harvestDeck.begin());

    return drawn_ht;
}

void Deck::printDeck() {
    std::cout << "The harvest deck has " << harvestDeck.size() << " tiles remaining.\n";
    std::cout << "The building deck has " << buildingDeck.size() << " tiles remaining.\n";
}

/*****************/
/** HAND CLASS **/
/***************/

Hand::Hand() {
    // Assign a player
    pid = new int(0);

    // Create Buildings Tiles
    Buildings* bld = nullptr;

    for (int i = 0; i < Hand::MAX_BT; i++) {
        int bld_cost = rand() % 6 + 1;
        bld = new Buildings();       // Create the same building tile for now
        buildingTiles.push_back(bld);
        // bld->printBuildingTile();
    }
    // std::cout << "\nBuilding tiles created.\n You have " << buildingTiles.size() << " building tiles. \n\n";

    // Create Harvest Tiles
    HarvestTile* ht = nullptr;

    for (int i = 0; i < Hand::MAX_HT; i++) {
        ht = new HarvestTile();                // Create same tile for now
        harvestTiles.push_back(ht);
        // ht->printHarvestTile();
    }
    // std::cout << "\nHarvest tiles created.\n You have  " << harvestTiles.size() << " harvest tiles. \n\n";

    // std::cout << "Hand created. \n\n";
}

Hand::Hand(int* player) {
    // Assign a player (through id for now)
    this->pid = player;

    // Display that the hand has been created for the player and that they have no building or harvest tiles yet.
    // std::cout << "Hand created. \n\n";
    // std::cout << "You have " << buildingTiles.size() << " building tiles and " << harvestTiles.size() << " harvest tiles. \n\n";
}

Hand::~Hand() {
    delete pid;
}

void exchange() {
    // TODO: Implement the exchange function.
}

void Hand::printHand() {
    std::vector<HarvestTile*> ht_hand = this->getHarvestTiles();
    std::vector<Buildings*> bld_hand = this->getBuildingTiles();

    std::cout << "Printing player " << *this->pid << "'s hand.\n";

    if (this->harvestTiles.size() == 0 && this->buildingTiles.size() == 0) {
        std::cout << "Your hand is empty. Please draw from the deck.";
    } else {
        std::cout << "Your building tiles are: \n";

        for (auto bt : bld_hand) {
        bt->printBuildingTile();
        }

        std::cout << "\n\n";
        std::cout << "Your harvest tiles are: \n";

        for (auto ht : ht_hand) {
            ht->printTile();
        }
    }
}