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

/* Colour Codes 

COLORS:
\x1b[30m     BLACK 
\x1b[31m     RED 
\x1b[32m     GREEN 
\x1b[33m     YELLOW 
\x1b[34m     BLUE 
\x1b[35m     MAGENTA 
\x1b[36m     CYAN 
\x1b[37m     WHITE

BACKGROUND COLORS:
\x1b[40m     BLACK 
\x1b[41m     RED 
\x1b[42m     GREEN 
\x1b[43m     YELLOW 
\x1b[44m     BLUE 
\x1b[45m     MAGENTA 
\x1b[46m     CYAN 
\x1b[47m     WHITE
 
RESET CODE:
\x1b[0m

USAGE:

cout << "[color]TEXT[resetcode] << endl;
cout << "\x1b[35mTEXT\x1b[0m" << endl;

SOURCE:
https://notdefined.tech/blog/how-to-add-color-to-your-terminal-output/

*/

void printMainMenu() {
    std::cout << "\n\x1b]1337;SetMark\x07Main Menu:\n"
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

void saveItem(std::string outFileName, LinkedList& vendingMachine);
void saveCoin(std::string outFileName, LinkedList& vendingMachine);

// This is the purchase item function.
void purchaseItem(LinkedList* LinkedList);
bool printChange(int change, LinkedList* VendingMachine);

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

    if (argv[1] == NULL || string(argv[1]) != "stock.dat") {
        cout << "\x1b[31mThe first argument must be stock.dat\x1b[0m" << endl;
        allowedArgs = false;
    }

    if (argv[2] == NULL || string(argv[2]) != "coins.dat") {
        cout << "\x1b[31mThe second argument must be coins.dat\x1b[0m" << endl;
        allowedArgs = false;
    }

    // Adding requried documents.
    if (allowedArgs) {
        outFileName = argv[1];
        coinFile = argv[2];
        cout << "name 1: " << outFileName << ", name 2: " << coinFile << endl;
        allowedArgs = loadItem(argv, vendingMachine);
    }

    string choice = "-1";
    bool exit = false;

    while (!std::cin.eof() && !exit && allowedArgs) {
        printMainMenu();
        choice = Helper::readInput();

        if (!std::cin.eof()) {
            bool proceed = true;
            int choiceLen = choice.length();

            // Type check for int
            for (int i = 0; i < choiceLen; ++i){
                if (!isdigit(choice.at(i))){
                    proceed = false;
                }
            }

            if (choiceLen > 1) {
                proceed = false;
            }

            // Menu Block
            if (proceed && choice != "") {
                cout << endl;
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

    cout << "\nPurchase Item" << endl;
    cout << "-------------" << endl;

    // Get itemID
    std::string itemId;
    bool quit = false;
    bool valid = true;
    while (!quit) {
        cout << "\n\x1b[0mPlease enter the id of the item you wish to purchase: \x1b[33m";
        std::getline(std::cin, itemId);
        Helper::strip(itemId);

        if ((cin.eof()) || (itemId == "")) {
            cout << "\x1b[0m" << "\x1b[31mPressed ctrl-D or enter\x1b[0m" << endl;
            quit = true;
            valid = false;
        } else if (itemId.length() != IDLEN) {
            cout << "\x1b[0m" << "\x1b[31mInvalid ItemID Length\x1b[0m" << endl;
        } else if ((quit == false) && ((*LinkedList).get(itemId) == 0)) {
            cout << "\x1b[0m" << "\x1b[31mItem ID does not exist\x1b[0m" << endl;
        } else {
            cout << "triggered" << endl;
            quit = true;
        }
    }

    if (valid) {
        // Check if the itemID exists
        Stock* item = (*LinkedList).get(itemId);
        if (item->on_hand > 0) {
            // Printing the item
            cout << "\x1b[0m";
            cout << "You have selected \x1b[33m\"";
            cout << item->name;
            cout << " - ";
            cout << item->description;
            cout << "\"\x1b[0m. This will cost you \x1b[32m$";
            // Set local variables.
            int dollar = item->price.dollars;
            int cent = item->price.cents;
            string money = std::to_string(dollar) + "." + std::to_string(cent);
            // Continuation
            cout << money << "\x1b[0m.\n" << endl;
            cout << "Please hand over the money - type in the value of each note/coin in cents.\n"
                 << "Press enter or ctrl-d on a new line to cancel this purchase:\n\n";
            // Initialise more Variables
            bool paidFor = false;
            int remainingCost = (dollar * 100) + cent;
            vector<int> coinsToAdd;
            string moneyIn;
            // Loop until the item has been paidFor or the user has terminated the loop
            while (paidFor == false) {
                dollar = remainingCost / 100;
                cent = remainingCost % 100;
                cout << "Remaining Cost: \x1b[32m$" << dollar << "." << cent << "\x1b[0m: ";
                moneyIn = Helper::readInput();
                Helper::strip(moneyIn);
                
                // This is to check for empty values
                if ((cin.eof()) || (moneyIn == "")) {
                    // User cancels purchase
                    cout << "\x1b[31mPressed ctrl-D or enter\x1b[0m\n" << endl;
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
                        cout << "\x1b[31mEnter a Valid Denomination\x1b[0m\n" << endl;
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
                            
                            cout << "\nHere is your " << item->name << " and your change of \x1b[32m$" << change / 100 << "." << change % 100 << "\x1b[0m: ";
                            if (printChange(change, LinkedList)) {
                                // if failed to give change
                                cout << "\x1b[31mSorry, we don't have enough coins to give you change" << endl;
                                cout << "Try again with more exact coins\x1b[0m" << endl;
                            } else {
                                // if successfully gave change
                                cout << "Please come again soon!\n\n";

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
                    }
                } else {
                    cout << "\x1b[31mEnter a Valid Denomination\x1b[0m\n" << endl;
                }
            }
        } else {
            cout << "\x1b[31mItem not in machine\x1b[0m" << endl;
        }
    } else {
        clearerr(stdin);
        cout << endl;
    }
}

bool printChange(int change, LinkedList* VendingMachine) {
    // Declare variables
    vector<int> coinDenom = {1000, 500, 200, 100, 50, 20, 10, 5};
    vector<int> addBack;
    bool refund = false;

    // Loop until change given
    int i = 0;
    while (change != 0) {
        bool cancel = false;
        if (change / coinDenom[i] <= 0) {
            //cout << "less than 0" << endl;
            cancel = true;
        }

        // no coins for that denomination
        if (VendingMachine->purse[i].count == 0) {
            //cout << "no coins" << endl;
            cancel = true;
        }

        // in case while loop becomes stuck
        if (i >= 7 && change > 0) {
            //cout << "stuck" << endl;
            change = 0; // stops the loop
            cancel = true;
            refund = true;
        }

        if (cancel) {
            i++;
        } else {
            if (i < 4) {
                cout << "$" << coinDenom[i] / 100 << " ";
                addBack.push_back(coinDenom[i]);
            } else {
                cout << coinDenom[i] << "c ";
                addBack.push_back(coinDenom[i]);
            }
            change %= coinDenom[i];
            VendingMachine->purse[7-i].count--;
        }

        if (refund) {
            for (int idx = 0; idx < int(addBack.size()); idx++) {
                int denomIdx = 0;
                for (int jdx = 0; jdx < 8; jdx++) {
                    if (addBack[idx] == coinDenom[7-jdx]) {
                        denomIdx = jdx;
                    }
                }
                VendingMachine->purse[denomIdx].count++;
            }
        }

    }
    cout << endl;
    return refund;
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
    std::cout << "The id of the new stock will be: \x1b[33m" << newID << "\x1b[0m" << std::endl;
    
    while (stepto < 3 && !cancel) {
        if (stepto == 0) {
            // Step 0: ask the user to enter the name.
            std::cout << "Enter the item name: \x1b[33m";
            std::getline(std::cin, name);
            name = Helper::strip(name);
            if (name == "" || std::cin.eof()) {
                cancel = true;
            } else {
                if (name.length() > NAMELEN){
                    std::cout << "\x1b[31mError: line entered was too long. Please try again.\n"
                                << "Error inputting name of the product. Please try again. \x1b[0m"
                                << std::endl;
                } else {
                    stepto++;
                }
            }
        } else if (stepto == 1) {
            // Step 1: ask the user to enter the description.
            std::cout << "\x1b[0mEnter the item description: ";
            std::getline(std::cin, description);
            description = Helper::strip(description);
            if (description =="" || std::cin.eof()) {
                cancel = true;
            } else {
                if (description.length() > DESCLEN) {
                    std::cout << "\x1b[31mError: line entered was too long. Please try again.\n"
                                << "Error inputting the description of the product. Please try again.\x1b[0m" 
                                << std::endl;
                }else {
                    stepto++;
                }
            }
        } else if (stepto == 2) {
            // Step 2: ask the user to enter the price.
            std::cout << "Enter the price for the item: \x1b[32m";
            std::getline(std::cin, price_s);
            std::cout << "\x1b[0m";
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
                        std::cout << "\x1b[31mError: the price is not valid.\x1b[0m" << std::endl;
                    } else if (tokens[0].length() >= 3 || std::stoi(tokens[0]) < 0) {
                        std::cout << "\x1b[31mError: the dollars are out of range.\x1b[0m" << std::endl;
                    } else if (tokens[1].length() >= 3 || std::stoi(tokens[1]) < 0) {
                        std::cout << "\x1b[31mError: the cents are out of range.\x1b[0m" << std::endl;
                    } else if (std::stoi(tokens[1])%5) {
                        std::cout << "\x1b[31mError: the cents need to be a multiple of 5.\x1b[0m" << std::endl;
                    } else {
                        price = std::stod(price_s);
                        stepto ++ ;
                    }
                } else {
                    std::cout << "\x1b[31mError: the price is not valid.\x1b[0m" << std::endl;
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
        cout << "Enter the item \x1b[33mID\x1b[0m of the item to \x1b[31mremove\x1b[0m from the menu: \x1b[33m";
        std::getline(std::cin, item);
        if (item == "" || std::cin.eof()) {
            cancel = true;
        } else if (item.length() > IDLEN) {
            std::cout << "\x1b[31mError: line entered was too long. Please try again.\n"
                    << "Error inputting ID of the product. Please try again.\x1b[0m" 
                    << std::endl;
        } else {
            quit = true;
        }
    }
    quit = false;
    // Exit if bad input
    if (!quit && !cancel) {
        Stock* itemInfo = list.get(item);
        if (itemInfo != nullptr) {
            cout << "\"\x1b[33m";
            cout << itemInfo->id;
            cout << "\x1b[0m - \x1b[33m";
            cout << itemInfo->name;
            cout << "\x1b[0m - ";
            cout << itemInfo->description;
            cout << "\" has been \x1b[31mremoved\x1b[0m from the system." << endl;
            list.remove(item);
        } else {
            cout << "\x1b[31mThat item does not exist in system.\x1b[0m" << endl;
        }
    }
    if (cancel) {
        std::cout << "Cancelling \"Remove Item\" at user's request.\n"
                << "\x1b[31mThe task Remove Item failed to run successfully.\x1b[0m"
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

// Condition: the coins arrive presorted.
void displayCoin(LinkedList& list) {
    cout << "Coins Summary" << endl;
    cout << Helper::printBorder(13);
    cout << "\x1b[32mDenomination\x1b[0m    |    Count" << endl;
    // Denom side == 16, count side == 10, Total = 27.
    cout << Helper::printBorder(27);
    int purseLen = sizeof(list.purse);
    for (int i=0; i < purseLen; i++) {
        cout << "\x1b[32m" << Helper::writeOnSize(16, list.purse[i].getName(), true) << "\x1b[0m";
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
