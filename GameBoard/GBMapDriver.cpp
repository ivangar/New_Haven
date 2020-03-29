//
// Created by Ivan Garzon on 2020-02-11.
//
#include <iostream>
#include <string>
#include "GBMapDriver.h"
#include "GBMap.h"
#include "../Player/PlayerDriver.h"
#include "../Resources/Resources.h"

void GBMapDriver::gameBoardMapDriver() {

	Deck *dck = new Deck();
	int players;
	std::cout << "Please enter the number of players (allowed 2, 3 or 4 players): ";
	std::cin >> players;

	while (!std::cin || (players < 2 || players > 4) )
	{
		// user didn't input a number
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// next, request user reinput
		std::cout << "Please enter a valid number: ";
		std::cin >> players;
	}

	GameBoard* gameBoard = new GameBoard(players, dck);

	gameBoard->printGameBoard();

	//Call the player driver and let the players place tiles on the board
	PlayerDriver::playerDriver(gameBoard);
}






