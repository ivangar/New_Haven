//
// Created by Ivan Garzon on 2020-02-11.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <iterator>
#include "HarvestTile.h"
#include "../Resources/Resources.h"

HarvestTile::HarvestTile() {
	this->resources = nullptr;  //amount of resources, if no resources the tile is empty
	this->setIsFaceUp(true);
}

HarvestTile::HarvestTile(const HarvestTile& copy_ht) {
	std::cout << "Copy Constructor.";
	this->resources = new int(*HarvestTile::NUM_CORNERS);

	res_vctr.push_back(new ResourceTypes(copy_ht.getResourceType(Corners::TOP_LEFT)));  //topLeft
	res_vctr.push_back(new ResourceTypes(copy_ht.getResourceType(Corners::TOP_RIGHT)));  //topRight
	res_vctr.push_back(new ResourceTypes(copy_ht.getResourceType(Corners::BOTTOM_LEFT))); //bottomLeft
	res_vctr.push_back(new ResourceTypes(copy_ht.getResourceType(Corners::BOTTOM_RIGHT)));  //bottomRight
}

HarvestTile::HarvestTile(HarvestTile&& ht) : res_vctr(ht.res_vctr), resources(ht.resources){
	std::cout << "Move Constructor.";
	ht.res_vctr.clear();
	ht.resources = nullptr;
}

HarvestTile::HarvestTile(std::vector<ResourceTypes> res){
	this->resources = new int(res.size());
	setHarvestTileResources(res);
}

Corner::Corner(ResourceTypes res) {
	setResourceType(res);
	setHasBeenCounted(false);
}

HarvestTile::HarvestTile(ResourceTypes r1, ResourceTypes r2, ResourceTypes r3, ResourceTypes r4) {

	this->resources = new int(*this->NUM_CORNERS);

	this->setCornerResource(Corners::TOP_LEFT, r1);
	this->setCornerResource(Corners::TOP_RIGHT, r2);
	this->setCornerResource(Corners::BOTTOM_LEFT, r3);
	this->setCornerResource(Corners::BOTTOM_RIGHT, r4);

	this->TopLeftResource = new Corner(r1);
	this->TopRightResource = new Corner(r2);
	this->BottomLeftResource = new Corner(r3);
	this->BottomRightResource = new Corner(r4);

	this->setIsFaceUp(true);
}

HarvestTile::~HarvestTile() {
	for (std::vector<ResourceTypes*>::iterator res = this->res_vctr.begin(); res != this->res_vctr.end(); ++res) {
		delete *res; 
	}
	this->res_vctr.clear();
	delete this->resources;
	delete this->NUM_CORNERS;
	this->resources = nullptr;
	this->NUM_CORNERS = nullptr;
	delete this->isFaceUp;
	this->isFaceUp = nullptr;
}

HarvestTile& HarvestTile::operator=(HarvestTile&& ht) {
	std::cout << "Move Assignment.";
	if (&ht == this)
		return *this;

	for (std::vector<ResourceTypes*>::iterator res = this->res_vctr.begin(); res != this->res_vctr.end(); ++res) {
		delete *res;
	}
	this->res_vctr.clear();

	res_vctr = ht.res_vctr;
	resources = ht.resources;
	ht.res_vctr.clear();
	ht.resources = nullptr;

	return *this;
}

void HarvestTile::printTile() {
	//if the Tile has resources, print each one
	if (resources != nullptr) {

		char topLeft = getResourceChar(this->res_vctr[Corners::TOP_LEFT]);
		char topRight = getResourceChar(this->res_vctr[Corners::TOP_RIGHT]);
		char bottomLeft = getResourceChar(this->res_vctr[Corners::BOTTOM_LEFT]);
		char bottomRight = getResourceChar(this->res_vctr[Corners::BOTTOM_RIGHT]);
		
		if (!(*getIsFaceUp()))
		{
			topLeft = 'X';
			topRight = 'X';
			bottomLeft = 'X';
			bottomRight = 'X';
		}

		std::cout << std::setfill('-') << std::setw(11) << "\n|" << topLeft << std::setfill(' ') << std::setw(6) << topRight << "|\n";
		std::cout << "|" << std::setfill(' ') << std::setw(9) << "|\n";
		std::cout << "|" << bottomLeft << std::setfill(' ') << std::setw(6) << bottomRight << "|\n";
		std::cout << std::setfill('-') << std::setw(11) << "\n";
	}

	//else print as an empty tile on the GameBoard
	else {
		std::cout << std::setfill('-') << std::setw(10) << "\n";
		for (int i = 0; i < 3; ++i) {
			std::cout << "|" << std::setfill(' ') << std::setw(9) << "|\n";
		}
		std::cout << std::setfill('-') << std::setw(10) << "\n";
	}
}

void HarvestTile::setHarvestTileResources(std::vector<ResourceTypes> res) {

	//Set statically resources for now
	if (res.size() == 2) {

		res_vctr.push_back(new ResourceTypes(res[0]));  //topLeft
		res_vctr.push_back(new ResourceTypes(res[0]));  //topRight
		res_vctr.push_back(new ResourceTypes(res[1]));  //bottomLeft
		res_vctr.push_back(new ResourceTypes(res[1]));  //bottomRight
	}

	else if (res.size() == 3) {
		res_vctr.push_back(new ResourceTypes(res[1]));  //topLeft
		res_vctr.push_back(new ResourceTypes(res[1]));  //topRight
		res_vctr.push_back(new ResourceTypes(res[0]));  //bottomLeft
		res_vctr.push_back(new ResourceTypes(res[2]));  //bottomRight
	}

}

void HarvestTile::printTopResources() {

	//if the Tile has resources, print each one
	if (resources != nullptr) {

		char topLeft = getResourceChar(this->res_vctr[Corners::TOP_LEFT]);
		char topRight = getResourceChar(this->res_vctr[Corners::TOP_RIGHT]);

		if (!(*getIsFaceUp()))
		{
			topLeft = 'X';
			topRight = 'X';
		}

		std::cout << "  |" << topLeft << std::setfill(' ') << std::setw(6) << topRight << "|   ";
	}

	//else print as an empty tile on the GameBoard
	else {
		std::cout << "  |       |   ";
	}
}

void HarvestTile::printBottomResources() {

	//if the Tile has resources, print each one
	if (resources != nullptr) {

		std::cout << "  |";
		char bottomLeft = getResourceChar(this->res_vctr[Corners::BOTTOM_LEFT]);
		char bottomRight = getResourceChar(this->res_vctr[Corners::BOTTOM_RIGHT]);

		if (!(*getIsFaceUp()))
		{
			bottomLeft = 'X';
			bottomRight = 'X';
		}

		std::cout << bottomLeft << std::setfill(' ') << std::setw(6) << bottomRight << "|   ";
	}

	//else print as an empty tyle on the GameBoard
	else {
		std::cout << "  |       |   ";
	}
}

//Return the first char of the Resource, in order to print only a character in the GameBoard
char HarvestTile::getResourceChar(ResourceTypes *resource) {
	
	char res;
	
	switch (*resource)
	{
	case WHEATFIELD: res = ResourceTypesStrings[0][0];   break;
	case MEADOW:  res = ResourceTypesStrings[1][0];  break;
	case FOREST:  res = ResourceTypesStrings[2][0];  break;
	case QUARRY:  res = ResourceTypesStrings[3][0];  break;
	}

	return res;
}

void HarvestTile::setRandomHarvestTile() {
	int int1, int2, int3, int4;
	do {
		int1 = rand() % 4;
		int2 = rand() % 4;
		int3 = rand() % 4;
		int4 = rand() % 4;
	} while (
		(int1 == int2 && int1 == int3 && int1 == int4) ||
		(int1 == int2 && int1 == int3) ||
		(int1 == int3 && int1 == int4) ||
		(int2 == int3 && int2 == int4) ||
		(int3 == int1 && int3 == int4)
		);

	std::vector<int> v = { int1, int2, int3, int4 };

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(v.begin(), v.end(), g);

	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";

	ResourceTypes resourceType1, resourceType2, resourceType3, resourceType4;

	resourceType1 = static_cast<ResourceTypes>(v.at(0));
	resourceType2 = static_cast<ResourceTypes>(v.at(1));
	resourceType3 = static_cast<ResourceTypes>(v.at(2));
	resourceType4 = static_cast<ResourceTypes>(v.at(3));


	this->resources = new int(*this->NUM_CORNERS);

	this->setCornerResource(Corners::TOP_LEFT, resourceType1);
	this->setCornerResource(Corners::TOP_RIGHT, resourceType2);
	this->setCornerResource(Corners::BOTTOM_LEFT, resourceType3);
	this->setCornerResource(Corners::BOTTOM_RIGHT, resourceType4);

	this->TopLeftResource = new Corner(resourceType1);
	this->TopRightResource = new Corner(resourceType2);
	this->BottomLeftResource = new Corner(resourceType3);
	this->BottomRightResource = new Corner(resourceType4);
}

void HarvestTile::resetCornerCount() {
	this->TopLeftResource->setHasBeenCounted(false);
	this->TopRightResource->setHasBeenCounted(false);
	this->BottomLeftResource->setHasBeenCounted(false);
	this->BottomRightResource->setHasBeenCounted(false);
}