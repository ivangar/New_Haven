//
// Created by Ivan Garzon on 2020-02-11.
//
#include <iostream>
#include "GBMapDriver.h"
#include "GBMap.h"


void GBMapDriver::gameBoardMapDriver() {

	int players;
	std::cout << "Please enter the number of players (allowed 2, 3 or 4 players): ";
	std::cin >> players;

	while (!std::cin || (players < 2 || players > 4) )
	{
		// user didn't input a number
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// next, request user reinput
		std::cout << "Please enter a valid number: ";
		std::cin >> players;
	}

	GameBoard* gameBoard = new GameBoard(players);

	gameBoard->printGameBoard();

	//Printing Default Game Board tiles
	std::cout << "Printing default Board top-left tile" << std::endl;
	std::vector<int> topLeft = gameBoard->getCornerTilePositions(0);
	auto topLeftTile = gameBoard->getTileXY(topLeft[0], topLeft[1]);
	topLeftTile->printTile();

	std::cout << "Printing default Board bottom-right tile" << std::endl;
	std::vector<int> bottomRight = gameBoard->getCornerTilePositions(3);
	auto bottomRightTile = gameBoard->getTileXY(bottomRight[0], bottomRight[1]);
	bottomRightTile->printTile();

	//Adding tiles to board and test
	std::cout << "Adding a HarvestTile at position:3, 2 " << std::endl;
	auto* harvestTile1 = new HarvestTile(ResourceTypes::MEADOW, ResourceTypes::FOREST, ResourceTypes::WHEATFIELD, ResourceTypes::WHEATFIELD);
	gameBoard->placeTileXY(harvestTile1, 3, 2);

	std::cout << "Adding a HarvestTile at position:3, 3 " << std::endl;
	std::vector<ResourceTypes> res = { ResourceTypes::WHEATFIELD, ResourceTypes::FOREST, ResourceTypes::MEADOW };
	auto harvestTile2 = new HarvestTile(res);
	gameBoard->placeTileXY(harvestTile2, 3, 3);

	std::cout << "Adding a HarvestTile at position:2, 3 " << std::endl;
	std::vector<ResourceTypes> res2 = { ResourceTypes::MEADOW, ResourceTypes::WHEATFIELD };
	auto harvestTile3 = new HarvestTile(res2);
	gameBoard->placeTileXY(harvestTile3, 2, 3);

	std::cout << "Adding a HarvestTile at position:3, 4 " << std::endl;
	std::vector<ResourceTypes> res3 = { ResourceTypes::QUARRY, ResourceTypes::WHEATFIELD, ResourceTypes::QUARRY };
	auto harvestTile4 = new HarvestTile(res3);
	gameBoard->placeTileXY(harvestTile4, 3, 4);

	std::cout << "Adding a HarvestTile at position:4, 3 " << std::endl;
	std::vector<ResourceTypes> res4 = { ResourceTypes::FOREST, ResourceTypes::MEADOW };
	auto harvestTile5 = new HarvestTile(res4);
	gameBoard->placeTileXY(harvestTile5, 4, 3);

	//placing a Tile in an occupied square in the Board
	std::cout << "Adding a HarvestTile at position:4, 3 " << std::endl;
	std::vector<ResourceTypes> res5 = { ResourceTypes::FOREST, ResourceTypes::MEADOW };
	auto harvestTile6 = new HarvestTile(res5);
	gameBoard->placeTileXY(harvestTile6, 4, 3);

	gameBoard->printGameBoard();
}






