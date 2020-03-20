#include "ResourcesDriver.h"
#include "Resources.h"
#include <iostream>

void ResourcesDriver::resourcesDriver() {

    /***************************/
    /** Testing Deck **/
    /***************************/

     std::cout << "Lets test the deck object. \n\n";
     Deck *dck = new Deck();

    std::cout << "This is the current deck: \n\n";
    dck->printDeck();

//    std::cout << "\n\n";
//    Buildings* drawBld = dck->drawBuildings();
//
//    std::cout << "Building tile drawn is: \n";
//    drawBld->printBuildingTile();
//
//    std::cout << "\n\n";
//    HarvestTile* drawHarvestTile = dck->drawHarvest();
//    drawHarvestTile->printTile();
//
//    std::cout << "\n\n";
//
//    std::cout << "This is the current deck: \n\n";
//    dck->printDeck();

}