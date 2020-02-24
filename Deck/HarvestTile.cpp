//
// Created by Ivan Garzon on 2020-02-11.
//

#include <iostream>
#include <iomanip> 
#include "HarvestTile.h"

HarvestTile::HarvestTile() {
	this->resources = nullptr;  //amount of resources, if no resources the tile is empty
}

HarvestTile::HarvestTile(ResourceTypes r1, ResourceTypes r2, ResourceTypes r3, ResourceTypes r4) {

	this->resources = new int(*this->NUM_CORNERS);
	//this->res_array.insert(this->res_array.begin() + r1, new ResourceTypes(r1));  //inserting at a specific pos
	this->res_array.push_back(new ResourceTypes(r1));
	this->res_array.push_back(new ResourceTypes(r2));
	this->res_array.push_back(new ResourceTypes(r3));
	this->res_array.push_back(new ResourceTypes(r4));
}

HarvestTile::HarvestTile(std::vector<ResourceTypes> res){
	this->resources = new int(res.size());
	setHarvestTileResources(res);
}

HarvestTile::~HarvestTile() {
	for (std::vector<ResourceTypes*>::iterator res = this->res_array.begin(); res != this->res_array.end(); ++res) {
		delete *res; 
	}
	this->res_array.clear();
	delete this->resources;
	delete this->NUM_CORNERS;
	this->resources = nullptr;
}

void HarvestTile::debugTile() {
	// TODO: Implement debugTile funreturn buildingCost;ction.
}

void HarvestTile::printTile() {
	//if the Tile has resources, print each one
	if (resources != nullptr) {
		char topLeft = getResourceChar(this->res_array[Corners::TOP_LEFT]);
		char topRight = getResourceChar(this->res_array[Corners::TOP_RIGHT]);
		char bottomLeft = getResourceChar(this->res_array[Corners::BOTTOM_LEFT]);
		char bottomRight = getResourceChar(this->res_array[Corners::BOTTOM_RIGHT]);

		std::cout << std::setfill('-') << std::setw(11) << "\n|" << topLeft << std::setfill(' ') << std::setw(6) << topRight << "|\n";
		std::cout << "|" << std::setfill(' ') << std::setw(9) << "|\n";
		std::cout << "|" << bottomLeft << std::setfill(' ') << std::setw(6) << bottomRight << "|\n";
		std::cout << std::setfill('-') << std::setw(11) << "\n";
	}

	//else print as an empty tyle on the GameBoard
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

		res_array.push_back(new ResourceTypes(res[0]));  //topLeft
		res_array.push_back(new ResourceTypes(res[0]));  //topRight
		res_array.push_back(new ResourceTypes(res[1]));  //bottomLeft
		res_array.push_back(new ResourceTypes(res[1]));  //bottomRight
	}

	else if (res.size() == 3) {
		res_array.push_back(new ResourceTypes(res[1]));  //topLeft
		res_array.push_back(new ResourceTypes(res[1]));  //topRight
		res_array.push_back(new ResourceTypes(res[0]));  //bottomLeft
		res_array.push_back(new ResourceTypes(res[2]));  //bottomRight
	}

}

void HarvestTile::printTopResources() {

	//if the Tile has resources, print each one
	if (resources != nullptr) {

		char topLeft = getResourceChar(this->res_array[Corners::TOP_LEFT]);
		char topRight = getResourceChar(this->res_array[Corners::TOP_RIGHT]);
		std::cout << "  |" << topLeft << std::setfill(' ') << std::setw(6) << topRight << "|   ";
	}

	//else print as an empty tyle on the GameBoard
	else {
		std::cout << "  |       |   ";
	}
}

void HarvestTile::printBottomResources() {

	//if the Tile has resources, print each one
	if (resources != nullptr) {

		std::cout << "  |";
		char bottomLeft = getResourceChar(this->res_array[Corners::BOTTOM_LEFT]);
		char bottomRight = getResourceChar(this->res_array[Corners::BOTTOM_RIGHT]);
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