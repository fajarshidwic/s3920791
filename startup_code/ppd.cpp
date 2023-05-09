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
void saveItem(std::string outFileName, LinkedList& vendingMachine);
// This is the purchase item function.
void purchaseItem(LinkedList* LinkedList);
void printChange(int change);

// This is to handle stock.
void addItem(LinkedList& list);
void resetStock(LinkedList& list);
void removeItem(LinkedList& list);

// About coins
void displayCoin();

// delete this function in the final code
// a sample of how to use Linked List
void useLinkedList();

int main(int argc, char **argv)
{
    // Make the vending machine linked list.
    LinkedList vendingMachine;
    // Holds the coin values.
    int coinDenomination = 8;
    int* coinPurse = new int[coinDenomination];
    int* coinValues = new int[coinDenomination];
    /* validate command line arguments */
    bool allowedArgs = true;
    //  save vending machine items in an output file
    std::string outFileName = "output.txt";
    if (argc != 3) {
        cout << "You may have not entered the right arguments." << endl;
        allowedArgs = false;
    }
    // Adding requried documents.
    else {
        // Reading the data inserted.
        string coinsDat = argv[2];
        string stockDat = argv[1];
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

    string choice = "-1";
    bool exit = false;
    while (!std::cin.eof() && !exit && allowedArgs) {
        
        printMainMenu();
        choice = Helper::readInput();
        if (!std::cin.eof()) {
            bool isInt = true;
            int choiceLen = choice.length();
            for (int i = 0; i < choiceLen; ++i){
                if (!isdigit(choice.at(i))){
                    isInt = false;
                }
            }
            if (isInt && choice != "") {
                if (std::stoi(choice) == 0) {
                    useLinkedList();
                }
                else if (std::stoi(choice) == 1) {
                    // This case shows the items on the system.
                    vendingMachine.sort();
                    vendingMachine.printItems();
                    cout << endl;
                } else if (std::stoi(choice) == 2) {
                    std::cout << "Purchase Items" << std::endl;
                    purchaseItem(&vendingMachine);
                } else if (std::stoi(choice) == 3) {
                    exit = true;
                    std::cout << "Save and Exit" << std::endl;
                    saveItem(outFileName, vendingMachine);
                } else if (std::stoi(choice) == 4) {
                    std::cout << "Add Item" << std::endl;
                    addItem(vendingMachine);
                    std::cin.clear();
                } else if (std::stoi(choice) == 5) {
                    // This case delete an item using itemID.
                    removeItem(vendingMachine);
                } else if (std::stoi(choice) == 6) {
                    // TODO: This case shows all coins in the system.
                    displayCoin();
                } else if (std::stoi(choice) == 7) {
                    std::cout << "Reset Stock" << std::endl;
                    resetStock(vendingMachine);
                } else if (std::stoi(choice) == 8) {
                    std::cout << "Reset Coins" << std::endl;
                } else if (std::stoi(choice) == 9) {
                    exit = true;
                    std::cout << "Abort Program" << std::endl;
                } else if (!std::cin.eof()) {
                    std::cout << "Error: menu item selected is not valid." << std::endl;
                }
            } else {
                std::cout << "Error: input was not a number. Please try again." << std::endl;
                std::cin.clear();
                // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    
    // This stops it from showing when not fitting condition
    if (allowedArgs) {
        std::cout << "\nJust a test, nothing implemented yet!" << std::endl;
    }
    
    return EXIT_SUCCESS;
}

void saveItem(std::string outFileName, LinkedList& vendingMachine) {
   std::ofstream outfile(outFileName);
   vendingMachine.printItems(outfile);
}

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
        
        bool paidFor = false;
        int remainingCost = (dollar * 100) + cent;
        string moneyIn;

        // Loop until the item has been paidFor or the user has terminated the loop
        while (paidFor == false) {
            dollar = remainingCost / 100;
            cent = remainingCost % 100;

            cout << "Remaining Cost: $" << dollar << "." << cent << ": ";
            moneyIn = Helper::readInput();
            Helper::strip(moneyIn);

            vector<int> coinsToAdd;
            int coinValues[8] = {5, 10, 20, 50, 100, 200, 500, 1000};
            int arrLen = sizeof(coinValues) / sizeof(int);
            bool validDenomination = false;

            for (int idx = 0; idx < arrLen; idx++) {
                if (stoi(moneyIn) == coinValues[idx]) {
                    validDenomination = true;
                }
            } 

            if ((cin.eof()) || (moneyIn == "")) {
                // Base termination case
                cout << "Pressed ctrl-D or enter" << endl;
                paidFor = true;
            } else if (validDenomination == false) {
                cout << "That is not a valid denomination" << endl;
            } else {
                // Valid Input
                remainingCost -= stoi(moneyIn);

                // Add input to sumVector
                coinsToAdd.push_back(stoi(moneyIn));

                if (remainingCost <= 0) {
                    // User has paid for the item
                    paidFor = true;
                    int change = abs(remainingCost);
                    cout << "Here is your " << item->name << " and your change of $" << change / 100 << "." << change % 100 << ": ";
                    printChange(change);
                    cout << endl;
                
                    // to add
                    // removing stock
                    // removing coins from purse
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
        cout << "$10 ";
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

void addItem(LinkedList& list) {
    bool quit = false;
    bool cancel = false;
    std::string maxID = Helper::maxId(list.getHead());
    std::string newID = Helper::incrementID(maxID);
    // int stepto = 0;
    std::string name, description, price_s;
    std::cout << "The id of the new stock will be: " << newID << std::endl;
    while (!quit && !cancel) {
        std::cout << "Enter the item name: ";
        std::getline(std::cin, name);
        if (name == "" || std::cin.eof()) {
            cancel = true;
        } else {
            quit = true;
        }
    }
    quit = false;
    while (!quit && !cancel) {
        std::cout << "Enter the item description: ";
        std::getline(std::cin, description);
        if (description =="" || std::cin.eof()) {
            cancel = true;
        } else {
            quit = true;
        }
    }
    quit = false;
    double price = 0;
    while (!quit && !cancel) {
        std::cout << "Enter the price for the item: ";
        std::getline(std::cin, price_s);
        if (price_s == "" || std::cin.eof()) {
            cancel = true;
        } else {
            std::vector<std::string> tokens;
            price_s = Helper::strip(price_s);
            if (price_s[0] == '.') {
                price_s.insert(0, "0");
            } else if (price_s[price_s.length()-1] == '.') {
                price_s.append("0");
            }
            
            Helper::splitString(price_s, tokens, ".");
            if (tokens.size() == 2) {
                if (tokens[1].length() == 1) {
                    tokens[1] += "0";
                }
                if (!Helper::isInt(tokens[0]) || !Helper::isInt(tokens[1])){
                    std::cout << "Error: the price is not valid." << std::endl;
                } else if (std::stoi(tokens[0]) > 99 || std::stoi(tokens[0]) < 0) {
                    std::cout << "Error: the dollars are out of range." << std::endl;
                } else if (std::stoi(tokens[1]) > 99 || std::stoi(tokens[1]) < 0) {
                    std::cout << "Error: the cents are out of range." << std::endl;
                } else if (std::stoi(tokens[1])%5) {
                    std::cout << "Error: the cents need to be a multiple of 5." << std::endl;
                } else {
                    price = std::stod(price_s);
                    quit = true;
                }
            } else {
                std::cout << "Error: the price is not valid." << std::endl;
            }
        }
    }
    if (cancel) {
        std::cout << "Cancelling \"add item\" at user's request.\n"
                << "The task Add Item failed to run successfully."
                << std::endl;
        clearerr(stdin);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    } else {
        list.addBack(new Stock(newID, name, description, price));
        std::cout << "This item \"" << name << " - " << description << "\" has now been added to the menu." << std::endl;
    }
    
}

// TODO: ensure that the memory used to store this is removed.
void removeItem(LinkedList& list) {
    cout << "Enter the item id of the item to remove from the menu: ";
    std::string item;
    std::getline(std::cin, item);
    Stock* itemInfo = list.get(item);
    if (itemInfo != nullptr) {
        cout << "\"";
        cout << itemInfo->id;
        cout << " - ";
        cout << itemInfo->name;
        cout << " - ";
        cout << itemInfo->description;
        cout << "\" has been removed from the system." << endl;
        list.remove(item);
    } else {
        cout << "That item does not exist in system." << endl;
    }
}

void resetStock(LinkedList& list){
    Node* upto = list.getHead();
    while (upto != nullptr) {
        upto->data->on_hand = DEFAULT_STOCK_LEVEL;
        upto = upto->next;
    }
}

// TODO: Has to have a way to read coins kept.
void displayCoin() {
    cout << "Coins Summary" << endl;
    cout << Helper::printBorder(13);
    cout << "Denomination    |    Count" << endl;
    // Denom side == 16, count side == 10, Total = 27.
    cout << Helper::printBorder(27);
    cout << Helper::writeOnSize(16, "5 Cents", true) << "|" << Helper::writeOnSize(10, "20", false) << endl;
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
            data->on_hand -= 1;
    } else {
        std::cout << "Item not found" << std::endl;
    }
    list.printItems();
}
