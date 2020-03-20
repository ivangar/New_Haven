//
// Created by Zachary Hynes on 2020-02-09.
//

#include "GraphDriver.h"
#include "Node.h"
#include "Graph.h"

void GraphDriver::graphTest() {
    // Test Nodes
//    Node* node1 = new Node();
//    Node* node2 = new Node();
//    Node* node3 = new Node();
//    Node* node4 = new Node();
//    Node* node5 = new Node();

//    std::cout << "Node1 Address: " << node1 << std::endl;
//    std::cout << std::endl;
//    std::cout << "Node2 Address: " << node2 << std::endl;
//    std::cout << "Node3 Address: " << node3 << std::endl;
//    std::cout << "Node4 Address: " << node4 << std::endl;
//    std::cout << "Node5 Address: " << node5 << std::endl;

//    node1->setNodeValue(new int(10));
//    node2->setNodeValue(new int(20));
//    node3->setNodeValue(new int(30));
//    node4->setNodeValue(new int(40));
//    node5->setNodeValue(new int(50));
//
//    node1->setNodeOnLeftEdge(node2);
//    node1->setNodeOnRightEdge(node3);
//    node1->setNodeOnTopEdge(node4);
//    node1->setNodeOnBottomEdge(node5);

//    node1->debugNode();
//    node2->debugNode();
//    node3->debugNode();
//    node4->debugNode();
//    node5->debugNode();



    // Test Game Board Graph
//    Graph* graph1 = new Graph(7, 7);
//
//    graph1->debugGraphNode();
//    graph1->debugGraphNode(0);
//    graph1->debugGraphNode(3);
//    graph1->debugGraphNode(6);
//    graph1->debugGraphNode(21);
//    graph1->debugGraphNode(24);
//    graph1->debugGraphNode(27);
//    graph1->debugGraphNode(42);
//    graph1->debugGraphNode(45);
//    graph1->debugGraphNode(48);
//
//    graph1->debugGraph();


    // Test Village Board Graph
    Graph* graph2 = new Graph(6,5);

    graph2->debugGraph();
    graph2->debugGraphNode(0);
    graph2->debugGraphNode(2);
    graph2->debugGraphNode(4);
    graph2->debugGraphNode(10);
    graph2->debugGraphNode(17);
    graph2->debugGraphNode(19);
    graph2->debugGraphNode(25);
    graph2->debugGraphNode(27);
    graph2->debugGraphNode(29);


}