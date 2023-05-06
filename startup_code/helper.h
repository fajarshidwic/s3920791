#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string.h>
#include <random>
#include "LinkedList.h"

class Helper
{
private:
    Helper();

public:

    /**
     * @brief Check whether the given string is an integer or a float 
     * 
     * @param s The given string
     * @return true if the string is an integer or a float 
     * @return false if the string is neither an integer nor a float 
     */
    static bool isNumber(std::string s);

    /**
     * @brief Split the given string given a delimeter. For instance, given the string "1,2,3" and the delimeter ",", 
     *        This string will be splited into "1","2","3", and they will be put into the vector.  
     * 
     * @param s The given string
     * @param tokens The vector containing the results
     * @param delimeter the string based on which splitting is performed
     */
    static void splitString(std::string s, std::vector<std::string>& tokens, std::string delimeter);

    /**
     * @brief Read the user input (a line) from keyboard
     * 
     * @return the user input.
     */
    static std::string readInput();

    static void printInvalidInput();

    /**
     * @brief Strips white space before and after string
     *
     * @param s The given string
     * 
     * @return s
     */
    static std::string strip(std::string& s);

    /**
     * @brief This function is to get the max id in the linked list to help generate a new id when select Add Item
     * 
     * @param head the head of the linked list
     * @return string 
     */
    static std::string maxId (Node* head);

    /**
     * @brief id increment
     * 
     * @param id id
     * @return string 
     */
    static std::string incrementID(std::string id);

    /**
     * @brief check if input content is double-type
     * 
     * @param input detected content
     * @return true 
     * @return false 
     */
    static bool isDouble(std::string& input);

    /**
     * @brief check if input content is int-type
     *
     * @param input detected content
     * @return true
     * @return false
     */
    static bool isInt(const std::string& input);
};
#endif