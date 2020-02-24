//
// Created by Zachary Hynes on 2020-02-06.
//

#include <iostream>
#include "VGMap.h"
#include "../Deck/BuildingTile.h"


//=========================
// CONSTRUCTORS & DESTRUCTORS
//=========================
//Construct a default Village Game Board Map.
VillageGameBoard::VillageGameBoard() {
    // Create Village Board graph.
    this->setVillageGameBoard(new Graph(NUMBER_OF_ROWS, NUMBER_OF_COLUMNS));

    auto villageGameBoard = this->getVillageGameBoard();
    int rowCost = 6;

    // Set building tiles in the nodes and set their costs.
    for (int i = 0; i < NUMBER_OF_ROWS; ++i) {
        int* rowBuildCost = new int(rowCost);

        for (int j = 0; j < NUMBER_OF_COLUMNS; ++j) {
            auto createdBuildingTile = new BuildingTile(*rowBuildCost);
            villageGameBoard->getNodeAtCoordinatesXY(i, j)->setGameTile(createdBuildingTile);
        }

        rowCost--;
    }
}

VillageGameBoard::~VillageGameBoard() {
//    for (int i = 0; i < NUMBER_OF_ROWS; ++i) {
//        for (int j = 0; j < NUMBER_OF_COLUMNS; ++j) {
//            delete villageGameBoard[i][j];
//        }
//    }
//
//    delete **villageGameBoard;
}


//=========================
// FUNCTIONS
//=========================
void VillageGameBoard::printVillageGameBoardMap() {
    printVillageGameBoardHeader();
    int rowBuildCost = 6;

    for (int i = 0; i < NUMBER_OF_ROWS; ++i) {
        std::cout << "[" << i << "] |";
        for (int j = 0; j < NUMBER_OF_COLUMNS; ++j) {
            AbstractGameTile* abstractGameTile = villageGameBoard->getNodeAtCoordinatesXY(i, j)->getGameTile();
            BuildingTile* buildingTile = dynamic_cast<BuildingTile*>(abstractGameTile);

            buildingTile->printTile();
        }
        std::cout << " Row Points: " << rowBuildCost--;
        printVillageGameBoardRowBorder();
    }

    printVillageGameBoardFooter();

}

void VillageGameBoard::debugVillageGameBoardMap() {

    // TODO: Implement debugVillageGameBoardMap function.
//    std::cout << "array address: " << &villageGameBoard[0] << std::endl;
//
//    for (int i = 0; i < NUMBER_OF_ROWS; ++i) {
//        for (int j = 0; j < NUMBER_OF_COLUMNS; ++j) {
//            std::cout << "array[" << i << "][" << j << "] address: " << &villageGameBoard[i][j];
//            std::cout << ", holds pointer to address: " << villageGameBoard[i][j];
//            std::cout << ", which contains the value: " << *villageGameBoard[i][j] << std::endl;
//        }
//    }
}

void VillageGameBoard::printVillageGameBoardScore() {
    int* score = new int(0);

    std::cout << "Player Score: " << calculateScore(score) << std::endl;

    delete score;
}

void VillageGameBoard::placeBuildingXY(Building* building, int rowNumber, int columnNumber, bool isPlacedFaceUp) {
    if (rowNumber >= NUMBER_OF_ROWS || columnNumber >= NUMBER_OF_COLUMNS) {
        std::cout << "ERROR: Row number or Column number exceeds village game board size." << std::endl;
        return;
    }

    building->setIsFaceUp(isPlacedFaceUp);

    this->getBuildingTileXY(rowNumber, columnNumber)->setBuilding(building);
}

Building* VillageGameBoard::getBuildingXY(int rowNumber, int columnNumber) {
    if (rowNumber >= NUMBER_OF_ROWS || columnNumber >= NUMBER_OF_COLUMNS) {
        std::cout << "ERROR: Row number or Column number exceeds village game board size." << std::endl;
        return nullptr;
    }

    return this->getBuildingTileXY(rowNumber, columnNumber)->getBuilding();
}

int VillageGameBoard::calculateScore(int* score) {
    int totalScore = 0;
    bool rowOrColumnHasAFaceDownBuilding = false;
    bool rowOrColumnIsMissingABuilding = false;

    // Calculate row scores
    for (int i = 0; i < NUMBER_OF_ROWS; ++i) {
        for (int j = 0; j < NUMBER_OF_COLUMNS; ++j) {
            auto currentBuilding = getBuildingXY(i, j);

            if (currentBuilding == nullptr) {
                rowOrColumnIsMissingABuilding = true;
            } else {
                if (!*currentBuilding->getIsFaceUp()) {
                    rowOrColumnHasAFaceDownBuilding = true;
                }
            }
        }

        if (rowOrColumnIsMissingABuilding) {
            // Don't calculate the score.
        } else if (rowOrColumnHasAFaceDownBuilding) {
            // Entire row filled with buildings, but one or more is face down.
            totalScore += getRowPoints(i);
        } else {
            totalScore += 2 * getRowPoints(i);
        }

        rowOrColumnHasAFaceDownBuilding = false;
        rowOrColumnIsMissingABuilding = false;
    }

    // Calculate column scores
    for (int i = 0; i < NUMBER_OF_COLUMNS; ++i) {
        for (int j = 0; j < NUMBER_OF_ROWS; ++j) {
            auto currentBuilding = getBuildingXY(j, i);

            if (currentBuilding == nullptr) {
                rowOrColumnIsMissingABuilding = true;
            } else {
                if (!*currentBuilding->getIsFaceUp()) {
                    rowOrColumnHasAFaceDownBuilding = true;
                }
            }
        }

        if (rowOrColumnIsMissingABuilding) {
            // Don't calculate the score.
        } else if (rowOrColumnHasAFaceDownBuilding) {
            // Entire row filled with buildings, but one or more is face down.
            totalScore += getColumnPoints(i);
        } else {
            totalScore += 2 * getColumnPoints(i);
        }

        rowOrColumnHasAFaceDownBuilding = false;
        rowOrColumnIsMissingABuilding = false;
    }

    *score = totalScore;
    return *score;
}


//=========================
// PRIVATE FUNCTIONS
//=========================
void VillageGameBoard::printVillageGameBoardHeader() {
    std::cout << "    |";
    for (int i = 0; i < NUMBER_OF_COLUMNS; ++i) {
        std::cout << "    [" << i << "]  |";
    }
    printVillageGameBoardRowBorder();
}

void VillageGameBoard::printVillageGameBoardRowBorder() {
    std::cout << "\n-------------------------------------------------------" << std::endl;
}

void VillageGameBoard::printVillageGameBoardFooter() {
    std::cout << "    |    5    |    4    |    3    |    4    |    5    | <--- Column Points\n" << std::endl;
}

int VillageGameBoard::getRowPoints(int rowNumber) {
    switch (rowNumber) {
        case 0: return 6;
        case 1: return 5;
        case 2: return 4;
        case 3: return 3;
        case 4: return 2;
        case 5: return 1;
        default: return 0;
    }
}

int VillageGameBoard::getColumnPoints(int columnNumber) {
    switch (columnNumber) {
        case 0: return 5;
        case 1: return 4;
        case 2: return 3;
        case 3: return 4;
        case 4: return 5;
        default: return 0;
    }
}












