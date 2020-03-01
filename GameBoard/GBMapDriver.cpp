//
// Created by Ivan Garzon on 2020-02-11.
//
#include <iostream>
#include <string>
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

	std::cout << "Adding a HarvestTile at position:3, 1 " << std::endl;
	auto* harvestTile1 = new HarvestTile(ResourceTypes::QUARRY, ResourceTypes::WHEATFIELD, ResourceTypes::WHEATFIELD, ResourceTypes::QUARRY);
	gameBoard->placeTileXY(harvestTile1, 3, 1);

	std::cout << "Adding a HarvestTile at position:3, 2 " << std::endl;
	auto harvestTile2 = new HarvestTile(ResourceTypes::WHEATFIELD, ResourceTypes::WHEATFIELD, ResourceTypes::QUARRY, ResourceTypes::FOREST);
	gameBoard->placeTileXY(harvestTile2, 3, 2);

	std::cout << "Adding a HarvestTile at position:2, 2 " << std::endl;
	auto harvestTile3 = new HarvestTile(ResourceTypes::WHEATFIELD, ResourceTypes::QUARRY, ResourceTypes::WHEATFIELD, ResourceTypes::WHEATFIELD);
	gameBoard->placeTileXY(harvestTile3, 2, 2);

	std::cout << "Adding a HarvestTile at position:3, 3 " << std::endl;
	auto harvestTile4 = new HarvestTile(ResourceTypes::WHEATFIELD, ResourceTypes::WHEATFIELD, ResourceTypes::FOREST, ResourceTypes::WHEATFIELD);
	gameBoard->placeTileXY(harvestTile4, 3, 3);

	std::cout << "Adding a HarvestTile at position:4, 2 " << std::endl;
	auto harvestTile5 = new HarvestTile(ResourceTypes::QUARRY, ResourceTypes::FOREST, ResourceTypes::MEADOW, ResourceTypes::FOREST);
	gameBoard->placeTileXY(harvestTile5, 4, 2);

	//placing a Tile in an occupied square in the Board
	
	std::cout << "Adding a HarvestTile at position:4, 2 " << std::endl;
	std::vector<ResourceTypes> res5 = { ResourceTypes::FOREST, ResourceTypes::MEADOW };
	auto harvestTile6 = new HarvestTile(res5);
	gameBoard->placeTileXY(harvestTile6, 4, 2);

	gameBoard->printGameBoard();

	std::cout << "\nCalculating gathered resources of Tile at position:3, 2" << std::endl;

	gameBoard->calculateResources(harvestTile2, 3, 2);
	gameBoard->getCollectedResources();
}






