#ifndef NODE_H
#define NODE_H
#include <string> 
#include <cmath>
#include "Coin.h"


//The length of the id string not counting the nul terminator
#define IDLEN 5

//The maximum length of a product name not counting the nul terminator
#define NAMELEN 40

//The maximum length of a product description not counting the nul terminator.
#define DESCLEN 255

//The default coin level to reset the coins to on request
#define DEFAULT_COIN_COUNT 20

//The default stock level that all new stock should start at and that we should reset to on restock
#define DEFAULT_STOCK_LEVEL 20

//The number of denominations of currency available in the system 
#define NUM_DENOMS 8

/**
 * a structure to represent a price. One of the problems with the floating
 * point formats in C++ like float and double is that they have minor issues
 * of inaccuracy due to rounding. In the case of currency this really is
 * not acceptable so we introduce our own type to keep track of currency.
 **/
class Price
{
public:
    // The dollar value, and the cents value for some price
    unsigned dollars, cents;
};

/**
 * data structure to represent a stock item within the system
 **/
class Stock
{
public:
    //the unique id for this item
    std::string id;

    //the name of this item
    std::string name;
    
    //the description of this item   
    std::string description;
    
    //the price of this item
    Price price;
    
    // how many of this item do we have on hand? 
    unsigned on_hand;

    /**
     * @brief Initialize a Stock class
     *
     * @param id The given ID (string type)
     * @param name The name of the item (string type)
     * @param description The description of item (string type)
     * @param price The price of the item, 12.50 as 12 dollars and 50 cents
     * @param on_hand The quantity of the item
     */
    Stock(std::string id="", std::string name="", std::string description="", double price=0, unsigned on_hand=DEFAULT_STOCK_LEVEL);
    ~Stock();
};

/**
 * the node that holds the data about an item stored in memory
 **/
class Node
{
public:
    Node();
    Node(Stock* data, Node* next = nullptr);
    ~Node();
    // pointer to the data held for the node 
    Stock* data;
    // pointer to the next node in the list 
    Node* next;
};

/**
 * try 2d LL implementation
 * if not working delete
*/
// class OuterNode 
// {
// public:
//     OuterNode();
//     OuterNode(Stock* data, Node* innerHead = nullptr, OuterNode* next = nullptr);
//     ~OuterNode();
//     // pointer to the data held for the outer node 
//     Stock* data;
//     // pointer to innerNode's head
//     Node* innerHead;
//     // pointer to the next outer node in the list
//     OuterNode* next;
// };

#endif // NODE_H