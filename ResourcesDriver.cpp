#include "Resources.cpp"
#include <array>
#include <iostream>
#include <vector>

int main() {
    std::cout << "We got movement \n";

    /***************************/
    /** Testing Buildings **/
    /***************************/

    // ResourceTypes rt = WHEATFIELD;
    // Buildings* bd;
    // int* newCost = new int(6);
    // bd->setCost(newCost);
    // int* b_cost = bd->getCost();
    // int &bcost = *b_cost;

    // bd->setCost(new int(3));
    // int* nb_cost = bd->getCost();
    // int &nbcost = *nb_cost;

    // bd->setResourceType(new ResourceTypes(ResourceTypes::QUARRY));
    // ResourceTypes* bd_type = bd->getResourceType();
    // ResourceTypes &bdtype = *bd_type;

    // std::cout << "type: " << bdtype << "\n";
    // std::cout << "bd cost: " << nbcost << "\n\n";

    // Buildings bd2(ResourceTypes::MEADOW,4);

    // ResourceTypes* bd2_type = bd2.getResourceType();
    // ResourceTypes bd2type = *bd2_type;

    // std::cout << "type: " << bd2type << "\n\n";
    // bd->printBuildingTile();
    // std::cout << std::endl;
    // bd2.printBuildingTile();

    /***************************/
    /** Testing Harvest Tile **/
    /***************************/
    // std::cout << "Testing Harvest tiles !! \n\n" ;

    // HarvestTile* ht = new HarvestTile();
    // ht->setCornerResource(Corners::TOP_LEFT, ResourceTypes::WHEATFIELD);

    // ht->printHarvestTile();

    // std::cout << "Lets make a custom harvest tile. \n\n";
    // HarvestTile ht2(QUARRY, QUARRY, WHEATFIELD, FOREST);

    // ht2.printHarvestTile();

    // std::cout << "Switched top right resource to Meadow. \n\n\n";

    // ht2.setCornerResource(Corners::TOP_RIGHT, ResourceTypes::MEADOW);

    // ht->printHarvestTile();
    // ht2.printHarvestTile();

    /***************************/
    /** Testing Deck **/
    /***************************/

    std::cout << "Lets test the deck object. \n\n";
    Deck dck;

    // std::vector<Buildings*> dck_bld = dck->getBuildingDeck();
    // std::cout << dck_bld.size() << '\n';
    // std::cout << std::endl;
    // std::vector<HarvestTile*> dck_ht = dck->getHarvestDeck();
    // std::cout << dck_ht.size() << '\n';

    std::cout << std::endl;
    std::cout << std::endl;
    
    // Buildings* draw_bld = new Buildings();
    // draw_bld = dck->draw(dck_bld);

    Buildings b1(ResourceTypes::MEADOW,4);
    b1.printBuildingTile();
    std::cout << std::endl;

    Buildings b2 = b1;   //copy cons
    Buildings b3 = std::move(b1);  //move cons

    //b1.printBuildingTile();
    b2.printBuildingTile();
    b3.printBuildingTile();

    b2 = b3; //copy assign
    b3 = std::move(b2);

    //b1.printBuildingTile();
    //b2.printBuildingTile();
    b3.printBuildingTile();

    
    //b2.setCost(6);
    std::cout << std::endl;
    std::cout << std::endl;
    //b1.setCost(1);
    //b1.printBuildingTile();
    //b2.printBuildingTile();

    return 0;
}