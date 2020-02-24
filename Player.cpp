#include "Player.h"
#include <iostream>
using namespace std;

//Constructor
Player::Player()
{
	this->name = nullptr;
}
Player::Player(string* name)
{
	this->name = new string(name);
	//Part 2:
	//VillageBoard* villageBoard; 

	//Part 6: ***not too sure about this part
	//BuildingScore bScore; 
	//ResourceScore rScore; 

	//Part 5: creates player's hand which has their harvest tiles and buildings 
	//Hand playersHand;

}
//Deconstructor
Player::~Player()
{
	delete name;
};
//Part 1: places Harvest tile from board and removes it from hand
void Player::placeHarvestTile()
{
}
void Player::drawBuildingTile()
{
}
void Player::drawHarvestTile()
{
}
void Player::resourceTracker()
{
}
void Player::buildVillage()
{
}
void Player::calculateResources()
{
}


