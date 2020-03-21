#include "ResourcesDriver.h"
#include "Resources.h"
#include <iostream>

void ResourcesDriver::resourcesDriver() {

    /***************************/
    /** Testing Deck **/
    /***************************/

    std::cout << "Lets test the deck object. \n\n";
    Deck *dck = new Deck();

    Hand *hd = new Hand(new int(3));

    std::cout << "\n\n Drawing Building tiles to place into hand.\n\n";
    Buildings* drawBld1 = dck->drawBuildings();
    Buildings* drawBld2 = dck->drawBuildings();
    Buildings* drawBld3 = dck->drawBuildings();

    hd->addBuildingTile(drawBld1);
    hd->addBuildingTile(drawBld2);
    hd->addBuildingTile(drawBld3);

    std::cout << "\n\n Drawing Harvest Tiles to place into hand.\n\n";

    HarvestTile* drawHarvestTile1 = dck->drawHarvest();
    HarvestTile* drawHarvestTile2 = dck->drawHarvest();
    HarvestTile* drawHarvestTile3 = dck->drawHarvest();

    hd->addHarvestTile(drawHarvestTile1);
    hd->addHarvestTile(drawHarvestTile2);
    hd->addHarvestTile(drawHarvestTile3);

    hd->printHand();
    
    std::cout << "\n\n Choosing building tile at position 2 to exchange." << std::endl;

    Buildings* ex_bld = new Buildings();
    ex_bld = hd->exchangeBuildingTile(2); 
    ex_bld->printBuildingTile();

    std::cout << "\n\n Choosing harvest tile at position 1 to exchange." << std::endl;

    HarvestTile* ex_ht = new HarvestTile();
    ex_ht = hd->exchangeHarvestTile(1);
    ex_ht->printTile();

    std::cout << "\n\n This is the current deck:" << std::endl;
    dck->printDeck();

    delete dck;
    dck = nullptr;

    delete hd;
    hd = nullptr;
}