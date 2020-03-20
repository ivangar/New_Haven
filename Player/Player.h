
#ifndef COMP345_NEWHAVENPROJECT_PLAYER_H
#define COMP345_NEWHAVENPROJECT_PLAYER_H

#include "../Resources/Resources.h"
#include "../VillageBoard/VGMap.h"
#include "../GameBoard/GBMap.h"
#include "../Deck/HarvestTile.h"
#include <string>

class Player
{

public:
    Player();
    Player(std::string name, int studentId, GameBoard* gameBoard);
    ~Player();

    Hand* getHand() const {
        return hand;
    }

    int* getId() const {
        return playerId;
    }

    void placeHarvestTile(HarvestTile* tile, int rowNumber, int columnNumber);
    void drawBuildingTile(Deck* game_deck);
    void drawHarvestTile(Deck* game_deck);
    void resourceTracker();
    void buildVillage();
    void calculateResources();
    void printPlayer();

    // Getters and Setters
    int *getPlayerId() const {
        return playerId;
    }

    void setPlayerId(int *playerId) {
        Player::playerId = playerId;
    }

    std::string *getName() const {
        return name;
    }

    void setName(std::string *name) {
        Player::name = name;
    }

    void setHand(Hand *hand) {
        Player::hand = hand;
    }

    VillageGameBoard *getVillageGameBoard() const {
        return villageGameBoard;
    }

    void setVillageGameBoard(VillageGameBoard *villageGameBoard) {
        Player::villageGameBoard = villageGameBoard;
    }

	GameBoard *getGameBoard() const {
		return gameBoard;
	}

	void setGameBoard(GameBoard *gameBoard) {
		Player::gameBoard = gameBoard;
	}

    int *getVillageBoardScore() const {
        return villageBoardScore;
    }

    void setVillageBoardScore(int *villageBoardScore) {
        Player::villageBoardScore = villageBoardScore;
    }


private:
    int* playerId;
    std::string* name;
    Hand* hand;
    VillageGameBoard* villageGameBoard;
	GameBoard* gameBoard;
    int* villageBoardScore;
	std::vector<int> collectedResources;
};


#endif //COMP345_NEWHAVENPROJECT_PLAYER_H
