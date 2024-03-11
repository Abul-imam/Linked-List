/**************************
Name: Abul Imam
Assignment: 6
Purpose of the file: This file creates a
functional doubly LinkedList class that can store
a struct-Data (id, data) in ascending order which
can be accessed using node pointers (head, next, prev).
***************************/

#include "linkedlist.h"

LinkedList::LinkedList() {
    /*****************************************
    Constructor : Sets the Node head pointer to NULL / List = empty

    @param na : na
    @return na : na
    @exception na : na 
    *********************************************/
    head = NULL;
}

LinkedList::~LinkedList() {
    /*****************************************
    Destructor: clearList() is called which deallocates all the memory
    and sets head = NULL. Prevents memory leak.
    *********************************************/
    clearList();
}

bool LinkedList::addHead(Node *current, Node *newNode) {
    /*****************************************
    Adds a new HEAD to the list (1st Node). It receives the current
    and new node pointer from addNode() and properly places the new node as the new head.

    @param *current : Node pointer of the current position passed from addNode().
    Its the node after the head.
    @param *newNode : Node pointer of the new node that needs to be set as the new head.
    @return (bool) : Returns True if the new head is added. 
    @exception na : na
    *********************************************/
    current->prev = newNode;
    newNode->next = current;
    newNode->prev = NULL;
    head = newNode;
    return true;
}

bool LinkedList::addTail(Node *current, Node *newNode) {
    /*****************************************
    Adds a new TAIL to the list (Last Node). It receives the current
    and new node pointer from addNode() and properly places the new node to the end of the list.

    @param *current : Node pointer of the current position passed from addNode().
    Its pointing to the last node.
    @param *newNode : Node pointer of the new node that needs to be set as the last node.
    @return (bool) : Returns True if the last node is added. 
    @exception na : na
    *********************************************/
    newNode->next = NULL;
    newNode->prev = current;
    current->next = newNode;
    return true;
}

bool LinkedList::addMiddle(Node *current, Node *newNode) {
    /*****************************************
    Adds a new MIDDLE NODE to the list. It receives the current and new node
    pointer from addNode() and properly places the new node in the middle of 2 nodes.

    @param *current : Node pointer of the current position passed from addNode().
    Its pointing to the node one place after we want the new node to be.
    @param *newNode : Node pointer of the new node.
    @return (bool) : Returns True if the new node is added. 
    @exception na : na
    *********************************************/
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
    return true;
}

Node* LinkedList::createNewNode(int id, string *info) {
    /*****************************************
    Allocates memory for a new node and stores the id & info inside it.
    Sets the prev and next pointers to NULL to avoid memory errors.

    @param id : int value placed inside the new node.
    @param *info : string pointer that will be stored in the new node.
    @return (Node*) : Returns the new node pointer as reference. 
    @exception na : na
    *********************************************/
    Node *newNode = new Node;
    newNode->data.id = id;
    newNode->data.data = *info;
    newNode->prev = newNode->next = NULL; 
    return newNode;
}

bool LinkedList::addNode(int id, string *info) {
    /*****************************************
    Checks for positive id and non-empty string. If the list is empty,
    it adds a new head. Otherwise, it forward traverses through the list
    if the id is greater. Once the right position is found, it cheecks for
    duplicate id and calls the correct add method (head, tail or middle).

    @param id : int value that will be stored in the new node.
    @param *info : string pointer that will be stored in the new node.
    @return (bool) : Returns true/false based on added/not added. 
    @exception na : na
    *********************************************/
    bool added = false;
    if (id > 0 && *info != "") {     
        if (head == NULL) {
            head = createNewNode(id, info);
            added = true;
        } else {
            Node *current = head;
            while(current->next && id > current->data.id) {
                current = current->next;
            }
            if (id != current->data.id) {
                Node *newNode = createNewNode(id, info);
                if (current->prev == NULL && id < current->data.id) {
                    added = addHead(current, newNode);
                } else if (current->next == NULL && id > current->data.id) {
                    added = addTail(current, newNode);
                } else {
                    added = addMiddle(current, newNode);}
            }
        }
    } return added;
}

bool LinkedList::deleteNode(int id) {
    /*****************************************
    Finds the Node with the given id and Deletes/Deallocates
    memory of the node. If the head node is deleted, it assigns the next
    Node as the new head. After deleting a node (current), it sets it to nullptr to
    avoid segmentation error.

    @param id : int value that will determine which node will be deleted.
    @return (bool) : Returns true/false based on deleted/not deleted. 
    @exception na : na
    *********************************************/
    bool deleted = false;
    Node *current = head;

    while (current) {
        if (current->data.id == id) {
            if (current == head) {
                head = current->next;
                if (head) {
                    head->prev = NULL; }
            } else {
                current->prev->next = current->next;
                if (current->next) {
                    current->next->prev = current->prev; 
                }
            }
            delete current;
            current = nullptr;
            deleted = true;
        } else {
            current = current->next;
        }
    } return deleted;
}

bool LinkedList::getNode(int id, Data *empty) {
    /*****************************************
    It checks for the Node that contains the particular id and returns
    the data inside it using reference.

    @param id : int value that will be searched in the list.
    @param *empty : empty struct-Data pointer passed from the caller. This method
    will store the data inside it and pass it to the caller by reference.
    @return (bool) : Returns true/false based on found/not found. 
    @exception na : na
    *********************************************/
    bool found = false;
    Node *current = head;

    empty->id = -1;
    empty->data = "";

    while(current && !found) {
        if (id == current->data.id) {
            empty->id = current->data.id;
            empty->data = current->data.data;
            found = true;
        }
        current = current->next;
    }
    return found;
}

bool LinkedList::exists(int id) {
    /*****************************************
    It checks for the Node that contains the particular id and returns
    true/false based on found/not found.

    @param id : int value that will be searched in the list.
    @return (bool) : Returns true/false based on exist/doesn't exist. 
    @exception na : na
    *********************************************/
    bool exist = false;
    Node *current = head;

    while (current && !exist) {
        if (id == current->data.id) {
            exist = true;
        }
        current = current->next;
    }
    return exist;
}

void LinkedList::printList(bool backward) {
    /*****************************************
    It prints the entire list using traversal algorithm. If defaults to
    backward = false (header file), which means the list is printed forward.

    @param backward : list is printed forward if false, otherwise it prints backwards.
    @return na : na
    @exception na : na
    *********************************************/
    Node *current = head;
    int count = 0;

    if (!head) {
        cout << "        List is Empty" << endl;
    } else {
        if (!backward) {
            while (current) {
                cout << "        " << ++count << ": " << current->data.id << " : " << current->data.data << endl;
                current = current->next;
            }    
        } else {
            while (current->next) {
                current = current->next;
            }
            while (current) {
                cout << "        " <<  ++count << ": " << current->data.id << " : " << current->data.data << endl;
                current = current->prev;
            }      
        }
    }
}

int LinkedList::getCount() {
    /*****************************************
    It calculates the  #No of node on the fly each time this method is called.

    @param na : na
    @return count : The no of nodes present in the list.
    @exception na : na
    *********************************************/
    int count = 0;
    Node *current = head;

    while (current) {
        count++;
        current = current->next;
    }   
    return count;
}

bool LinkedList::clearList(){
    /*****************************************
    It traverses the linked list and deletes each node one by one until the head
    pointer becomes NULL, indicating that the entire list has been cleared. It 
    declares a *current Node pointer that stores the address of the head pointer. 
    Then it moves head to the next node and deletes the *current pointer (current head).

    @param na : na
    @return bool : True when list is cleared (head=NULL)
    @exception na : na
    *********************************************/

    while (head) {
        Node *current = head;
        head = head->next; 
        delete current;
    }
    head = NULL;

    return true; 
}
