#include "Coin.h"
#include <string>

std::string Coin::getName() {
    std::string name;
    if (denom == FIVE_CENTS) {
        name = "5 Cents";
    }
    else if (denom == TEN_CENTS) {
        name = "10 Cents";
    }
    else if (denom == TWENTY_CENTS) {
        name = "20 Cents";
    }
    else if (denom == FIFTY_CENTS) {
        name = "50 Cents";
    }
    else if (denom == ONE_DOLLAR) {
        name = "1 Dollar";
    }
    else if (denom == TWO_DOLLARS) {
        name = "2 Dollar";
    }
    else if (denom == FIVE_DOLLARS) {
        name = "5 Dollar";
    }
    else if (denom == TEN_DOLLARS) {
        name = "10 Dollar";
    }
    return name;
}

void Coin::sortCoins(Coin* purse) {
    int n = 8;
    Coin* arr = purse;
    // Bubble sort since only 8 items.
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].denom > arr[j + 1].denom) {
                Coin temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    purse = arr;
}
 // implement functions for managing coins; this may depend on your design.
