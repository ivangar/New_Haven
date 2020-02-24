//
// Created by Ivan Garzon on 2020-02-10.
//

#include <stdio.h>
#include <iostream>
#include <iomanip> 
#include <vector>
#include "GBMap.h"
#include "../Deck/HarvestTile.h"
#include "../Enums/ResourceTypes.h"

GameBoard::GameBoard(int players) {
	this->players = new int(players);
	this->setRows_Columns();

	Graph *g = new Graph(*this->mapRows, *this->mapColumns);
	this->setGameBoard(g);
	
	//Get game board and test
	auto gameBoardGraph = this->getGameBoard();

	// Set harvest tiles in the nodes
	for (int i = 0; i < *this->mapRows; ++i) {

		for (int j = 0; j < *this->mapColumns; ++j) {

			auto emptyHarvestTile = new HarvestTile();
			gameBoardGraph->getNodeAtCoordinatesXY(i, j)->setGameTile(emptyHarvestTile);
		}
	}

	//Set 4 corner positions
	setcornerTilePositions();

	//Setting a default harvest tile to put on game board
	std::vector<ResourceTypes> res = { ResourceTypes::WHEATFIELD, ResourceTypes::FOREST };
	auto defaultHarvestTile = new HarvestTile(res);

	std::vector<ResourceTypes> res2 = { ResourceTypes::MEADOW, ResourceTypes::FOREST, ResourceTypes::WHEATFIELD };
	auto secondHarvestTile = new HarvestTile(res2);

	//Set the corner Harvest Tiles
	placeTileXY(defaultHarvestTile, getCornerTilePositions(0)[0], getCornerTilePositions(0)[1]);
	placeTileXY(secondHarvestTile, getCornerTilePositions(1)[0], getCornerTilePositions(1)[1]);
	placeTileXY(secondHarvestTile, getCornerTilePositions(2)[0], getCornerTilePositions(2)[1]);
	placeTileXY(defaultHarvestTile, getCornerTilePositions(3)[0], getCornerTilePositions(3)[1]);

}

GameBoard::~GameBoard() {
	delete mapRows;
	delete mapColumns;
	delete players;
	delete gameBoardGraph;
}

void GameBoard::placeTileXY(HarvestTile* tile, int rowNumber, int columnNumber) {
	if (rowNumber >= *mapRows || columnNumber >= *mapColumns) {
		std::cout << "ERROR: Row number or Column number exceeds game board size." << std::endl;
		return;
	}

	auto targetHarvestTile = getTileXY(rowNumber, columnNumber);

	if (targetHarvestTile->getResources() != nullptr) {
		std::cout << "ERROR: This position is already occupied by a Harvest Tile. Please choose other position" << std::endl;
		return;
	}

	gameBoardGraph->getNodeAtCoordinatesXY(rowNumber, columnNumber)->setGameTile(tile);
}

HarvestTile* GameBoard::getTileXY(int rowNumber, int columnNumber) {
	if (rowNumber >= *mapRows || columnNumber >= *mapColumns) {
		std::cout << "ERROR: Row number or Column number exceeds game board size." << std::endl;
		return nullptr;
	}

	AbstractGameTile* targetTile = gameBoardGraph->getNodeAtCoordinatesXY(rowNumber, columnNumber)->getGameTile();
	HarvestTile* targetHarvestTile = dynamic_cast<HarvestTile*>(targetTile);
	return targetHarvestTile;
}

void GameBoard::printGameBoard() {

	std::cout << "GAME BOARD SIDE A" << std::endl;

	for (int col = 0; col < *mapColumns; ++col) {
		std::cout << "      " << col << "       ";
	}
	std::cout << std::endl;

	for (int i = 0; i < *mapRows; ++i) {
		printTopRow(i);
		printBottomRow(i);
	}
}

void GameBoard::printTopRow(int row) {
	
	if (*this->players == 4 && (row == 0 || row == 6) ) {
		std::cout << "              ";
		for (int i = 1; i < (*mapColumns-1); ++i) {
			std::cout << "  ---------   ";
		}
		std::cout << std::endl;
		std::cout << "              ";
		for (int j = 1; j < (*mapColumns-1); ++j) {
			auto harvestTile = getTileXY(row, j);
			harvestTile->printTopResources();
		}
		std::cout << std::endl;
		std::cout << row << "             ";
		for (int k = 1; k < (*mapColumns-1); ++k) {
			std::cout << "  |       |   ";
		}
		std::cout << std::endl;
	}

	else {
		for (int i = 0; i < *mapColumns; ++i) {
			std::cout << "  ---------   ";
		}
		std::cout << std::endl;

		for (int j = 0; j < *mapColumns; ++j) {
			auto harvestTile = getTileXY(row, j);
			harvestTile->printTopResources();
		}

		std::cout << std::endl;
		std::cout << row << " |       |   ";
		for (int k = 1; k < *mapColumns; ++k) {
			std::cout << "  |       |   ";
		}
		std::cout << std::endl;
	}

}

void GameBoard::printBottomRow(int row){

	if (*this->players == 4 && (row == 0 || row == 6)) {
		std::cout << "              ";
		for (int i = 1; i < (*mapColumns-1); ++i) {
			auto harvestTile = getTileXY(row, i);
			harvestTile->printBottomResources();
		}
		std::cout << std::endl;
		std::cout << "              ";
		for (int j = 1; j < (*mapColumns-1); ++j) {
			std::cout << "  ---------   ";
		}
		std::cout << std::endl;
	}

	else {
		for (int i = 0; i < *mapColumns; ++i) {
			auto harvestTile = getTileXY(row, i);
			harvestTile->printBottomResources();
		}

		std::cout << std::endl;
		for (int j = 0; j < *mapColumns; ++j) {
			std::cout << "  ---------   ";
		}
		std::cout << std::endl;
	}
}


void GameBoard::setcornerTilePositions() {
	this->cornerTilePositions.resize(4);

	if (*this->players == 2) {
		this->cornerTilePositions[0] = { 0 , 0 };
		this->cornerTilePositions[1] = { 0 , 4 };
		this->cornerTilePositions[2] = { 4 , 0 };
		this->cornerTilePositions[3] = { 4 , 4 };
	}

	else if (*this->players == 3) {
		this->cornerTilePositions[0] = { 1 , 0 };
		this->cornerTilePositions[1] = { 1 , 4 };
		this->cornerTilePositions[2] = { 5 , 0 };
		this->cornerTilePositions[3] = { 5 , 4 };
	}

	else if (*this->players == 4) {
		this->cornerTilePositions[0] = { 1 , 1 };
		this->cornerTilePositions[1] = { 1 , 5 };
		this->cornerTilePositions[2] = { 5 , 1 };
		this->cornerTilePositions[3] = { 5 , 5 };
	}
}

std::vector<int> GameBoard::getCornerTilePositions(int position) {
	std::vector<int> positionVector;

	switch (position)
	{
	case 0:
		positionVector = this->cornerTilePositions[0];
		break;
	case 1:
		positionVector = this->cornerTilePositions[1];
		break;
	case 2:
		positionVector = this->cornerTilePositions[2];
		break;
	case 3:
		positionVector = this->cornerTilePositions[3];
		break;
	}

	return positionVector;
}

void GameBoard::setRows_Columns() {
	switch (*this->players)
	{
		case 2: 
			this->mapRows = new int(5);
			this->mapColumns = new int(5);
			break;
		case 3: 
			this->mapRows = new int(7);
			this->mapColumns = new int(5);
			break;
		case 4: 
			this->mapRows = new int(7);
			this->mapColumns = new int(7);
			break;
	}
}
