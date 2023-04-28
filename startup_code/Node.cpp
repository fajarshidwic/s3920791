#include "Node.h"

Stock::Stock(std::string id, std::string name, std::string description, double price, unsigned on_hand)
: id(id), name(name), description(description), on_hand(on_hand)
{
    price = price * 100;
    this->price.dollars = int(price / 100);
    this->price.cents = int(price - this->price.dollars*100);
}

Stock::~Stock(){
}

Node::Node(){
    data = nullptr;
    next = nullptr;
}

Node::Node(Stock* data, Node* next)
: data(data), next(next) {}

Node::~Node(){
}
