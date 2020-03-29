#include "GameStartDriver.h"
#include "../GameBoard/GBMap.h"
#include "../Player/Player.h"
#include "../Resources/Resources.h"
#include <iostream>
#include <string>
#include <vector>
#include <iterator> 
#include <map>
#include <algorithm>

void GameStartDriver::gameStart() {

	int numberOfPlayers;
	std::string playerName;
	int playerId;
	std::vector<int> playerIds;
	std::map<int, Player*> players;
	Deck *dck = new Deck();

	//There is no way to know in advance how many players will be playing, so we declare all of them
	Player* player1;
	Player* player2;
	Player* player3;
	Player* player4;

	std::cout << "Please enter the number of players (allowed 2, 3 or 4 players): ";
	std::cin >> numberOfPlayers;

	while (!std::cin || (numberOfPlayers < 2 || numberOfPlayers > 4))
	{
		// user didn't input a number
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// next, request user reinput
		std::cout << "Please enter a valid number: ";
		std::cin >> numberOfPlayers;
	}

	GameBoard* gameBoard = new GameBoard(numberOfPlayers, dck);
	
	gameBoard->printGameBoard();

	//Get players data
	for (int i = 1; i <= numberOfPlayers; ++i)
	{
		std::cout << "\n\nEnter the name of a player : ";
		std::cin >> playerName;
		std::cout << "Enter the ID of a player : ";
		std::cin >> playerId;

		players.insert(std::pair<int, Player*>(playerId, new Player(playerName, playerId, gameBoard)));
		playerIds.push_back(playerId);
	}

	//Sorting the ids from lowest to highest, when assigning them player1 to player4 will take from lowest to highest value
	//So for the GameLoop, going clockwise we go with player1, player2... 
	std::sort(playerIds.begin(), playerIds.end());

	player1 = players[playerIds[0]];
	player2 = players[playerIds[1]];
	player1->buildVillage();
	player2->buildVillage();

	/*
	//To draw a building from a face up pool, and set it to player's hand
	Buildings* drawBld1 = gameBoard->getFaceUpPool()->drawFaceUpBuilding(1);
	player1->getHand()->addBuildingTile(drawBld1);
	
	std::cout << "\n\n Player 1 hand:" << std::endl;
	player1->getHand()->printHand();

	//To Replenish face up pool after player's turn is over
	gameBoard->getFaceUpPool()->replenishPool(dck);
	*/

	//Draw building tiles and harvest tiles for each player
	for (int i = 0; i < 6; ++i) 
	{
		player1->drawBuildingTile(dck);
		player2->drawBuildingTile(dck);
	}

	for (int i = 0; i < 2; ++i)
	{
		player1->drawHarvestTile(dck);
		player2->drawHarvestTile(dck);
	}

	//Draw Shipment Tiles for each player
	player1->drawShipmentTile(dck);
	player2->drawShipmentTile(dck);

	//Setup extra players
	if (numberOfPlayers == 3){
		player3 = players[playerIds[2]];
		player3->buildVillage();
		player3->drawShipmentTile(dck);

		for (int i = 0; i < 6; ++i)
			player3->drawBuildingTile(dck);

		for (int i = 0; i < 2; ++i)
			player3->drawHarvestTile(dck);

		std::cout << "\n\n Player 3 hand:" << std::endl;
		player3->getHand()->printHand();
	}
		
	if (numberOfPlayers == 4) {
		player3 = players[playerIds[2]];
		player4 = players[playerIds[3]];
		player3->buildVillage();
		player4->buildVillage();
		player3->drawShipmentTile(dck);
		player4->drawShipmentTile(dck);

		for (int i = 0; i < 6; ++i)
		{
			player3->drawBuildingTile(dck);
			player4->drawBuildingTile(dck);
		}

		for (int i = 0; i < 2; ++i)
		{
			player3->drawHarvestTile(dck);
			player4->drawHarvestTile(dck);
		}

		std::cout << "\n\n Player 4 hand:" << std::endl;
		player4->getHand()->printHand();
	}

	/*
	//To exchange a Shipment Tile from player's hand:
	std::cout << "\n\n Exchanging player1 Shipment tile :" << std::endl;
	HarvestTile* ex_ht = new HarvestTile();
	ex_ht = player1->getHand()->exchangeShipmentTile();
	ex_ht->printTile();

	player1->getHand()->printHand();
	*/
	std::cout << "\n\n This is the current deck after drawing tiles:" << std::endl;
	dck->printDeck();
}