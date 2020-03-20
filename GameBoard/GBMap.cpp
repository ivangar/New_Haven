/**
 * This file has the definitions of GameBoard class and its members
 *
 * Author(s):
 * @author Ivan Garzon - 27006284
 */

#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip> 
#include <vector>
#include "GBMap.h"
#include "../Deck/HarvestTile.h"
#include "../Enums/ResourceTypes.h"
#include "../Enums/TileEdges.h"

 /**
 * Resource Track object used in game board
 */
ResourceTrack::ResourceTrack() {
	this->resourceMarkers.assign(4, 0);
}

void ResourceTrack::resetTrack() {
	std::cout << "\nReseting Resource markers \n";
	this->resourceMarkers.assign(4, 0);
	printResourceTrack();
}

/**
* Increment/decrement a resource marker
*/

void ResourceTrack::incrementResource(ResourceTypes resourceType) {
	this->resourceMarkers[resourceType] = ++(this->resourceMarkers[resourceType]);
}

void ResourceTrack::decrementResource(ResourceTypes resourceType, int amount) {
	if(amount <= this->resourceMarkers[resourceType])
		this->resourceMarkers[resourceType] = this->resourceMarkers[resourceType] - amount;
	else
		std::cout << "ERROR: The amount of " << amount << " " << ResourceTypesStrings[resourceType] << " resources exceeds the current number of resources\n";
}

/**
* This function prints the collected resources
*/

void ResourceTrack::printResourceTrack() {

	std::cout << "\nResource Track: \n\n";

	//Change to print the resource string: WHEAT 0, TIMBER 5...
	for (int i = 0; i < this->resourceMarkers.size(); i++) {
		std::cout << ResourceTypesStrings[i] << ": " << this->resourceMarkers[i] << std::endl;
	}
}

/**
* Constructor that sets a gameboard graph and 4 default HarvesTiles in the 4 corners
*/
GameBoard::GameBoard(int players) {
	this->players = new int(players);
	this->setRows_Columns();

	Graph *g = new Graph(*this->mapRows, *this->mapColumns);
	this->setGameBoard(g);
	
	//Get game board and test
	auto gameBoardGraph = this->getGameBoard();

	//set an empty resource track
	this->resourceTrack = new ResourceTrack();

	// Set harvest tiles in the nodes
	for (int i = 0; i < *this->mapRows; ++i) {

		for (int j = 0; j < *this->mapColumns; ++j) {
			
			int nodeVal = ((i * (*this->mapColumns)) + j);
			
			auto emptyHarvestTile = new HarvestTile();
			emptyHarvestTile->setNodeValue(nodeVal);
			gameBoardGraph->getNodeAtCoordinatesXY(i, j)->setGameTile(emptyHarvestTile);
		}
	}

	//Set 4 corner positions
	setcornerTilePositions();

	//Setting a default harvest tile to put on game board
	auto* topLeftTile = new HarvestTile(ResourceTypes::QUARRY, ResourceTypes::MEADOW, ResourceTypes::FOREST, ResourceTypes::FOREST);
	auto* topRightTile = new HarvestTile(ResourceTypes::WHEATFIELD, ResourceTypes::MEADOW, ResourceTypes::WHEATFIELD, ResourceTypes::FOREST);
	auto* bottomLeftTile = new HarvestTile(ResourceTypes::MEADOW, ResourceTypes::QUARRY, ResourceTypes::MEADOW, ResourceTypes::WHEATFIELD);
	auto* bottomRightTile = new HarvestTile(ResourceTypes::QUARRY, ResourceTypes::QUARRY, ResourceTypes::FOREST, ResourceTypes::WHEATFIELD);

	//Set the corner Harvest Tiles
	placeTileXY(topLeftTile, getCornerTilePositions(0)[0], getCornerTilePositions(0)[1]);
	placeTileXY(topRightTile, getCornerTilePositions(1)[0], getCornerTilePositions(1)[1]);
	placeTileXY(bottomLeftTile, getCornerTilePositions(2)[0], getCornerTilePositions(2)[1]);
	placeTileXY(bottomRightTile, getCornerTilePositions(3)[0], getCornerTilePositions(3)[1]);

	//Reset track, we don't want to track resources yet
	this->resourceTrack->resetTrack();
}

/**
* Default destructor to remove dangling pointers
*/

GameBoard::~GameBoard() {
	delete mapRows;
	delete mapColumns;
	delete players;

	for (int i = 0; i < *this->mapRows; ++i) {
		for (int j = 0; j < *this->mapColumns; ++j) {
			Node* node = gameBoardGraph->getNodeAtCoordinatesXY(i, j);
            delete node;
			node = nullptr;
        }
    }

	delete gameBoardGraph;

	mapRows = nullptr;
	mapColumns = nullptr;
	players = nullptr;
	gameBoardGraph = nullptr;
}

/**
* This function places a Tile on a specified row and column. 
* It checks if the position is already taken by another Tile object
*/

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

	//Set the node value of each new tile placed
	int nodeVal = ((rowNumber * (*this->mapColumns)) + columnNumber);
	tile->setNodeValue(nodeVal);
	gameBoardGraph->getNodeAtCoordinatesXY(rowNumber, columnNumber)->setGameTile(tile);
	
	//Every time a tile is placed calculate resources
	this->calculateResources(tile);
}

/**
* This function gets a Harvest Tile from a specified position on the board
*/

HarvestTile* GameBoard::getTileXY(int rowNumber, int columnNumber) {
	if (rowNumber >= *mapRows || columnNumber >= *mapColumns) {
		std::cout << "ERROR: Row number or Column number exceeds game board size." << std::endl;
		return nullptr;
	}

	AbstractGameTile* targetTile = gameBoardGraph->getNodeAtCoordinatesXY(rowNumber, columnNumber)->getGameTile();
	HarvestTile* targetHarvestTile = dynamic_cast<HarvestTile*>(targetTile);
	return targetHarvestTile;
}

/**
* This function prints the GameBoard as a series of squares with resources inside
* It follows a similar style to that of the actual game board
*/

void GameBoard::printGameBoard() {

	std::cout << "\n\nGAME BOARD SIDE A\n\n";

	for (int col = 0; col < *mapColumns; ++col) {
		std::cout << "      " << col << "       ";
	}
	std::cout << std::endl;

	for (int i = 0; i < *mapRows; ++i) {
		printTopRow(i);
		printBottomRow(i);
	}
}

/**
* This function prints the top row of each tile with the top left and top right resources
*/

void GameBoard::printTopRow(int row) {
	
	//If its 4 players, don't print the corners of the board
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

/**
* This function prints the bottom row of each tile with the bottom left and bottom right resources
*/

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

/**
* This function sets the corner tiles of the game board when it's created
*/

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

/**
* This function returns a pair of corner tile positions based on a position
*/

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

/**
* This function sets the default number of rows and columns of the game board
*/

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

/**
* This function calculates the resources from an adjacent Harvest Tile
*/

void GameBoard::calculateResources(HarvestTile* tilePlayed) {

	// Check all 4 resources:
	// TOP_LEFT

	Corner* TopLeftResource = tilePlayed->getTopLeftResource();
	CheckResources(tilePlayed, TopLeftResource->getResourceType(), Corners::TOP_LEFT);

	// TOP_RIGHT

	Corner* TopRightResource = tilePlayed->getTopRightResource();
	CheckResources(tilePlayed, TopRightResource->getResourceType(), Corners::TOP_RIGHT);

	//BOTTOM_LEFT

	Corner* BottomLeftResource = tilePlayed->getBottomLeftResource();
	CheckResources(tilePlayed, BottomLeftResource->getResourceType(), Corners::BOTTOM_LEFT);

	//BOTTOM_RIGHT

	Corner* BottomRightResource = tilePlayed->getBottomRightResource();
	CheckResources(tilePlayed, BottomRightResource->getResourceType(), Corners::BOTTOM_RIGHT);

	resetTileCorners();
}

void GameBoard::CheckResources(HarvestTile* currentHarvestTile, ResourceTypes Resourcetype, Corners corner) {
	
	ResourceTrack* resTracker = getResourceTrack();

	if (corner == Corners::TOP_LEFT) {

		Corner* topLeftCorner = currentHarvestTile->getTopLeftResource();

		if (topLeftCorner->getResourceType() == Resourcetype) {
			if (!topLeftCorner->getHasBeenCounted()) {
				// Add resource to the resource counting vector
				resTracker->incrementResource(topLeftCorner->getResourceType());

				// Mark the resource as having been counted
				topLeftCorner->setHasBeenCounted(true);

				// Check Bottom Left Resource of the Top Harvest Tile
				auto* topHarvestTile = getAdjacentTile(currentHarvestTile, Edges::TOP);

				if (topHarvestTile != nullptr) {
					CheckResources(topHarvestTile, Resourcetype, Corners::BOTTOM_LEFT);
				}

				// Check Top Right Resource of the Left Harvest Tile
				auto* leftHarvestTile = getAdjacentTile(currentHarvestTile, Edges::LEFT);

				if (leftHarvestTile != nullptr) {
					CheckResources(leftHarvestTile, Resourcetype, Corners::TOP_RIGHT);
				}

			}

			// If Top Right is ResourceType && !hasBeenCounted
			Corner* topRightCorner = currentHarvestTile->getTopRightResource();

			if ((topRightCorner->getResourceType() == Resourcetype) && !topRightCorner->getHasBeenCounted())
				CheckResources(currentHarvestTile, Resourcetype, Corners::TOP_RIGHT);

			// If Bottom Left is ResourceType && !hasBeenCounted
			Corner* bottomLeftCorner = currentHarvestTile->getBottomLeftResource();

			if ((bottomLeftCorner->getResourceType() == Resourcetype) && !bottomLeftCorner->getHasBeenCounted())
				CheckResources(currentHarvestTile, Resourcetype, Corners::BOTTOM_LEFT);
		}
	}

	else if (corner == Corners::TOP_RIGHT) {

		Corner* topRightCorner = currentHarvestTile->getTopRightResource();

		if (topRightCorner->getResourceType() == Resourcetype) {
			if (!topRightCorner->getHasBeenCounted()) {
				// Add resource to the resource counting vector
				resTracker->incrementResource(topRightCorner->getResourceType());

				// Mark the resource as having been counted
				topRightCorner->setHasBeenCounted(true);


				// Check Bottom Right Resource of the Top Harvest Tile
				auto* topHarvestTile = getAdjacentTile(currentHarvestTile, Edges::TOP);

				if (topHarvestTile != nullptr) {
					CheckResources(topHarvestTile, Resourcetype, Corners::BOTTOM_RIGHT);
				}

				// Check Top Left Resource of the Right Harvest Tile
				auto* rightHarvestTile = getAdjacentTile(currentHarvestTile, Edges::RIGHT);

				if (rightHarvestTile != nullptr) {
					CheckResources(rightHarvestTile, Resourcetype, Corners::TOP_LEFT);
				}
			}

			// If Top Left is ResourceType && !hasBeenCounted
			Corner* topLeftCorner = currentHarvestTile->getTopLeftResource();

			if ((topLeftCorner->getResourceType() == Resourcetype) && !topLeftCorner->getHasBeenCounted())
				CheckResources(currentHarvestTile, Resourcetype, Corners::TOP_LEFT);

			// If Bottom Right is ResourceType && !hasBeenCounted
			Corner* bottomRightCorner = currentHarvestTile->getBottomRightResource();

			if ((bottomRightCorner->getResourceType() == Resourcetype) && !bottomRightCorner->getHasBeenCounted())
				CheckResources(currentHarvestTile, Resourcetype, Corners::BOTTOM_RIGHT);
		}
	}

	else if (corner == Corners::BOTTOM_LEFT) {

		Corner* bottomLeftCorner = currentHarvestTile->getBottomLeftResource();

		if (bottomLeftCorner->getResourceType() == Resourcetype) {
			if (!bottomLeftCorner->getHasBeenCounted()) {
				// Add resource to the resource counting vector
				resTracker->incrementResource(bottomLeftCorner->getResourceType());

				// Mark the resource as having been counted
				bottomLeftCorner->setHasBeenCounted(true);

				// Check Top Left Resource of the Bottom Harvest Tile
				auto* bottomHarvestTile = getAdjacentTile(currentHarvestTile, Edges::BOTTOM);

				if (bottomHarvestTile != nullptr) {
					CheckResources(bottomHarvestTile, Resourcetype, Corners::TOP_LEFT);
				}

				// Check Bottom Right Resource of the Left Harvest Tile
				auto* leftHarvestTile = getAdjacentTile(currentHarvestTile, Edges::LEFT);

				if (leftHarvestTile != nullptr) {
					CheckResources(leftHarvestTile, Resourcetype, Corners::BOTTOM_RIGHT);
				}
			}

			// If Top Left is ResourceType && !hasBeenCounted
			Corner* topLeftCorner = currentHarvestTile->getTopLeftResource();

			if ((topLeftCorner->getResourceType() == Resourcetype) && !topLeftCorner->getHasBeenCounted())
				CheckResources(currentHarvestTile, Resourcetype, Corners::TOP_LEFT);

			// If Bottom Right is ResourceType && !hasBeenCounted
			Corner* bottomRightCorner = currentHarvestTile->getBottomRightResource();

			if ((bottomRightCorner->getResourceType() == Resourcetype) && !bottomRightCorner->getHasBeenCounted())
				CheckResources(currentHarvestTile, Resourcetype, Corners::BOTTOM_RIGHT);
		}
	}

	else if (corner == Corners::BOTTOM_RIGHT) {
	
		Corner* bottomRightCorner = currentHarvestTile->getBottomRightResource();

		if (bottomRightCorner->getResourceType() == Resourcetype) {
			if (!bottomRightCorner->getHasBeenCounted()) {
				// Add resource to the resource counting vector
				resTracker->incrementResource(bottomRightCorner->getResourceType());

				// Mark the resource as having been counted
				bottomRightCorner->setHasBeenCounted(true);

				// Check Top Right Resource of the Bottom Harvest Tile
				auto* bottomHarvestTile = getAdjacentTile(currentHarvestTile, Edges::BOTTOM);

				if (bottomHarvestTile != nullptr) {
					CheckResources(bottomHarvestTile, Resourcetype, Corners::TOP_RIGHT);
				}

				// Check Bottom Left Resource of the Right Harvest Tile
				auto* rightHarvestTile = getAdjacentTile(currentHarvestTile, Edges::RIGHT);

				if (rightHarvestTile != nullptr) {
					CheckResources(rightHarvestTile, Resourcetype, Corners::BOTTOM_LEFT);
				}
			}

			// If Top Right is ResourceType && !hasBeenCounted
			Corner* topRightCorner = currentHarvestTile->getTopRightResource();

			if ((topRightCorner->getResourceType() == Resourcetype) && !topRightCorner->getHasBeenCounted())
				CheckResources(currentHarvestTile, Resourcetype, Corners::TOP_RIGHT);

			// If Bottom Left is ResourceType && !hasBeenCounted
			Corner* bottomLeftCorner = currentHarvestTile->getBottomLeftResource();

			if ((bottomLeftCorner->getResourceType() == Resourcetype) && !bottomLeftCorner->getHasBeenCounted())
				CheckResources(currentHarvestTile, Resourcetype, Corners::BOTTOM_LEFT);
		}
	}
}


HarvestTile* GameBoard::getAdjacentTile(HarvestTile* tile, enum Edges edge) {

	if (edge == Edges::TOP) {

		// Check Bottom Left Resource of the Top Harvest Tile
		Node* topNode = gameBoardGraph->getNode(tile->getNodeValue())->getNodeOnTopEdge();
		//Careful, the node can be null, we have to check it's not
		if (topNode != nullptr) {
			HarvestTile* topHarvestTile = dynamic_cast<HarvestTile*>(topNode->getGameTile());

			//Check that the Tile is not empty and has resources (it can be an empty tile)
			if (topHarvestTile->getResources() != nullptr) {
				return topHarvestTile;
			}
		}
	}
	else if (edge == Edges::LEFT)
	{

		Node* leftNode = gameBoardGraph->getNode(tile->getNodeValue())->getNodeOnLeftEdge();

		if (leftNode != nullptr) {
			HarvestTile* leftHarvestTile = dynamic_cast<HarvestTile*>(leftNode->getGameTile());

			if (leftHarvestTile->getResources() != nullptr) {
				return leftHarvestTile;
			}
		}
	}
	else if (edge == Edges::RIGHT)
	{

		Node* rightNode = gameBoardGraph->getNode(tile->getNodeValue())->getNodeOnRightEdge();

		if (rightNode != nullptr) {
			HarvestTile* rightHarvestTile = dynamic_cast<HarvestTile*>(rightNode->getGameTile());

			if (rightHarvestTile->getResources() != nullptr) {
				return rightHarvestTile;
			}
		}
	}
	else if (edge == Edges::BOTTOM)
	{

		Node* bottomNode = gameBoardGraph->getNode(tile->getNodeValue())->getNodeOnBottomEdge();

		if (bottomNode != nullptr) {
			HarvestTile* bottomHarvestTile = dynamic_cast<HarvestTile*>(bottomNode->getGameTile());

			if (bottomHarvestTile->getResources() != nullptr) {
				return bottomHarvestTile;
			}
		}
	}
    return nullptr;
}

//After traversal of tiles, reset the corners count of each tile
void GameBoard::resetTileCorners() {
	for (int i = 0; i < *this->mapRows; ++i) {
		for (int j = 0; j < *this->mapColumns; ++j) {
			auto harvestTile = getTileXY(i, j);

			if (harvestTile->getResources() != nullptr)
				harvestTile->resetCornerCount();
		}
	}
}