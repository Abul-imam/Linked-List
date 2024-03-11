/**************************
Name: Abul Imam
Assignment: 6
Purpose of the file: This file contains all
the directives needed for linkedlist.cpp to run.
***************************/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "string"
#include "data.h"

using std::cout;
using std::endl;
using std::string;

class LinkedList{
    /*********************************************
     * This LinkedList class works with 2 ADTs:(struct:Data) that stores
     * (id,data) and (struct:Node) that stores (Data,next,prev). It supports
     * operations such as: adding, deleting, printing, finding, and clearing the list.
     * 
     * @attrib *head : Node pointer that points to the 1st Node of the List. 
     * *********************************************/

public:
    /**********************
     * Constructors/Destructor
     **********************/
    LinkedList();
    ~LinkedList();

    /**********************
     * Getters/Accessors
     **********************/ 
    bool getNode(int, Data*);
    bool exists(int);
    void printList(bool = false);
    int getCount();
    
    /**********************
     * Setters/Mutators
     **********************/
    bool addNode(int, string*);
    bool deleteNode(int);   
    bool clearList();
    
private:
    Node *head;

    /**********************
     * Setters/Mutators
     **********************/
    Node* createNewNode(int, string*);
    bool addHead(Node*, Node*);
    bool addTail(Node*, Node*);
    bool addMiddle(Node*, Node*);

};
#endif /* LINKEDLIST_H */