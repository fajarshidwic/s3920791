#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // more functions to be added perhaps...
    Node* getHead();

    void addFront(Stock* data);
    void addBack(Stock* data);
    void addAt(Stock* data, unsigned index);
    
    void removeFront();
    void removeBack();
    void removeAt(unsigned index);
    void remove(std::string id);
    
    /**
     * @brief Throw id serach item in stock
     *
     *@param id The given ID (string type)
     *@return a printer of a item
     *@return nullptr if item not found
     */
    Stock* get(std::string id);
    
    void sort();

    void printItems();
    void printItems(std::ostream& outfile);

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;

    // Helper functions for sort (I used merge sort for Linked List)
    void splitList(Node* source, Node** front, Node** back);
    Node* mergeLists(Node* a, Node* b);
    Node* mergeSort(Node* head);

};

#endif  // LINKEDLIST_H


