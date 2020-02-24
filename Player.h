#pragma once
using namespace std;
class Player
{

public:
	Player();
	Player(string* name);
	~Player();

	void placeHarvestTile();
	void drawBuildingTile();
	void drawHarvestTile();
	void resourceTracker();
	void buildVillage();
	void calculateResources();

private:
	string* name;

};