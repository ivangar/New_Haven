#include "Player.h"
#include "PlayerDriver.h"
#include "../Resources/Resources.h"
#include "../GameBoard/GBMap.h"
#include "../Deck/HarvestTile.h"
#include <iostream>
#include <string>

using namespace std;

void PlayerDriver::playerDriver(GameBoard* gameBoard)
{
    VillageGameBoard* villageGameBoard1 = new VillageGameBoard();

    auto* building1 = new Building(ResourceTypes::WHEATFIELD, 6);
    auto* building2 = new Building(ResourceTypes::MEADOW, 6);
    auto* building3 = new Building(ResourceTypes::FOREST, 6);
    auto* building4 = new Building(ResourceTypes::QUARRY, 6);
    auto* building5 = new Building(ResourceTypes::WHEATFIELD, 6);
    auto* building6 = new Building(ResourceTypes::MEADOW, 5);
    auto* building7 = new Building(ResourceTypes::FOREST, 4);
    auto* building8 = new Building(ResourceTypes::QUARRY, 3);
    auto* building9 = new Building(ResourceTypes::WHEATFIELD, 2);
    auto* building10 = new Building(ResourceTypes::MEADOW, 1);

    villageGameBoard1->placeBuildingXY(building1, 0, 0, false);
    villageGameBoard1->placeBuildingXY(building2, 0, 1, true);
    villageGameBoard1->placeBuildingXY(building3, 0, 2, true);
    villageGameBoard1->placeBuildingXY(building4, 0, 3, true);
    villageGameBoard1->placeBuildingXY(building5, 0, 4, true);

//    villageGameBoard1->placeBuildingXY(building2, 3, 1, true);
//    villageGameBoard1->placeBuildingXY(building3, 3, 2, true);
//    villageGameBoard1->placeBuildingXY(building4, 3, 3, true);
//    villageGameBoard1->placeBuildingXY(building5, 3, 4, true);

    villageGameBoard1->placeBuildingXY(building6, 1, 0, true);
    villageGameBoard1->placeBuildingXY(building7, 2, 0, true);
    villageGameBoard1->placeBuildingXY(building8, 3, 0, true);
    villageGameBoard1->placeBuildingXY(building9, 4, 0, true);
    villageGameBoard1->placeBuildingXY(building10, 5, 0, true);

    villageGameBoard1->placeBuildingXY(building6, 1, 2, true);
    villageGameBoard1->placeBuildingXY(building7, 2, 2, true);
    villageGameBoard1->placeBuildingXY(building8, 3, 2, true);
    villageGameBoard1->placeBuildingXY(building9, 4, 2, true);
    villageGameBoard1->placeBuildingXY(building10, 5, 2, true);

    // INVALID BUILDING PLACEMENTs
//    villageGameBoard1->placeBuildingXY(building1, 0, 5 , false);
//    villageGameBoard1->placeBuildingXY(building1, 6, 0 , false);

    villageGameBoard1->printVillageGameBoardMap();

    villageGameBoard1->printVillageGameBoardScore();

	Player* player1 = new Player("bob", 40041756, gameBoard);
	Player* player2 = new Player("Ross", 40041758, gameBoard);

	player1->printPlayer();
	player2->printPlayer();

	//Testing players placing harvest tiles on the GameBoard object and calculating resources

	auto* harvestTile1 = new HarvestTile(ResourceTypes::QUARRY, ResourceTypes::WHEATFIELD, ResourceTypes::WHEATFIELD, ResourceTypes::QUARRY);
	auto* harvestTile2 = new HarvestTile(ResourceTypes::WHEATFIELD, ResourceTypes::WHEATFIELD, ResourceTypes::QUARRY, ResourceTypes::FOREST);
	auto* harvestTile3 = new HarvestTile(ResourceTypes::WHEATFIELD, ResourceTypes::QUARRY, ResourceTypes::WHEATFIELD, ResourceTypes::WHEATFIELD);
	auto* harvestTile4 = new HarvestTile(ResourceTypes::WHEATFIELD, ResourceTypes::WHEATFIELD, ResourceTypes::FOREST, ResourceTypes::WHEATFIELD);
	auto* harvestTile5 = new HarvestTile(ResourceTypes::QUARRY, ResourceTypes::FOREST, ResourceTypes::MEADOW, ResourceTypes::FOREST);
	
	player1->placeHarvestTile(harvestTile1, 3, 1);
	gameBoard->getResourceTrack()->printResourceTrack();
	player2->placeHarvestTile(harvestTile3, 2, 2);
	gameBoard->getResourceTrack()->printResourceTrack();
	player2->placeHarvestTile(harvestTile4, 3, 3);
	gameBoard->getResourceTrack()->printResourceTrack();
	player1->placeHarvestTile(harvestTile5, 4, 2);
	gameBoard->getResourceTrack()->printResourceTrack();

	//clean resource track and calculate resources of next move

	gameBoard->getResourceTrack()->resetTrack();
	player1->placeHarvestTile(harvestTile2, 3, 2);

	gameBoard->getResourceTrack()->printResourceTrack();
	gameBoard->printGameBoard();

	std::cout << "\n\n";
	Hand* p1_hand = player1->getHand();
	p1_hand->printHand();

	std::cout << "\n\n";

	player1->setVillageGameBoard(villageGameBoard1);
	player1->calculateResources();
	std::cout << "Player1 score: " << *player1->getVillageBoardScore() << std::endl;

	player2->buildVillage();
}