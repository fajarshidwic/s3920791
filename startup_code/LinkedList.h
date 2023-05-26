#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>
#include "Node.h"

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // Beginning of coins list
    Coin* purse;

    // more functions to be added perhaps...
    Node* getHead();

    void addFront(Stock* data);
    // add 2d linkedlist (fail)
    //  void addBack(Stock* data, OuterNode* outerHead);
    void addBack(Stock* data);
    // add 2d linkedlist (fail)
    //  OuterNode* addBackOuterNode(Stock *data, OuterNode* outerHead = nullptr);
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
    // print 2d linked list (fail)
    // void printItems(OuterNode* current);
    void printItems();
    // print 2d linked list (fail)
    // void printOuterItems();
    void printItems(std::ostream& outfile);
    void printCoins(std::ostream& outfile);
    void printIdOnly();
    void printCoinOnly();

private:
    // the beginning of the list
    Node* head;
   //  OuterNode* outerHead;
  
    // how many nodes are there in the list?
    unsigned count;

    // Helper functions for sort (I used merge sort for Linked List)
    void splitList(Node* source, Node** front, Node** back);
    Node* mergeLists(Node* a, Node* b);
    Node* mergeSort(Node* head);

};

#endif  // LINKEDLIST_H


