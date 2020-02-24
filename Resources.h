#pragma once
#include <array>
#include <iostream>
#include <vector>
#include "Enums/CornersTypes.h"

enum ResourceTypes { FOREST, MEADOW, QUARRY, WHEATFIELD };

class Buildings {
    public:
        /** Constructors & Destructors **/
        Buildings();
        Buildings(ResourceTypes resource, int cost);
        Buildings(const Buildings& copy_bld);
        Buildings(Buildings&& bld);
        ~Buildings();

        Buildings& operator=(const Buildings& bld);
        Buildings& operator=(Buildings&& bld);

        /** Getters & Setters **/
        inline void setCost(int cst) {
            *cost = cst;
        }

        int* const getCost() {
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

class HarvestTile {
    public:
        /** Constructors & Destructors **/
        HarvestTile();
        HarvestTile(ResourceTypes r1, ResourceTypes r2, ResourceTypes r3, ResourceTypes r4);
        HarvestTile(HarvestTile&& ht); 
        ~HarvestTile();

        HarvestTile& operator=(HarvestTile&& ht);

        /** Getters & Setters **/
        void setCornerResource(enum Corners pos, enum ResourceTypes resourceType) {
            this->res_array[pos] = resourceType;
        }

        ResourceTypes const& getResourceType(enum Corners pos) {
            return res_array[pos];
        } 

        /** Functionality **/
        void printHarvestTile();

    private:
        /** Attributes **/
        const int NUM_CORNERS = 4;
        ResourceTypes* res_array;

};

class Deck {
    public:
        /** Constructors & Destructors **/
        Deck();
        Deck(const Deck& copy_dck);
        ~Deck();

        /** Getters & Setters **/
        std::vector<Buildings*> const& getBuildingDeck() {
            std::cout << "Succesfully got Building deck.\n";
            return buildingDeck;
        };

        std::vector<HarvestTile*> const& getHarvestDeck() {
            std::cout << "Succesfully got Harvest deck.\n";
            return harvestDeck;
        };

        /** Functionality **/
        Buildings* draw(std::vector<Buildings*> buildingDeck);
        HarvestTile* draw(std::vector<HarvestTile*> harvestDeck);
        
    private:
        const int HARVEST_DECK_SIZE = 60;
        const int BUILDING_DECK_SIZE = 144;
        std::vector<Buildings*> buildingDeck;
        std::vector<HarvestTile*> harvestDeck;
};

class Hand {
    public:
        /** Constructors & Destructors **/
        Hand();
        ~Hand();

        /** Getters & Setters **/

        /** Functionality **/
        //exchange();
        
    private:
        Buildings* buildingTiles;
        HarvestTile* harvestTiles;
        int* player;

};

/** RESOURCE TYPES HELP FUNCTION **/
 std::string resourceTypeString(ResourceTypes resource) {
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