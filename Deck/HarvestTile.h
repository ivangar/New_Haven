//
// Created by Ivan Garzon on 2020-02-11.
//

#ifndef COMP345_NEWHAVENPROJECT_HARVESTTILE_H
#define COMP345_NEWHAVENPROJECT_HARVESTTILE_H
#include "../Abstract Classes/AbstractGameTile.h"
#include "../Enums/ResourceTypes.h"
#include "../Enums/CornersTypes.h"
#include <iostream> 
#include <vector>

class HarvestTile: public AbstractGameTile {
public:

	HarvestTile();
	HarvestTile(std::vector<ResourceTypes> res);
	HarvestTile(ResourceTypes r1, ResourceTypes r2, ResourceTypes r3, ResourceTypes r4);
	~HarvestTile();

	void setCornerResource(enum Corners pos, enum ResourceTypes resourceType) {
		this->res_array.insert(this->res_array.begin() + pos, new ResourceTypes(resourceType));  //inserting at a specific pos
	}
	void setHarvestTileResources(std::vector<ResourceTypes> res);
	char getResourceChar(ResourceTypes *resource);
	void printTopResources();
	void printBottomResources();
	int* getResources() {
		return resources;
	}
	void printTile() override;
	void debugTile() override;

private:
	const int corners = 4;
	const int *NUM_CORNERS = &corners;
	int* resources;
	std::vector<ResourceTypes *> res_array;
};

#endif