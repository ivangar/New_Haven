//
// Created by Zachary Hynes on 2020-02-07.
//

#include "Node.h"

//=========================
// CONSTRUCTORS & DESTRUCTORS
//=========================
Node::Node() {
    this->nodeOnLeftEdge = nullptr;
    this->nodeOnRightEdge = nullptr;
    this->nodeOnTopEdge = nullptr;
    this->nodeOnBottomEdge = nullptr;
    this->nodeValue = nullptr;
    this->gameTile = nullptr;
}

Node::Node(int &nodeValue) {
    this->nodeOnLeftEdge = nullptr;
    this->nodeOnRightEdge = nullptr;
    this->nodeOnTopEdge = nullptr;
    this->nodeOnBottomEdge = nullptr;
    this->nodeValue = &nodeValue;
    this->gameTile = nullptr;
}

Node::Node(Node &leftNode, Node &rightNode, Node &topNode, Node &bottomNode) {
    this->nodeOnLeftEdge = &leftNode;
    this->nodeOnRightEdge = &rightNode;
    this->nodeOnTopEdge = &topNode;
    this->nodeOnBottomEdge = &bottomNode;
    this->nodeValue = nullptr;
    this->gameTile = nullptr;
}

Node::Node(
        Node &leftNode,
        Node &rightNode,
        Node &topNode,
        Node &bottomNode,
        int &nodeValue
){
    this->nodeOnLeftEdge = &leftNode;
    this->nodeOnRightEdge = &rightNode;
    this->nodeOnTopEdge = &topNode;
    this->nodeOnBottomEdge = &bottomNode;
    this->nodeValue = &nodeValue;
    this->gameTile = nullptr;
}

Node::~Node() {
    // TODO: Implement Node destructor algorithm.
}


//=========================
// FUNCTIONS
//=========================
void Node::debugNode() {
    std::cout << "\nDebugging Node at address: " << this << std::endl;

    std::cout << std::endl;

    std::cout << "Node value: " << std::endl;
    std::cout << "Node value address: " << &nodeValue;
    std::cout << ", holds pointer to address: " << nodeValue;
    std::cout << ", which contains the value: " << *nodeValue << std::endl;

    std::cout << std::endl;

    std::cout << "Connected nodes: " << std::endl;
    std::cout << "Left Edge address: " << &nodeOnLeftEdge;
    std::cout << ", holds pointer to Node at address: " << nodeOnLeftEdge;
    std::cout << ", which contains the value: ";
    if (nodeOnLeftEdge != nullptr) {
        std::cout << *nodeOnLeftEdge->getNodeValue();
    } else {
        std::cout << "null";
    }
    std::cout << std::endl;

    std::cout << "Right Edge address: " << &nodeOnRightEdge;
    std::cout << ", holds pointer to Node at address: " << nodeOnRightEdge;
    std::cout << ", which contains the value: ";
    if (nodeOnRightEdge != nullptr) {
        std::cout << *nodeOnRightEdge->getNodeValue();
    } else {
        std::cout << "null";
    }
    std::cout << std::endl;

    std::cout << "Top Edge address: " << &nodeOnTopEdge;
    std::cout << ", holds pointer to Node at address: " << nodeOnTopEdge;
    std::cout << ", which contains the value: ";
    if (nodeOnTopEdge != nullptr) {
        std::cout << *nodeOnTopEdge->getNodeValue();
    } else {
        std::cout << "null";
    }
    std::cout << std::endl;

    std::cout << "Bottom Edge address: " << &nodeOnBottomEdge;
    std::cout << ", holds pointer to Node at address: " << nodeOnBottomEdge;
    std::cout << ", which contains the value: ";
    if (nodeOnBottomEdge != nullptr) {
        std::cout << *nodeOnBottomEdge->getNodeValue();
    } else {
        std::cout << "null";
    }
    std::cout << std::endl;
}
