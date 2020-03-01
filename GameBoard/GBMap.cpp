//
// Created by Ivan Garzon on 2020-02-10.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip> 
#include <vector>
#include "GBMap.h"
#include "../Deck/HarvestTile.h"
#include "../Enums/ResourceTypes.h"
#include "../Enums/TileEdges.h"

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

void GameBoard::calculateResources(HarvestTile* tilePlayed, int rowNumber, int columnNumber) {

	resourcesCollected.assign(4, 0); //initialize all resources to 0

	//Calculate the placed tile's own resources
	for (int i = 0; i < 4; i++) {
		incrementResource(tilePlayed->getResourceType(static_cast<Corners>(i)));
	}

	Node* topNode = gameBoardGraph->getNodeAtCoordinatesXY(rowNumber, columnNumber)->getNodeOnTopEdge();
	Node* leftNode = gameBoardGraph->getNodeAtCoordinatesXY(rowNumber, columnNumber)->getNodeOnLeftEdge();
	Node* rightNode = gameBoardGraph->getNodeAtCoordinatesXY(rowNumber, columnNumber)->getNodeOnRightEdge();
	Node* bottomNode = gameBoardGraph->getNodeAtCoordinatesXY(rowNumber, columnNumber)->getNodeOnBottomEdge();

	//First check that the node exists (checking for out of bounds Node pointer)
	if (topNode != nullptr) {
		HarvestTile* topHarvestTile = dynamic_cast<HarvestTile*>(topNode->getGameTile());

		//Check that the Tile is not empty and has resources
		if (topHarvestTile->getResources() != nullptr) {
			//std::cout << "top node exists and it has resources\n";
			calculateAdjacentRes(tilePlayed, topHarvestTile, Edges::TOP);
		}

	}
	
	if (leftNode != nullptr) {
		HarvestTile* leftHarvestTile = dynamic_cast<HarvestTile*>(leftNode->getGameTile());

		if (leftHarvestTile->getResources() != nullptr) {
			//std::cout << "left node exists and it has resources\n";
			calculateAdjacentRes(tilePlayed, leftHarvestTile, Edges::LEFT);
		}

	}

	if (rightNode != nullptr) {
		HarvestTile* rightHarvestTile = dynamic_cast<HarvestTile*>(rightNode->getGameTile());

		if (rightHarvestTile->getResources() != nullptr) {
			//std::cout << "right node exists and it has resources\n";
			calculateAdjacentRes(tilePlayed, rightHarvestTile, Edges::RIGHT);
		}

	}

	if (bottomNode != nullptr) {
		HarvestTile* bottomHarvestTile = dynamic_cast<HarvestTile*>(bottomNode->getGameTile());

		if (bottomHarvestTile->getResources() != nullptr) {
			//std::cout << "bottom node exists and it has resources\n";
			calculateAdjacentRes(tilePlayed, bottomHarvestTile, Edges::BOTTOM);
		}

	}

}

void GameBoard::calculateAdjacentRes(HarvestTile* tilePlayed, HarvestTile* edgeTile, enum Edges edge) {
	if (edge == Edges::TOP) {
		//std::cout << "top Node Edge, let's start a chain collection from the played tile topLeft resource\n";

		ResourceTypes topLeftResource = tilePlayed->getResourceType(Corners::TOP_LEFT);

		if (topLeftResource == edgeTile->getResourceType(Corners::BOTTOM_LEFT)) {
			//std::cout << "resource chain collection from the played tile TOP_LEFT resource\n";
			
			incrementResource(topLeftResource);
			
			if (edgeTile->getResourceType(Corners::BOTTOM_RIGHT) == topLeftResource) {

				incrementResource(topLeftResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::TOP_RIGHT) == topLeftResource)
					incrementResource(topLeftResource);
			}
				
			if (edgeTile->getResourceType(Corners::TOP_LEFT) == topLeftResource) {
				
				incrementResource(topLeftResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::TOP_RIGHT) == topLeftResource)
					incrementResource(topLeftResource);
			}
		}

		ResourceTypes topRightResource = tilePlayed->getResourceType(Corners::TOP_RIGHT);

		//To avoid duplicate collection, lets follow the Tile Corners order. The next one is the TOP_RIGHT resource
		//We need to check if the TOP_LEFT resource has already collected the same type of adjacent resources
		if (topLeftResource == topRightResource && topLeftResource == edgeTile->getResourceType(Corners::BOTTOM_LEFT)) {
			//std::cout << "These resources has been previously collected.\n";
		}
		else if (topRightResource == edgeTile->getResourceType(Corners::BOTTOM_RIGHT)) {
			//std::cout << "resource chain collection from the played tile TOP_RIGHT resource\n";
			
			incrementResource(topRightResource);
			
			if (edgeTile->getResourceType(Corners::BOTTOM_LEFT) == topRightResource) {
				
				incrementResource(topRightResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::TOP_LEFT) == topRightResource)
					incrementResource(topRightResource);
			}

			if (edgeTile->getResourceType(Corners::TOP_RIGHT) == topRightResource) {

				incrementResource(topRightResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::TOP_LEFT) == topRightResource)
					incrementResource(topRightResource);
			}
				

		}
	}

	if (edge == Edges::LEFT) {
		//std::cout << "left Node Edge, let's start a chain collection from the played tile topLeft resource\n";

		ResourceTypes topLeftResource = tilePlayed->getResourceType(Corners::TOP_LEFT);

		if (topLeftResource == edgeTile->getResourceType(Corners::TOP_RIGHT)) {
			//std::cout << "resource chain collection from the played tile TOP_LEFT resource\n";

			incrementResource(topLeftResource);

			if (edgeTile->getResourceType(Corners::TOP_LEFT) == topLeftResource) {

				incrementResource(topLeftResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::BOTTOM_LEFT) == topLeftResource)
					incrementResource(topLeftResource);
			}

			if (edgeTile->getResourceType(Corners::BOTTOM_RIGHT) == topLeftResource) {

				incrementResource(topLeftResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::BOTTOM_LEFT) == topLeftResource)
					incrementResource(topLeftResource);
			}
		}

		ResourceTypes bottomLeftResource = tilePlayed->getResourceType(Corners::BOTTOM_LEFT);
		
		//To avoid duplicate collection, lets follow the Tile Corners order. The next one is the BOTTOM_LEFT resource
		//We need to check if the TOP_LEFT resource has already collected the same type of adjacent resources
		if (topLeftResource == bottomLeftResource && topLeftResource == edgeTile->getResourceType(Corners::BOTTOM_RIGHT)) {
			//std::cout << "These resources has been previously collected.\n";
		}
		else if (bottomLeftResource == edgeTile->getResourceType(Corners::BOTTOM_RIGHT)) {
			//std::cout << "resource chain collection from the played tile BOTTOM_LEFT resource\n";

			incrementResource(bottomLeftResource);

			if (edgeTile->getResourceType(Corners::BOTTOM_LEFT) == bottomLeftResource) {

				incrementResource(bottomLeftResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::TOP_LEFT) == bottomLeftResource)
					incrementResource(bottomLeftResource);
			}

			if (edgeTile->getResourceType(Corners::TOP_RIGHT) == bottomLeftResource) {

				incrementResource(bottomLeftResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::TOP_LEFT) == bottomLeftResource)
					incrementResource(bottomLeftResource);
			}


		}
	}

	if (edge == Edges::RIGHT) {
		//std::cout << "right Node Edge, let's start a chain collection from the played tile topRight resource\n";

		ResourceTypes topRightResource = tilePlayed->getResourceType(Corners::TOP_RIGHT);

		if (topRightResource == edgeTile->getResourceType(Corners::TOP_LEFT)) {
			//std::cout << "resource chain collection from the played tile TOP_RIGHT resource\n";

			incrementResource(topRightResource);

			if (edgeTile->getResourceType(Corners::TOP_RIGHT) == topRightResource) {

				incrementResource(topRightResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::BOTTOM_RIGHT) == topRightResource)
					incrementResource(topRightResource);
			}

			if (edgeTile->getResourceType(Corners::BOTTOM_LEFT) == topRightResource) {

				incrementResource(topRightResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::BOTTOM_RIGHT) == topRightResource)
					incrementResource(topRightResource);
			}
		}

		ResourceTypes bottomRightResource = tilePlayed->getResourceType(Corners::BOTTOM_RIGHT);

		//To avoid duplicate collection, lets follow the Tile Corners order. The next one is the BOTTOM_LEFT resource
		//We need to check if the TOP_LEFT resource has already collected the same type of adjacent resources
		if (topRightResource == bottomRightResource && topRightResource == edgeTile->getResourceType(Corners::TOP_LEFT)) {
			//std::cout << "These resources has been previously collected.\n";
		}
		else if (bottomRightResource == edgeTile->getResourceType(Corners::BOTTOM_LEFT)) {
			//std::cout << "resource chain collection from the played tile BOTTOM_LEFT resource\n";

			incrementResource(bottomRightResource);

			if (edgeTile->getResourceType(Corners::TOP_LEFT) == bottomRightResource) {

				incrementResource(bottomRightResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::TOP_RIGHT) == bottomRightResource)
					incrementResource(bottomRightResource);
			}

			if (edgeTile->getResourceType(Corners::BOTTOM_RIGHT) == bottomRightResource) {

				incrementResource(bottomRightResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::TOP_RIGHT) == bottomRightResource)
					incrementResource(bottomRightResource);
			}


		}
	}

	if (edge == Edges::BOTTOM) {
		//std::cout << "bottom Node Edge, let's start a chain collection from the played tile bottomleft resource\n";

		ResourceTypes bottomLeftResource = tilePlayed->getResourceType(Corners::BOTTOM_LEFT);

		if (bottomLeftResource == edgeTile->getResourceType(Corners::TOP_LEFT)) {
			//std::cout << "resource chain collection from the played tile BOTTOM_LEFT resource\n";

			incrementResource(bottomLeftResource);

			if (edgeTile->getResourceType(Corners::TOP_RIGHT) == bottomLeftResource) {

				incrementResource(bottomLeftResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::BOTTOM_RIGHT) == bottomLeftResource)
					incrementResource(bottomLeftResource);
			}

			if (edgeTile->getResourceType(Corners::BOTTOM_LEFT) == bottomLeftResource) {

				incrementResource(bottomLeftResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::BOTTOM_RIGHT) == bottomLeftResource)
					incrementResource(bottomLeftResource);
			}
		}

		ResourceTypes bottomRightResource = tilePlayed->getResourceType(Corners::BOTTOM_RIGHT);

		//To avoid duplicate collection, lets follow the Tile Corners order. The next one is the BOTTOM_LEFT resource
		//We need to check if the TOP_LEFT resource has already collected the same type of adjacent resources
		if (bottomLeftResource == bottomRightResource && bottomLeftResource == edgeTile->getResourceType(Corners::TOP_LEFT)) {
			//std::cout << "These resources has been previously collected.\n";
		}
		else if (bottomRightResource == edgeTile->getResourceType(Corners::TOP_RIGHT)) {
			//std::cout << "resource chain collection from the played tile BOTTOM_LEFT resource\n";

			incrementResource(bottomRightResource);

			if (edgeTile->getResourceType(Corners::TOP_LEFT) == bottomRightResource) {

				incrementResource(bottomRightResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::BOTTOM_LEFT) == bottomRightResource)
					incrementResource(bottomRightResource);
			}

			if (edgeTile->getResourceType(Corners::BOTTOM_RIGHT) == bottomRightResource) {

				incrementResource(bottomRightResource);

				//Collect diagonal resources only if any adjacent tile is of the same resource
				if (edgeTile->getResourceType(Corners::BOTTOM_LEFT) == bottomRightResource)
					incrementResource(bottomRightResource);
			}

		}
	}
}

void GameBoard::getCollectedResources() {

	//Change to print the resource string: WHEAT 0, TIMBER 5...
	for (int i = 0; i < this->resourcesCollected.size(); i++){
		std::cout << ResourceTypesStrings[i] << ": " << this->resourcesCollected[i] << std::endl;
	}
}

void GameBoard::incrementResource(enum ResourceTypes resourceType) {
	this->resourcesCollected[resourceType] = ++(this->resourcesCollected[resourceType]);
}
