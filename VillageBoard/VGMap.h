//
// Created by Zachary Hynes on 2020-02-06.
//

#ifndef COMP345_NEWHAVENPROJECT_VGMAP_H
#define COMP345_NEWHAVENPROJECT_VGMAP_H


#include "../Data Structures/Graph.h"
#include "../Deck/BuildingTile.h"

class VillageGameBoard {
public:
    //=========================
    // CONSTANTS
    //=========================
    static const int NUMBER_OF_ROWS = 6;
    static const int NUMBER_OF_COLUMNS = 5;

    //=========================
    // CONSTRUCTORS & DESTRUCTORS
    //=========================
    VillageGameBoard();
    ~VillageGameBoard();


    //=========================
    // GETTERS & SETTERS
    //=========================
    Graph *getVillageGameBoard() const {
        return villageGameBoard;
    }

    void setVillageGameBoard(Graph *villageGameBoard) {
        VillageGameBoard::villageGameBoard = villageGameBoard;
    }

    BuildingTile* getBuildingTileXY(int rowNumber, int columnNumber) const {
        auto abstractGameTile = villageGameBoard->getNodeAtCoordinatesXY(rowNumber, columnNumber)->getGameTile();
        return dynamic_cast<BuildingTile*>(abstractGameTile);
    }

    void setBuildingTileXY(BuildingTile* buildingTile, int rowNumber, int columnNumber) {
        villageGameBoard->getNodeAtCoordinatesXY(rowNumber, columnNumber)->setGameTile(buildingTile);
    }


    //=========================
    // FUNCTIONS
    //=========================
    void printVillageGameBoardMap();
    void debugVillageGameBoardMap();
    void printVillageGameBoardScore();

    void placeBuildingXY(Building* building, int rowNumber, int columnNumber, bool isPlacedFaceUp);

    Building* getBuildingXY(int rowNumber, int columnNumber);

    int calculateScore(int* score);


private:
    //=========================
    // CLASS PROPERTIES
    //=========================
    Graph* villageGameBoard{};

    //=========================
    // PRIVATE FUNCTIONS
    //=========================
    void printVillageGameBoardHeader();
    void printVillageGameBoardRowBorder();
    void printVillageGameBoardFooter();
    int getRowPoints(int rowNumber);
    int getColumnPoints(int columnNumber);
};


#endif //COMP345_NEWHAVENPROJECT_VGMAP_H
