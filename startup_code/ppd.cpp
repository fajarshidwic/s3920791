#include <iostream>
#include "LinkedList.h"

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/

void printMainMenu() {
    std::cout << "Main Menu:" << std::endl;
    std::cout << "\t1. Display Items" << std::endl;
    std::cout << "\t2. Purchase Items" << std::endl;
    std::cout << "\t3. Save and Exit" << std::endl;
    std::cout << "Administrator-Only Menu:" << std::endl;
    std::cout << "\t4. Add Item" << std::endl;
    std::cout << "\t5. Remove Item" << std::endl;
    std::cout << "\t6. Display Coins" << std::endl;
    std::cout << "\t7. Reset Stock" << std::endl;
    std::cout << "\t8. Reset Coins" << std::endl;
    std::cout << "\t9. Abort Program" << std::endl;
    std::cout << "Select your option (1-9):";
}


int main(int argc, char **argv)
{
    /* validate command line arguments */
    // TODO
    int choise = 0;

    while (!(choise == 3 || choise == 9) && !std::cin.eof()) {

        printMainMenu();
        std::cin >> choise;
        std::cout << std::endl;

        if (choise == 1) {
            std::cout << "Display Items" << std::endl;
        } else if (choise == 2) {
            std::cout << "Purchase Items" << std::endl;
        } else if (choise == 3) {
            std::cout << "Save and Exit" << std::endl;
        } else if (choise == 4) {
            std::cout << "Add Item" << std::endl;
        } else if (choise == 5) {
            std::cout << "Remove Item" << std::endl;
        } else if (choise == 6) {
            std::cout << "Display Coins" << std::endl;
        } else if (choise == 7) {
            std::cout << "Reset Stock" << std::endl;
        } else if (choise == 8) {
            std::cout << "Reset Coins" << std::endl;
        } else if (choise == 9) {
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
    std::cout << "Just a test, nothing implemented yet!" << std::endl;
    
    return EXIT_SUCCESS;
}
