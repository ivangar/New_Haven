#include <iostream>
#include <string>
#include "VillageBoard/VGMapDriver.h"
#include "GameBoard/GBMapDriver.h"
#include "Data Structures/Node.h"
#include "Data Structures/Graph.h"
#include "Data Structures/GraphDriver.h"
#include "Player/PlayerDriver.h"
#include "Resources/ResourcesDriver.h"

int main() {
//  GraphDriver::graphTest();
//	VGMapDriver::villageGameBoardMapDriver();
	GBMapDriver::gameBoardMapDriver();
//	ResourcesDriver::resourcesDriver();

  system("pause");
    return 0;
}
