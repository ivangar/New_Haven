//
// Created by Ivan Garzon on 2020-02-11.
//

#ifndef COMP345_NEWHAVENPROJECT_HARVESTTILE_H
#define COMP345_NEWHAVENPROJECT_HARVESTTILE_H
#include "../Abstract Classes/AbstractGameTile.h"
#include "../Enums/ResourceTypes.h"
#include "../Enums/CornersTypes.h"
#include <iostream>
#include <string>
#include <vector>

class Corner {
public:

	Corner();
	Corner(ResourceTypes r1);
	~Corner();
	ResourceTypes getResourceType() {
		return resource;
	}

	void setResourceType(ResourceTypes r1) {
		this->resource = r1;
	}

	bool getHasBeenCounted() {
		return hasBeenCounted;
	}

	void setHasBeenCounted(bool counted) {
		hasBeenCounted = counted;
	}
private:
	ResourceTypes resource;
	bool hasBeenCounted;
};

class HarvestTile: public AbstractGameTile {
public:

	HarvestTile();
	HarvestTile(std::vector<ResourceTypes> res);
	HarvestTile(ResourceTypes r1, ResourceTypes r2, ResourceTypes r3, ResourceTypes r4);
	HarvestTile(const HarvestTile& copy_ht);    // Copy Constructor
	HarvestTile(HarvestTile&& ht);              // Move Constructor
	~HarvestTile();

	/** Operator Overloads **/
	HarvestTile& operator=(HarvestTile&& ht);

	void setCornerResource(enum Corners pos, enum ResourceTypes resourceType) {
		this->res_vctr.insert(this->res_vctr.begin() + pos, new ResourceTypes(resourceType));  //inserting at a specific pos
	}
	ResourceTypes getResourceType(enum Corners pos) const {
		return *res_vctr[pos];
	}
	void setHarvestTileResources(std::vector<ResourceTypes> res);
	void setRandomHarvestTile();
	char getResourceChar(ResourceTypes *resource);
	void printTopResources();
	void printBottomResources();
	void printHarvestTile();		// Used to print a string version of the tile
	int* getResources() {
		return resources;
	}
	void printTile() override;		// Used to print the tiles on the Game board

	int getNodeValue() {
		return nodeValue;
	}

	void setNodeValue(int nodeVal) {
		nodeValue = nodeVal;
	}

	Corner* getTopLeftResource() {
		return TopLeftResource;
	}
	Corner* getTopRightResource() {
		return TopRightResource;
	}
	Corner* getBottomLeftResource() {
		return BottomLeftResource;
	}
	Corner* getBottomRightResource() {
		return BottomRightResource;
	}

	void resetCornerCount();

private:
	const int corners = 4;
	const int *NUM_CORNERS = &corners;
	int* resources;
	std::vector<ResourceTypes *> res_vctr;
	int nodeValue;
	Corner* TopLeftResource;
	Corner* TopRightResource;
	Corner* BottomLeftResource;
	Corner* BottomRightResource;
};

#endif