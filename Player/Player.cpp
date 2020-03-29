#include "Player.h"
#include "../Deck/HarvestTile.h"
#include <iostream>
#include <string>
#include <vector>

//Constructor
Player::Player()
{
    this->playerId = new int(0);
    this->name = nullptr;
    this->hand = new Hand();
    this->villageGameBoard = new VillageGameBoard();
    this->villageBoardScore = new int(0);
	this->gameBoard = nullptr;
}

Player::Player(std::string name, int studentId, GameBoard* gameBoard) : Player()
{
    this->playerId = new int(studentId);
    this->name = new std::string(name);
    this->hand = new Hand(playerId);
	this->gameBoard = gameBoard;
}

//Deconstructor
Player::~Player()
{
    delete playerId;
    delete name;
    delete hand;
	delete gameBoard;
};

/** Game Functionality **/
//Exchange() calls this function to place a Harvest tile on Game board
void Player::placeHarvestTile(HarvestTile* tile, int rowNumber, int columnNumber)
{
	this->gameBoard->placeTileXY(tile, rowNumber, columnNumber);
	std::cout << "\n" << *name << " added a Harvest tile at position:" << rowNumber << "," << columnNumber << std::endl;
}

void Player::drawBuildingTile(Deck* game_deck)
{
    Buildings* drawnBld = game_deck->drawBuildings();

    this->hand->addBuildingTile(drawnBld);
}

void Player::drawHarvestTile(Deck* game_deck)
{
    HarvestTile* drawnHt = game_deck->drawHarvest();

    this->hand->addHarvestTile(drawnHt);
}

void Player::drawShipmentTile(Deck* game_deck)
{
	HarvestTile* drawnHt = game_deck->drawHarvest();
	drawnHt->flipTile();

	this->hand->addShipmentTile(drawnHt);
}

void Player::resourceTracker()
{
	this->collectedResources.clear();
	this->collectedResources = this->gameBoard->getResourceTrack()->getCollectedResources();
}
void Player::buildVillage()
{
    std::cout << "Building player " << *playerId << "'s Village game board.\n";
    this->villageGameBoard = new VillageGameBoard();
}
void Player::calculateResources()
{
    this->getVillageGameBoard()->calculateScore(this->getVillageBoardScore());
}

/** Extra Functionality **/
void Player::printPlayer() {

    std::cout << "Player " << *playerId << "'s name is " << *name << ".\n";
}

