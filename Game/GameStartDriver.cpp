//
// Created by Ivan Garzon on 2020-03-25.
//
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

	}

	//HERE SHOULD BE CALLED THE NEXT DRIVER PASSING ALL OBJECTS
	//for example: GamePlayDriver::gamePlay(gameBoard, dck, numberOfPlayers, player1, player2, player3, player4);
}