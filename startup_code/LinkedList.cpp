#include "LinkedList.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

LinkedList::LinkedList() {
    head = nullptr;
    count = 0;
    purse = new Coin[8];
}

LinkedList::~LinkedList() {
    Node* current = head;
    Node* next = nullptr;
    
    while (current != nullptr) {
        next = current->next;
        delete current->data;
        delete current;
        current = next;
    }
    delete[] purse;
}

Node* LinkedList::getHead() {
    return head;
}

void LinkedList::addFront(Stock* data) {
    Node* newNode = new Node(data, head);
    this->head = newNode;
    count ++;
}

void LinkedList::addBack(Stock *data) {
    Node* newNode = new Node(data);
    if (head != nullptr) {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    } else {
        head = newNode;
    }
    count ++;
}

void LinkedList::addAt(Stock *data, unsigned index) {
    if (index <= count) {
        if (index == 0) {
            addFront(data);
        } else if (index == count) {
            addBack(data);
        } else {
            Node* newNode = new Node(data);
            Node* current = head;
            
            for (unsigned i = 1; i < index; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            count++;
        }
    } else {
        throw std::runtime_error("Index out of range");
    }
}

void LinkedList::removeFront() {
    if (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp->data;
        delete temp;
        count--;
    } else {
        throw std::runtime_error("You can't remove from an empty LinkedList");
    }
}

void LinkedList::removeBack() {
    if (head != nullptr) {
        if (head->next == nullptr) {
            removeFront();
        } else {
            Node* current = head;
            while (current->next->next != nullptr) {
                current = current->next;
            }
            delete current->next->data;
            delete current->next;
            current->next = nullptr;
            count--;
        }
    } else {
        throw std::runtime_error("You can't remove from an empty LinkedList");
    }
}

void LinkedList::removeAt(unsigned index) {
    if (index < count) {
        if (index == 0) {
            removeFront();
        } else if (index == count - 1) {
            removeBack();
        } else {
            Node* current = head;
            for (unsigned i = 1; i < index; ++i) {
                current = current->next;
            }
            Node* toRemove = current->next;
            current->next = toRemove->next;
            delete toRemove->data;
            delete toRemove;
            count--;
        }
    } else {
        throw std::runtime_error("Index out of range");
    }
}

void LinkedList::remove(std::string id) {
    if (head != nullptr) {
        if (head->data->id == id) {
            Node* temp = head;
            head = head->next;
            delete temp->data;
            delete temp;
            count--;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                if (current->next->data->id == id) {
                    Node* temp = current->next;
                    current->next = temp->next;
                    delete temp->data;
                    delete temp;
                    count--;
                    return;
                }
                current = current->next;
            }
        }
    }
}

Stock* LinkedList::get(std::string id) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data->id == id) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

void LinkedList::sort() {
    head = mergeSort(head);
}

void LinkedList::printItems() {
    Node* current = head;
    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    cout << "ID   |Name                                    | Available | Price" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    for (unsigned i=0; i<count; ++i) {
        cout << std::left << std::setw(5) << current->data->id
            << "|" << std::setw(40) << current->data->name
            << "|" << std::setw(11) << current->data->on_hand
            << "|$";
        if (current->data->price.dollars < 10) {
            cout << " ";
        }
        cout << current->data->price.dollars << '.' << std::setw(2) << std::setfill('0') << current->data->price.cents
            << std::setfill(' ')
            << endl;
        current = current->next;
    }
    
}

void LinkedList::printIdOnly() {
    Node* current = head;
    for (unsigned i=0; i<count; ++i) {
        cout << std::left << std::setw(5) << current->data->id << endl;
        current = current->next;
    }
    
}

void LinkedList::printCoinOnly() {
    for (int i=0; i<8; i++) {
        cout << purse->denomination_to_string(purse[i].denom)
            << endl;
    }
    
}

void LinkedList::printCoins(std::ostream& outfile) {
    /*
    1000,3
    */
    for (int i=0; i<8; i++) {
        outfile << purse->denomination_to_string(purse[i].denom)
            << "," << purse[i].count
            << endl;
    }
    
}

void LinkedList::printItems(std::ostream& outfile) {
    sort();
    Node* current = head;
    /*
    I0001|Meat Pie|Yummy Beef in Gravy surrounded by pastry|3.50|50
    I0002|Apple Pie                               |20         |$ 3.00
    */
    for (unsigned i=0; i<count; ++i) {
        outfile << std::left << std::setw(5) << current->data->id
            << "|" << current->data->name
            << "|" << current->data->description
            << "|" << current->data->price.dollars << '.' << std::setw(2) << std::setfill('0') << current->data->price.cents
            << "|" << current->data->on_hand
            << endl;
        current = current->next;
    }
    
}

// Helper Functions

void LinkedList::splitList(Node *source, Node **front, Node **back) {
    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;
    
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    
    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}

Node* LinkedList::mergeLists(Node *a, Node *b) {
    Node* merged = nullptr;

    if (a == nullptr) {
        return b;
    } else if (b == nullptr) {
        return a;
    }

    if (a->data->name < b->data->name) {
        merged = a;
        merged->next = mergeLists(a->next, b);
    } else {
        merged = b;
        merged->next = mergeLists(a, b->next);
    }

    return merged;
}

Node* LinkedList::mergeSort(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    Node* front;
    Node* back;
    splitList(head, &front, &back);

    front = mergeSort(front);
    back = mergeSort(back);

    return mergeLists(front, back);
}
