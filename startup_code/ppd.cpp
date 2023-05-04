#include <iostream>
#include "LinkedList.h"
// Added to make line "std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');" work
#include <limits>
/* This handles the opening and closing of files. Taken from: 
https://www.w3schools.in/cplusplus/working-with-files#:~:text=Opening%20a%20File%20in%20C%2B%2B,-The%20first%20operation&text=The%20syntax%20of%20opening%20a,flags%20used%20for%20file%20opening.*/
#include <fstream>
// For function of previous assignment
#include "helper.h"
// For convenience
using namespace std;

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/

void printMainMenu() {
    std::cout << "Main Menu:\n" 
            << "\t0. test Linked List\n" // delete this in the final code
            << "\t1. Display Items\n" 
            << "\t2. Purchase Items\n" 
            << "\t3. Save and Exit\n" 
            << "Administrator-Only Menu:\n"
            << "\t4. Add Item\n"
            << "\t5. Remove Item\n"
            << "\t6. Display Coins\n"
            << "\t7. Reset Stock\n"
            << "\t8. Reset Coins\n" 
            << "\t9. Abort Program\n"
            << "Select your option (1-9):";
}

// This is the purchase item function.
void purchaseItem(LinkedList* LinkedList);
void printChange(int change);

// delete this function in the final code
void useLinkedList();

int main(int argc, char **argv)
{
    // make the vending machine linked list.
    LinkedList vendingMachine;
    // Holds the coin values.
    int coinDenomination = 8;
    int* coinPurse = new int[coinDenomination];
    int* coinValues = new int[coinDenomination];
    /* validate command line arguments */
    bool allowedArgs = true;
    if (argc != 3) {
        cout << "You may have not entered the right arguments." << endl;
        allowedArgs = false;
    }
    // Adding requried documents.
    else {
        // Reading the data inserted.
        string coinsDat = argv[1];
        string stockDat = argv[2];
        // Reading files
        string line;
        // Save the stock file as a linked list.
        ifstream myfile(stockDat);
        if (myfile.is_open()) {
            while (getline(myfile, line)) {
                // Local variables
                string item_id, item_name, item_desc;
                double item_price;
                int item_stock;
                // Split string function by delimter.
                std::vector<std::string> stockTokens;
                string delimiter = "|";
                Helper::splitString(line,stockTokens,delimiter);
                // Giving values
                item_id = stockTokens[0];
                item_name = stockTokens[1];
                item_desc = stockTokens[2];
                item_price = std::stod(stockTokens[3]);
                item_stock = std::stoi(stockTokens[4]);
                // Create node
                Stock* stock = new Stock(item_id, item_name, item_desc, item_price, item_stock);
                // Append node to end of linked list
                vendingMachine.addBack(stock);
            }
            // Failed to open
            myfile.close();
        }
        else {
            allowedArgs = false;
            cout << "Unable to open stock file" << endl;
        }
        // Save the coin file as array since fixed array size of eight.
        ifstream coinFile(coinsDat);
        if (coinFile.is_open()) {
            int count = 0;
            while (getline(coinFile, line)) {
                std::vector<std::string> coinToken;
                string delimiter = ",";
                Helper::splitString(line,coinToken,delimiter);
                coinValues[count] = std::stoi(coinToken[0]);
                coinPurse[count] = std::stoi(coinToken[1]);
            }
            coinFile.close();
        }
        else {
            allowedArgs = false;
            cout << "Unable to open coin file" << endl;
        }
    }
    
    // Testing
    if (allowedArgs) {
        purchaseItem(&vendingMachine);
    }
    
    int choice = -1;

    while (!(choice == 3 || choice == 9) && !std::cin.eof() && allowedArgs) {
        
        printMainMenu();
        std::cin >> choice;
        std::cout << std::endl;

        if (choice == 0) {
            useLinkedList();
        }
        else if (choice == 1) {
            vendingMachine.printItems();
            cout << endl;
        } else if (choice == 2) {
            std::cout << "Purchase Items" << std::endl;
        } else if (choice == 3) {
            std::cout << "Save and Exit" << std::endl;
        } else if (choice == 4) {
            std::cout << "Add Item" << std::endl;
        } else if (choice == 5) {
            std::cout << "Remove Item" << std::endl;
        } else if (choice == 6) {
            std::cout << "Display Coins" << std::endl;
        } else if (choice == 7) {
            std::cout << "Reset Stock" << std::endl;
        } else if (choice == 8) {
            std::cout << "Reset Coins" << std::endl;
        } else if (choice == 9) {
            std::cout << "Abort Program" << std::endl;
        } else if (!std::cin.eof()) {
            if (std::cin.fail()) {
                std::cout << "Error: input was not a number. Please try again." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                std::cout << "Error: menu item selected is not valid." << std::endl;
            }
        } 
    }
    
    // This stops it from showing when not fitting condition
    if (allowedArgs) {
        std::cout << "\nJust a test, nothing implemented yet!" << std::endl;
    }
    
    return EXIT_SUCCESS;
}

// delete this function in the final code

void useLinkedList() {
    // The stock data should be stored in linked list in this format
    // Stock(id="", name="", description="", price=0.0, on_hand=20)  defult initialization
    Stock* stock1 = new Stock("I0001", "Burger", "A cheese burger", 12.99, 10);
    Stock* stock2 = new Stock("I0002", "Pizza", "A big pizza", 15.99, 10);
    Stock* stock3 = new Stock("I0003", "Tea", "Black tea", 6.75, 10);
    Stock* stock4 = new Stock("I0004", "Fruit", "any fruit", 0.95, 10);
    Stock* stock5 = new Stock("I0005", "Apple Pie", "description", 1.5, 100);

    LinkedList list;

    list.addFront(stock1);
    list.addBack(stock2);
    list.addFront(stock3);
    list.addBack(stock4);
    list.addAt(stock5, 2); // addAt(data, index) I think it will probably be used rarely
    // or use this: which the on_hand param has initialized 20 in defult
    list.addFront(new Stock("I0006", "Lemon Tart", "description", 3.75)); 
    // print items
    list.printItems();

    list.removeBack();
    list.removeFront();
    list.removeAt(2);
    list.remove("I0002");
    list.sort();
   
    list.printItems();
   
    // get() will return nullptr when id not found
    Stock* data = list.get("I0003");
    if (data != nullptr) {
        std::cout << std::endl;
        std::cout<< "Name: " << data->name << "\n"
            << "ID: " << data->id << "\n"
            << "Stock: "<< data->on_hand << "\n"
            << "Price: \n"
            << "\tdollars: "<< data->price.dollars << "\n"
            << "\tcents: "<< data->price.cents << "\n"
            << "Description: " << data->description << std::endl;
    } else {
        std::cout << "Item not found" << std::endl;
    }
};

void purchaseItem(LinkedList* LinkedList) {
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;
    cout << "Please enter the id of the item you wish to purchase:";
    std::string itemId;
    std::getline(std::cin, itemId);
    Helper::strip(itemId);
    Stock* item = (*LinkedList).get(itemId);
    if ((item != nullptr) & (item->on_hand > 0)) {
        // Printing the item
        cout << "You have selected \"";
        cout << item->name;
        cout << " - ";
        cout << item->description;
        cout << "\". This will cost you $ ";
        // Set local variables.
        // Price cost = item->price;
        int dollar = item->price.dollars;
        int cent = item->price.cents;
        string money = std::to_string(dollar) + "." + std::to_string(cent);
        cout << money << "." << endl;
        // Continuation
        cout << "Please hand over the money - type in the value of each note/coin in cents.\nPress enter or ctrl-d on a new line to cancel this purchase:\n";
        // Test variable
        bool validAnswer = true;
        int change = dollar*100 + cent;
        while (validAnswer) {
            dollar = change / 100;
            cent = change % 100;
            cout << "You still need to give us $" << dollar << "." << cent << ": ";
            std::getline(std::cin, itemId);
            Helper::strip(itemId);
            // Base termination case:
            if ((std::cin.eof()) || (itemId == "")) {
                cout << "Pressed crtl-d or enter" << endl;
                validAnswer = false;
            }
            // Success case:
            else {
                change = change - std::stoi(itemId);
                if (change <= 0) {
                    change = abs(change);
                    cout << change << endl;
                    cout << "Here is your " << item->name << " and your change of $ " << change / 100 << "." << change % 100 << ": ";
                    printChange(change);
                    cout << endl;
                    validAnswer = false;
                }
            }
        }
    }
    else {
        cout << "Item not in machine" << endl;
    }
}

void printChange(int change) {
    if (change / 1000 > 0) {
        for (int i = 0; i < (change / 1000); i++) {
            cout << "$10 ";
        }
        change %= 1000;
    }
    if (change / 500 > 0) {
        cout << "$5 ";
        change %= 500;
    } 
    if (change / 200 > 0) {
        cout << "$2 ";
        change %= 200;
    }
    if (change / 100 > 0) {
        cout << "$1 ";
        change %= 100;
    }
    if (change / 50 > 0) {
        cout << "50c ";
        change %= 50;
    }
    if (change / 20 > 0) {
        cout << "20c ";
        change %= 20;
    }
    if (change / 10 > 0) {
        cout << "10c ";
        change %= 10;
    }
    if (change / 5 > 0) {
        cout << "5c ";
        change %= 5;
    }
}