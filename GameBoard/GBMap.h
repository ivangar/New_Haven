/**
 * This file has the declarations of GameBoard class and its members
 * It sets the gameboard graph based on how many players there are
 * As well it calculates adjacent resources
 *
 * Author(s):
 * @author Ivan Garzon - 27006284
 */

#ifndef COMP345_NEWHAVENPROJECT_GBMAP_H
#define COMP345_NEWHAVENPROJECT_GBMAP_H

#include "../Deck/HarvestTile.h"
#include "../Data Structures/Graph.h"
#include "../Enums/CornersTypes.h"
#include "../Enums/TileEdges.h"
#include "../Resources/Resources.h"
#include <vector>

class FaceUpPool {
public:

	FaceUpPool();
	~FaceUpPool();

	void replenishPool(Deck* game_deck);
	void printFaceUpPool();
	Buildings* drawFaceUpBuilding(int position);

private:
	std::vector<Buildings*> faceUpBuildings;
};

class ResourceTrack {
public:

	ResourceTrack();
	~ResourceTrack();

	void resetTrack();
	void addResources(int position, int amount);
	void incrementResource(ResourceTypes resourceType);
	void decrementResource(ResourceTypes resourceType, int amount);
	void printResourceTrack();
	std::vector<int> getCollectedResources() const {
		return resourceMarkers;
	}

private:
	std::vector<int> resourceMarkers;
};

class GameBoard {
public:

	//Setting up constructors and destructors

	GameBoard();
	GameBoard(int players, Deck* game_deck);
	~GameBoard();

	//getters and setters
	
	Graph *getGameBoard() const {
		return gameBoardGraph;
	}

	void setGameBoard(Graph *gBoard) {
		GameBoard::gameBoardGraph = gBoard;
	}

	void setRows_Columns();
	void setcornerTilePositions();
	std::vector<int> getCornerTilePositions(int position);
	void placeTileXY(HarvestTile* tile, int rowNumber, int columnNumber);
	HarvestTile* getTileXY(int rowNumber, int columnNumber);
	void printGameBoard();
	void calculateResources(HarvestTile* tilePlayed);
	void CheckResources(HarvestTile* currentHarvestTile, ResourceTypes Resourcetype, Corners corner);
	HarvestTile* getAdjacentTile(HarvestTile* tile, Edges edge);
	ResourceTrack* getResourceTrack() const {
		return resourceTrack;
	}
	FaceUpPool* getFaceUpPool() const {
		return faceUpPool;
	}
	void resetTileCorners();

private:
	int* mapRows;
	int* mapColumns;
	int* players;
	Graph* gameBoardGraph{};
	void printTopRow(int row);
	void printBottomRow(int row);
	std::vector< std::vector<int> > cornerTilePositions;
	ResourceTrack* resourceTrack;
	FaceUpPool* faceUpPool;
};
#endif