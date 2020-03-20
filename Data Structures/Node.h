//
// Created by Zachary Hynes on 2020-02-07.
//

#ifndef COMP345_NEWHAVENPROJECT_NODE_H
#define COMP345_NEWHAVENPROJECT_NODE_H
#include <iostream>
#include <string>
#include "../Abstract Classes/AbstractGameTile.h"

class Node {
public:
    //=========================
    // CONSTRUCTORS & DESTRUCTORS
    //=========================
    Node();

    Node(int &nodeValue);

    Node(
        Node &leftNode,
        Node &rightNode,
        Node &topNode,
        Node &bottomNode
    );

    Node(
        Node &leftNode,
        Node &rightNode,
        Node &topNode,
        Node &bottomNode,
        int &nodeValue
    );

    ~Node();


    //=========================
    // GETTERS & SETTERS
    //=========================
    //===============
    // NODE VALUE
    //===============
    int *getNodeValue() const {
        return nodeValue;
    }

    void setNodeValue(int *nodeValue) {
        Node::nodeValue = nodeValue;
    }

    //===============
    // GAME TILE
    //===============
    AbstractGameTile *getGameTile() const {
        return gameTile;
    }

    void setGameTile(AbstractGameTile *gameTile) {
        Node::gameTile = gameTile;
    }

    //===============
    // LEFT NODE
    //===============
    Node *getNodeOnLeftEdge() const {
        return nodeOnLeftEdge;
    }

    void setNodeOnLeftEdge(Node *leftEdge) {
        Node::nodeOnLeftEdge = leftEdge;

        if (nodeOnLeftEdge->getNodeOnRightEdge() == nullptr || nodeOnLeftEdge->getNodeOnRightEdge() != this) {
            nodeOnLeftEdge->setNodeOnRightEdge(this);
        }
    }

    void removeEdgeToNodeOnLeft() {
        Node::nodeOnLeftEdge = this->getNodeOnLeftEdge();

        if (nodeOnLeftEdge != nullptr) {
            nodeOnLeftEdge->setNodeOnRightEdge(nullptr);
            this->setNodeOnLeftEdge(nullptr);
        }
    }

    //===============
    // RIGHT NODE
    //===============
    Node *getNodeOnRightEdge() const {
        return nodeOnRightEdge;
    }

    void setNodeOnRightEdge(Node *rightEdge) {
        Node::nodeOnRightEdge = rightEdge;

        if (nodeOnRightEdge->getNodeOnLeftEdge() == nullptr || nodeOnRightEdge->getNodeOnLeftEdge() != this) {
            nodeOnRightEdge->setNodeOnLeftEdge(this);
        }
    }

    void removeEdgeToNodeOnRight() {
        Node::nodeOnRightEdge = this->getNodeOnRightEdge();

        if (nodeOnRightEdge != nullptr) {
            nodeOnRightEdge->setNodeOnLeftEdge(nullptr);
            this->setNodeOnRightEdge(nullptr);
        }
    }

    //===============
    // TOP NODE
    //===============
    Node *getNodeOnTopEdge() const {
        return nodeOnTopEdge;
    }

    void setNodeOnTopEdge(Node *topEdge) {
        Node::nodeOnTopEdge = topEdge;

        if (nodeOnTopEdge->getNodeOnBottomEdge() == nullptr || nodeOnTopEdge->getNodeOnBottomEdge() != this) {
            nodeOnTopEdge->setNodeOnBottomEdge(this);
        }
    }

    void removeEdgeNodeOnTop() {
        Node::nodeOnTopEdge = this->getNodeOnTopEdge();

        if (nodeOnTopEdge != nullptr) {
            nodeOnTopEdge->setNodeOnBottomEdge(nullptr);
            this->setNodeOnTopEdge(nullptr);
        }
    }

    //===============
    // BOTTOM NODE
    //===============
    Node *getNodeOnBottomEdge() const {
        return nodeOnBottomEdge;
    }

    void setNodeOnBottomEdge(Node *bottomEdge) {
        Node::nodeOnBottomEdge = bottomEdge;

        if (nodeOnBottomEdge->getNodeOnTopEdge() == nullptr || nodeOnBottomEdge->getNodeOnTopEdge() != this) {
            nodeOnBottomEdge->setNodeOnTopEdge(this);
        }
    }

    void removeEdgeToNodeOnBottom() {
        Node::nodeOnBottomEdge = this->getNodeOnBottomEdge();

        if (nodeOnBottomEdge != nullptr) {
            nodeOnBottomEdge->setNodeOnTopEdge(nullptr);
            this->setNodeOnBottomEdge(nullptr);
        }
    }


    //=========================
    // FUNCTIONS
    //=========================
    void debugNode();


private:
    //=========================
    // CLASS PROPERTIES
    //=========================
    int* nodeValue;
    AbstractGameTile* gameTile;
    Node* nodeOnLeftEdge;
    Node* nodeOnRightEdge;
    Node* nodeOnTopEdge;
    Node* nodeOnBottomEdge;
};


#endif //COMP345_NEWHAVENPROJECT_NODE_H
