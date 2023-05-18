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
            << "\t1. Display Items\n" 
            << "\t2. Purchase Items\n" 
            << "\t3. Save and Exit\n" 
            << "Administrator-Only Menu:\n"
            << "\t4. Add Item\n"
            << "\t5. Remove Item\n"
            << "\t6. Display Coins\n"
            << "\t7. Reset Stock\n"
            << "\t8. Reset Coins\n" 
            << "\t9. Abort Program\n\n"
            << "Select your option (1-9): ";
}
bool loadItem(char **argv, LinkedList& vendingMachine);

// Save to files
void saveItem(std::string outFileName, LinkedList& vendingMachine);
void saveCoin(std::string outFileName, LinkedList& vendingMachine);

// This is the purchase item function.
void purchaseItem(LinkedList* LinkedList);
void printChange(int change, LinkedList* VendingMachine);

// This is to handle stock.
void addItem(LinkedList& list);
void resetStock(LinkedList& list);
void removeItem(LinkedList& list);

// About coins
void displayCoin(LinkedList& list);
void resetCoin(LinkedList& list);

// delete this function in the final code
// a sample of how to use Linked List
void useLinkedList();

int main(int argc, char **argv)
{
    // Initialise Variables
    LinkedList vendingMachine;
    bool allowedArgs = true;
    std::string outFileName;
    std::string coinFile;

    // Input Validation
    if (argc != 3) {
        cout << "You may have not entered the right arguments." << endl;
        allowedArgs = false;
    }

    // Adding requried documents.
    else {
        outFileName = argv[1];
        coinFile = argv[2];
        allowedArgs = loadItem(argv, vendingMachine);
    }

    string choice = "-1";
    bool exit = false;

    while (!std::cin.eof() && !exit && allowedArgs) {
        printMainMenu();
        choice = Helper::readInput();

        if (!std::cin.eof()) {
            bool isInt = true;
            int choiceLen = choice.length();

            // Type check for int
            for (int i = 0; i < choiceLen; ++i){
                if (!isdigit(choice.at(i))){
                    isInt = false;
                }
            }

            // Menu Block
            if (isInt && choice != "") {

                if (std::stoi(choice) == 1) {
                    // Display Items
                    vendingMachine.sort();
                    vendingMachine.printItems();
                    cout << endl;

                } else if (std::stoi(choice) == 2) {
                    // Purchase Items
                    purchaseItem(&vendingMachine);
                    cin.clear();

                } else if (std::stoi(choice) == 3) {
                    // Save & Exit
                    exit = true;
                    std::cout << "Save and Exit" << std::endl;
                    saveItem(outFileName, vendingMachine);
                    saveCoin(coinFile, vendingMachine);

                } else if (std::stoi(choice) == 4) {
                    // Add Item
                    addItem(vendingMachine);
                    std::cin.clear();

                } else if (std::stoi(choice) == 5) {
                    // Remove Item
                    removeItem(vendingMachine);
                    cin.clear();

                } else if (std::stoi(choice) == 6) {
                    // Displayt Coins
                    displayCoin(vendingMachine);

                } else if (std::stoi(choice) == 7) {
                    // Reset Stock
                    resetStock(vendingMachine);

                } else if (std::stoi(choice) == 8) {
                    // Reset Coins
                    resetCoin(vendingMachine);

                } else if (std::stoi(choice) == 9) {
                    // Abort Program
                    exit = true;
                } else if (!std::cin.eof()) {
                    // Invalid Input Number
                    std::cout << "Error: menu item selected is not valid." << std::endl;

                }
            } else {
                // Invalid Input
                std::cout << "Error: input was not a number. Please try again." << std::endl;
                std::cin.clear();
                // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    
    return EXIT_SUCCESS;
}

bool loadItem(char **argv, LinkedList& vendingMachine){
   // Reading the data inserted.
   bool allowedArgs = true;
   string stockDat = argv[1];
   string coinsDat = argv[2];
   // Reading files
   string stockLine;
   // Save the stock file as a linked list.
   ifstream myfile(stockDat);
   if (myfile.is_open()) {
      while (getline(myfile, stockLine)) {
            // Local variables
            string item_id, item_name, item_desc;
            double item_price;
            int item_stock;
            // Split string function by delimter.
            std::vector<std::string> stockTokens;
            string delimiter = "|";
            Helper::splitString(stockLine,stockTokens,delimiter);
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
   string coinLine;
   // Save the coin file as array since fixed array size of eight.
   ifstream coinFile(coinsDat);
   if (coinFile.is_open()) {
        int count = 0;
        while (getline(coinFile, coinLine)) {
                std::vector<std::string> coinToken;
                string delimiter = ",";
                Helper::splitString(coinLine,coinToken,delimiter);
                // Check if the coins file is a correct input.
                vendingMachine.purse[count].count = std::stoi(coinToken[1]);

                // TODO: Unable to handle non valid files.
                vendingMachine.purse[count].denom = vendingMachine.purse->string_to_denomination(coinToken[0]);
                count += 1;
        }
        coinFile.close();
        //Sort the coin array.
        vendingMachine.purse->sortCoins(vendingMachine.purse);
   }
   else {
      allowedArgs = false;
      cout << "Unable to open coin file" << endl;
   }

   return allowedArgs;
}

void saveItem(std::string outFileName, LinkedList& vendingMachine) {
   std::ofstream outfile(outFileName);
   vendingMachine.printItems(outfile);
   outfile.close();
}

void saveCoin(std::string outFileName, LinkedList& vendingMachine) {
   std::ofstream outfile(outFileName);
   vendingMachine.printCoins(outfile);
   outfile.close();
}

void purchaseItem(LinkedList* LinkedList) {

    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;
    cout << "Please enter the id of the item you wish to purchase:";

    // Get itemID
    std::string itemId;
    std::getline(std::cin, itemId);
    Helper::strip(itemId);

    if ((!cin.eof())) {
        // Check if the itemID exists
        if ((*LinkedList).get(itemId) == 0) {
            cout << "Invalid Input" << endl;
            cout << endl;
        } else {

            Stock* item = (*LinkedList).get(itemId);

            if (item->on_hand > 0) {

                // Printing the item
                cout << "You have selected \"";
                cout << item->name;
                cout << " - ";
                cout << item->description;
                cout << "\". This will cost you $ ";

                // Set local variables.
                int dollar = item->price.dollars;
                int cent = item->price.cents;
                string money = std::to_string(dollar) + "." + std::to_string(cent);

                // Continuation
                cout << money << "." << endl;
                cout << "Please hand over the money - type in the value of each note/coin in cents.\nPress enter or ctrl-d on a new line to cancel this purchase:\n";

                // Initialise more Variables
                bool paidFor = false;
                int remainingCost = (dollar * 100) + cent;
                vector<int> coinsToAdd;
                string moneyIn;

                // Loop until the item has been paidFor or the user has terminated the loop
                while (paidFor == false) {
                    dollar = remainingCost / 100;
                    cent = remainingCost % 100;

                    cout << "Remaining Cost: $" << dollar << "." << cent << ": ";
                    moneyIn = Helper::readInput();
                    Helper::strip(moneyIn);
                    
                    // This is to check for empty values
                    if ((cin.eof()) || (moneyIn == "")) {
                        // User cancels purchase
                        cout << "Pressed ctrl-D or enter" << endl;
                        paidFor = true;
                        clearerr(stdin);
                    } 

                    else if (Helper::isInt(moneyIn)) {
                        // Initialise and set variables
                        int coinDenoms[8] = {5, 10, 20, 50, 100, 200, 500, 1000};
                        int denomSize = sizeof(coinDenoms) / sizeof(coinDenoms[0]);
                        bool validDenomination = false;
    
                        // Check if the input is a valid denomination
                        for (int idx = 0; idx < denomSize; idx++) {
                            if (stoi(moneyIn) == coinDenoms[idx]) {
                                validDenomination = true;
                            }
                        } 
                        
                        if (validDenomination == false) {
                            // Invalid Denomination
                            cout << "That is not a valid denomination" << endl;
                        } else {
                            // Valid Input
                            remainingCost -= stoi(moneyIn);
    
                            // Add input to sumVector
                            coinsToAdd.push_back(stoi(moneyIn));
                            
                            // Paid for item
                            if (remainingCost <= 0) {
                                // User has paid for the item
                                paidFor = true;
                                int change = abs(remainingCost);
                                
                                cout << "Here is your " << item->name << " and your change of $" << change / 100 << "." << change % 100 << ": ";
                                printChange(change, LinkedList);
                                cout << "Please come again soon.\n";
    
                                // removing stock
                                item->on_hand -= 1;
    
                                // removing coins from purse
                                int sizeAdd = coinsToAdd.size();
                                for (int idx = 0; idx < sizeAdd; idx++) {
                                    int denomIdx = 0;
                                    for (int jdx = 0; jdx < 8; jdx++) {
                                        if (coinsToAdd[idx] == coinDenoms[jdx]) {
                                            denomIdx = jdx;
                                        }
                                    }
                                    LinkedList->purse[denomIdx].count++;
                                }
                            }
                        }
                    } else {
                        cout << "Enter a valid denomination" << endl;
                    }
                }
            }
            else {
                cout << "Item not in machine" << endl;
            }
        }
    } else {
        clearerr(stdin);
        cout << endl;
    }
}

void printChange(int change, LinkedList* VendingMachine) {
    int coinDenom[8] = {1000, 500, 200, 100, 50, 20, 10, 5};
    int i = 0;
    while (change != 0) {
        if (change / coinDenom[i] > 0) {
            if (i < 4) {
                cout << "$" << coinDenom[i] / 100 << " ";
            } else {
                cout << coinDenom[i] << "c ";
            }
            change %= coinDenom[i];
        } else {
            i++;
        }
    }
    cout << endl;
}

void addItem(LinkedList& list) {
    bool cancel = false;
    std::string maxID = Helper::maxId(list.getHead());
    std::string newID = Helper::incrementID(maxID);
    // use stepto to track the process
    // 0: name, 1: description, 2: price
    int stepto = 0;
    double price = 0;
    std::string name, description, price_s;
    std::cout << "The id of the new stock will be: " << newID << std::endl;
    
    while (stepto < 3 && !cancel) {
        if (stepto == 0) {
            // Step 0: ask the user to enter the name.
            std::cout << "Enter the item name: ";
            std::getline(std::cin, name);
            name = Helper::strip(name);
            if (name == "" || std::cin.eof()) {
                cancel = true;
            } else {
                if (name.length() > NAMELEN){
                    std::cout << "Error: line entered was too long. Please try again.\n"
                                << "Error inputting name of the product. Please try again." 
                                << std::endl;
                } else {
                    stepto++;
                }
            }
        } else if (stepto == 1) {
            // Step 1: ask the user to enter the description.
            std::cout << "Enter the item description: ";
            std::getline(std::cin, description);
            description = Helper::strip(description);
            if (description =="" || std::cin.eof()) {
                cancel = true;
            } else {
                if (description.length() > DESCLEN) {
                    std::cout << "Error: line entered was too long. Please try again.\n"
                                << "Error inputting the description of the product. Please try again." 
                                << std::endl;
                }else {
                    stepto++;
                }
            }
        } else if (stepto == 2) {
            // Step 2: ask the user to enter the price.
            std::cout << "Enter the price for the item: ";
            std::getline(std::cin, price_s);
            if (price_s == "" || std::cin.eof()) {
                cancel = true;
            } else {
                std::vector<std::string> tokens;
                price_s = Helper::strip(price_s);
                int dotNum = 0;
                for (int i = 0; i < int(price_s.length()); ++i) {
                    if (price_s[i] == '.') {
                        dotNum ++;
                    }
                }
                if (dotNum == 0) {
                    price_s.append(".");
                }
                if (price_s[0] == '.') {
                    price_s.insert(0, "0");
                } else if (price_s[price_s.length()-1] == '.') {
                    price_s.append("0");
                }
                Helper::splitString(price_s, tokens, ".");
                if (tokens.size() == 2) {
                    if (tokens[1].length() == 1) {
                        tokens[1].append("0");
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
                        stepto ++ ;
                    }
                } else {
                    std::cout << "Error: the price is not valid." << std::endl;
                }
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
    bool quit = false;
    bool cancel = false;
    std::string item;
    while (!quit && !cancel) {
        cout << "Enter the item id of the item to remove from the menu: ";
        std::getline(std::cin, item);
        if (item == "" || std::cin.eof()) {
            cancel = true;
        } else {
            quit = true;
        }
    }
    quit = false;
    // Exit if bad input
    if (!quit && !cancel) {
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
    if (cancel) {
        std::cout << "Cancelling \"Remove Item\" at user's request.\n"
                << "The task Remove Item failed to run successfully."
                << std::endl;
        clearerr(stdin);
    }
    return;
}

void resetStock(LinkedList& list){
    Node* upto = list.getHead();
    while (upto != nullptr) {
        upto->data->on_hand = DEFAULT_STOCK_LEVEL;
        upto = upto->next;
    }
    std::cout << "All stock has been reset to the default level of 20" << std::endl;
}

// precondition: the coins arrive presorted.
void displayCoin(LinkedList& list) {
    cout << "Coins Summary" << endl;
    cout << Helper::printBorder(13);
    cout << "Denomination    |    Count" << endl;
    // Denom side == 16, count side == 10, Total = 27.
    cout << Helper::printBorder(27);
    int purseLen = sizeof(list.purse);
    for (int i=0; i < purseLen; i++) {
        cout << Helper::writeOnSize(16, list.purse[i].getName(), true);
        cout << "|";
        cout << Helper::writeOnSize(10, std::to_string(list.purse[i].count), false) << endl;
    }
    // Spacing reasons
    cout << endl;
}

void resetCoin(LinkedList& vendingMachine) {
    for (int i = 0; i < 8; i++) {
        vendingMachine.purse[i].count = DEFAULT_COIN_COUNT;
    }
    cout << "All coins have been reset to the default level of: ";
    cout << DEFAULT_COIN_COUNT << endl;
}
