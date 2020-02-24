//
// Created by Zachary Hynes on 2020-02-07.
//

#ifndef COMP345_NEWHAVENPROJECT_GRAPH_H
#define COMP345_NEWHAVENPROJECT_GRAPH_H
#include <iostream>
#include "Node.h"

class Graph {
public:
    //=========================
    // CONSTANTS
    //=========================
    // Max size of game board.
    static const int MAX_NUMBER_OF_NODES = 49;

    //=========================
    // CONSTRUCTORS & DESTRUCTORS
    //=========================
    Graph();

    Graph(int numberOfRows, int numberOfColumns);

    ~Graph();

    //=========================
    // GETTERS & SETTERS
    //=========================
    Node *getTopLeftNode() {
        return topLeftNode;
    }

    void setTopLeftNode(Node &topLeftNode) {
        this->topLeftNode = &topLeftNode;
    }

    int* getNumberOfRows() const {
        return numberOfRows;
    }

    void setNumberOfRows(int *numberOfRows) {
        Graph::numberOfRows = numberOfRows;
    }

    int* getNumberOfColumns() const {
        return numberOfColumns;
    }

    void setNumberOfColumns(int *numberOfColumns) {
        Graph::numberOfColumns = numberOfColumns;
    }

    //=========================
    // FUNCTIONS
    //=========================
    Node* getNodeAtCoordinatesXY(int x, int y);

    void printGraph();

    void debugGraph();

    void debugGraphNode(int nodeToDebug);


private:
    //=========================
    // CLASS PROPERTIES
    //=========================
    Node* topLeftNode;
    int* numberOfRows;
    int* numberOfColumns;
    Node* nodesInGraph[MAX_NUMBER_OF_NODES]{};
};


#endif //COMP345_NEWHAVENPROJECT_GRAPH_H
