#include "Resources.h"
#include <array>
#include <iostream>
#include <vector>

/**********************/
/** BUILDINGS CLASS **/
/********************/
Buildings::Buildings() : resourceType(nullptr), cost(nullptr) {
    //this->resourceType = nullptr;
    //this->cost = nullptr;
    //std::cout << "Building Made. \n";
}

Buildings::Buildings(ResourceTypes resource, int cost) : resourceType(new ResourceTypes(resource)), cost(new int(cost)) {
    //this.resourceType = new ResourceTypes(resource);
    //this.cost = new int(cost);
    //std::cout << "Custom building made. \n";
}

Buildings::Buildings(const Buildings &old_bld) {
    std::cout << "Copy constructor\n";
    resourceType = new ResourceTypes();
    cost = new int();

    *resourceType = *old_bld.resourceType;
    *cost = *old_bld.cost;
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

    std::cout << "Building Tile \n";
    std::cout << "Type: " << resStr << " Cost: " << *cost << " @ " << cost << " \n";
}

/*************************/
/** HARVEST TILE CLASS **/
/***********************/
HarvestTile::HarvestTile() {
    int corners = HarvestTile::NUM_CORNERS;
    res_array = new ResourceTypes[corners]();       // res_array created with null pointers
    
    //std::cout << "Created default harvest tile. \n\n";
}

HarvestTile::HarvestTile(ResourceTypes r1, ResourceTypes r2, ResourceTypes r3, ResourceTypes r4) {
    int corners = HarvestTile::NUM_CORNERS;
    res_array = new ResourceTypes[corners];

   this->setCornerResource(Corners::TOP_LEFT, r1);
   this->setCornerResource(Corners::TOP_RIGHT, r2);
   this->setCornerResource(Corners::BOTTOM_LEFT, r3);
   this->setCornerResource(Corners::BOTTOM_RIGHT, r4);

   //std::cout << "Created custom tile. \n\n"; 
}

HarvestTile::HarvestTile(HarvestTile&& ht) : res_array(ht.res_array) {
	ht.res_array = nullptr;
}

HarvestTile::~HarvestTile() {
    delete [] res_array;
}

HarvestTile& HarvestTile::operator=(HarvestTile&& ht) {
    if (&ht == this)
        return *this;

    delete [] res_array;

    res_array = ht.res_array;
    ht.res_array = nullptr;

    return *this;
}

void HarvestTile::printHarvestTile() {

    ResourceTypes r1 = this->getResourceType(Corners::TOP_LEFT);
    ResourceTypes r2 = this->getResourceType(Corners::TOP_RIGHT);
    ResourceTypes r3 = this->getResourceType(Corners::BOTTOM_LEFT);
    ResourceTypes r4 = this->getResourceType(Corners::BOTTOM_RIGHT);

    std::string r1_strg = resourceTypeString(r1);
    std::string r2_strg = resourceTypeString(r2);
    std::string r3_strg = resourceTypeString(r3);
    std::string r4_strg = resourceTypeString(r4);

    std::cout << "Harvest Tile \n";
    std::cout << "============= \n";
    std::cout << "Resource Type of Top left corner: " << r1_strg << ".\n";
    std::cout << "Resource Type of Top right corner: " << r2_strg << ".\n";
    std::cout << "Resource Type of Bottom left corner: " << r3_strg << ".\n";
    std::cout << "Resource Type of Bottom right corner: " << r4_strg << ".\n\n";

}

/*****************/
/** DECK CLASS **/
/***************/
Deck::Deck() {
    // Create Building Deck

    Buildings* bld = nullptr;

    for (int i = 0; i < 6; i++) {
        bld = new Buildings();
        buildingDeck.push_back(bld);
    }
    std::cout << "Building deck created. \n Size: " << buildingDeck.size() << ". \n\n";

    // Create Harvest Tile Deck

    HarvestTile* ht = nullptr;

    for (int i = 0; i < 10; i++) {
        ht = new HarvestTile();
        harvestDeck.push_back(ht);
    }
    std::cout << "Harvest deck created. \n Size: " << harvestDeck.size() << ". \n\n";

    std::cout << "Default deck created. \n\n";
}

// Deck::Deck(const Deck& dck2) {
//     // Copy building deck
    
//     Buildings* blds = nullptr;


// }

Deck::~Deck() {
    for(auto bld : buildingDeck) {
        delete bld;
    }
    buildingDeck.clear();

    for(auto ht : harvestDeck) {
        delete ht;
    }
    harvestDeck.clear();
}

Buildings* Deck::draw(std::vector<Buildings*> bd) {
    Buildings* buildingTile = new Buildings();

    buildingTile = bd.front();
    //buildingTile->printBuildingTile();
    // this->buildingDeck.erase(bd.begin());

    return buildingTile;
}

HarvestTile* Deck::draw(std::vector<HarvestTile*> hd) {
    HarvestTile* harvestTile  = new HarvestTile();

    harvestTile = hd.front();
    this->harvestDeck.erase(hd.begin());
    
    return harvestTile;
}