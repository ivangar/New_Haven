//
// Created by Ivan Garzon on 2020-02-10.
//
#ifndef COMP345_NEWHAVENPROJECT_GBMAP_H
#define COMP345_NEWHAVENPROJECT_GBMAP_H

#include "../Deck/HarvestTile.h"
#include "../Data Structures/Graph.h"
#include <vector>

class GameBoard {
public:
	GameBoard();
	GameBoard(int players);
	~GameBoard();

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

private:
	int* mapRows;
	int* mapColumns;
	int* players;
	Graph* gameBoardGraph{};
	void printTopRow(int row);
	void printBottomRow(int row);
	std::vector< std::vector<int> > cornerTilePositions;
};
#endif