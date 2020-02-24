//
// Created by Zachary Hynes on 2020-02-07.
//

#include "Graph.h"

//=========================
// CONSTRUCTORS & DESTRUCTORS
//=========================
Graph::Graph() {
    Graph(7,7);
}

Graph::Graph(int numberOfRows, int numberOfColumns) {
    if ((numberOfRows * numberOfColumns) < Graph::MAX_NUMBER_OF_NODES + 1) {
        this->setNumberOfRows(new int(numberOfRows));
        this->setNumberOfColumns(new int(numberOfColumns));

        // Create graph of nodes and initialize their values.
        for (int i = 0; i < numberOfRows; ++i) {
            for (int j = 0; j < numberOfColumns; ++j) {
                int currentNodeIndex = i * numberOfColumns + j;
                nodesInGraph[currentNodeIndex] = new Node();
                nodesInGraph[currentNodeIndex]->setNodeValue(new int(currentNodeIndex));
            }
        }

        // Set the top left Node of the graph.
        this->topLeftNode = nodesInGraph[0];

        // Create edges between the nodes.
        for (int i = 0; i < numberOfRows; ++i) {
            for (int j = 0; j < numberOfColumns; ++j) {
                int currentNodeIndex = i * numberOfColumns + j;
                Node* currentNode = nodesInGraph[currentNodeIndex];

                if (i == 0 && j == 0) {                                         // If top left corner
                    currentNode->setNodeOnRightEdge(nodesInGraph[currentNodeIndex + 1]);
                    currentNode->setNodeOnBottomEdge(nodesInGraph[currentNodeIndex + numberOfColumns]);
                } else if (i == 0 && j == numberOfColumns - 1) {                // If top right corner
                    currentNode->setNodeOnLeftEdge(nodesInGraph[currentNodeIndex - 1]);
                    currentNode->setNodeOnBottomEdge(nodesInGraph[currentNodeIndex + numberOfColumns]);
                }  else if (i == 0) {                                            // If top row of graph
                    currentNode->setNodeOnLeftEdge(nodesInGraph[currentNodeIndex - 1]);
                    currentNode->setNodeOnRightEdge(nodesInGraph[currentNodeIndex + 1]);
                    currentNode->setNodeOnBottomEdge(nodesInGraph[currentNodeIndex + numberOfColumns]);
                } else if (i == numberOfRows - 1 && j == 0) {                   // If bottom left corner
                    currentNode->setNodeOnRightEdge(nodesInGraph[currentNodeIndex + 1]);
                    currentNode->setNodeOnTopEdge(nodesInGraph[currentNodeIndex - numberOfColumns]);
                } else if (i == numberOfRows - 1 && j == numberOfColumns - 1) { // If bottom right corner
                    currentNode->setNodeOnLeftEdge(nodesInGraph[currentNodeIndex - 1]);
                    currentNode->setNodeOnTopEdge(nodesInGraph[currentNodeIndex - numberOfColumns]);
                } else if (i == numberOfRows - 1)     {                         // If bottom row of graph
                    currentNode->setNodeOnLeftEdge(nodesInGraph[currentNodeIndex - 1]);
                    currentNode->setNodeOnRightEdge(nodesInGraph[currentNodeIndex + 1]);
                    currentNode->setNodeOnTopEdge(nodesInGraph[currentNodeIndex - numberOfColumns]);
                } else if (j == 0) {                                            // If left side of graph
                    currentNode->setNodeOnRightEdge(nodesInGraph[currentNodeIndex + 1]);
                    currentNode->setNodeOnTopEdge(nodesInGraph[currentNodeIndex - numberOfColumns]);
                    currentNode->setNodeOnBottomEdge(nodesInGraph[currentNodeIndex + numberOfColumns]);
                } else if (j == numberOfColumns -1) {                           // If right side of graph
                    currentNode->setNodeOnLeftEdge(nodesInGraph[currentNodeIndex - 1]);
                    currentNode->setNodeOnTopEdge(nodesInGraph[currentNodeIndex - numberOfColumns]);
                    currentNode->setNodeOnBottomEdge(nodesInGraph[currentNodeIndex + numberOfColumns]);
                } else {                                                        // All other nodes
                    currentNode->setNodeOnLeftEdge(nodesInGraph[currentNodeIndex - 1]);
                    currentNode->setNodeOnRightEdge(nodesInGraph[currentNodeIndex + 1]);
                    currentNode->setNodeOnTopEdge(nodesInGraph[currentNodeIndex - numberOfColumns]);
                    currentNode->setNodeOnBottomEdge(nodesInGraph[currentNodeIndex + numberOfColumns]);
                }
            }
        }
    } else {
        std::cout << "ERROR: \tThe number of rows and columns exceeds the capacity allowed by this graph structure."
                    << "\n\t\tPlease try again with a valid number of rows and columns."
                    << std::endl;
    }
}

Graph::~Graph() {
    // TODO: Implement Node destructor algorithm.
}


//=========================
// FUNCTIONS
//=========================
Node* Graph::getNodeAtCoordinatesXY(int rowNumber, int columnNumber) {
    return nodesInGraph[((rowNumber * *numberOfColumns) + columnNumber)];
}

void Graph::printGraph() {
    // TODO: Implement printGraph function.
}

void Graph::debugGraph() {
    std::cout << "Graph at address: " << this << std::endl;

    std::cout << std::endl;

    std::cout << "Graph rows: " << *this->getNumberOfRows() << std::endl;
    std::cout << "Graph columns: " << *this->getNumberOfColumns() << std::endl;

    std::cout << std::endl;

    std::cout << "Graph top-left-most node address: " << std::endl;
    if (this->topLeftNode != nullptr) {
        std::cout << "Node value address: " << &topLeftNode;
        std::cout << ", holds pointer to a Node at address: " << topLeftNode;
        std::cout << ", calling the Node's debug function: " << std::endl;
        topLeftNode->debugNode();
    } else {
        std::cout << "The graph is currently not pointing to any Node." << std::endl;
    }
}

void Graph::debugGraphNode(int nodeToDebug) {
    nodesInGraph[nodeToDebug]->debugNode();
}
