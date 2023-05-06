#include "helper.h"

using std::string;
using std::vector;

Helper::Helper(){}

void Helper::printInvalidInput()
{
    std::cout << "Invalid input.\n" << std::endl;
}

bool Helper::isNumber(string s)
{
    string::const_iterator it = s.begin();
    char dot = '.';
    int nb_dots = 0;
    while (it != s.end()) 
    {
        if (*it == dot)
        {
            nb_dots++;
            if (nb_dots>1)
            {
                break;
            }
        }   
        else if (!isdigit(*it))
        {
            break;
        } 

        ++it;
    }
    return !s.empty() && s[0] != dot && it == s.end();
}

void Helper::splitString(string s, vector<string>& tokens, string delimeter)
{
    tokens.clear();
    char* _s = new char[s.length()+1];
    strcpy(_s, s.c_str());

    char * pch;
    pch = strtok (_s, delimeter.c_str());
    while (pch != NULL)
    {
        tokens.push_back(pch);
        pch = strtok (NULL, delimeter.c_str());
    }
    delete[] _s;
}

string Helper::readInput()
{
    string input;
    std::getline(std::cin, input);
    std::cout << std::endl;

    return input;
}

string Helper::strip(std::string& s) {
    int i = 0;
    while (std::isspace(s[i])) {
        // Remove the character at index i
        s.erase(i, 1);
    }
    // Count for new index for end point here.
    int lastIndex = s.length() - 1;
    while (std::isspace(s[lastIndex])) {
        // Remove the character at index i
        s.erase(lastIndex, 1);
        // Count for new index for end point here.
        lastIndex = s.length() - 1;
    }
    return s;
}

std::string Helper::maxId(Node* head) {
    if (head == nullptr) {
        return "I0000";
    } else {
        std::string temp_id = head->data->id;
        if (maxId(head->next) > temp_id){
            temp_id = maxId(head->next);
        }
        return temp_id;
    }
}

std::string Helper::incrementID(std::string id) {
    char prefix;
    int number;
    std::stringstream ss(id);

    ss >> prefix >> number;
    number++;

    std::stringstream newId;
    newId << prefix << std::setw(4) << std::setfill('0') << number;

    return newId.str();
}

bool Helper::isDouble(std::string& input) {
    bool retVal = true;
    int dotNum = 0;
    int inputLen = input.length();
    for (int i = 0; i < inputLen; ++i){
        if (!isdigit(input[i]) && (char)input[i] != '.'){
            retVal = false;
        }
        if ((char)input[i] == '.'){
            dotNum += 1;
        }
    }
    if (dotNum > 1){
        retVal = false;
    }
    return retVal;
}

bool Helper::isInt(const std::string& input) {
    bool retVal = true;
    int inputLen = input.length();
    for (int i = 0; i < inputLen; ++i){
        if (!isdigit(input[i])){
            retVal = false;
        }
    }
    return retVal;
}
