//this is the tokenizer file 
//lexical analyser
#include<vector>
#include <map>
#include <algorithm>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
bool isUppercase(std::string& str);

bool containsOnlyAlphabets(const std::string& str) ;
bool containsOnlyAlphanumeric(const std::string& str) ;
bool containsOnlyLowercase(const std::string& str);

struct TOKEN
{
    std::string token_name;
    std::string raw_data;
    std::pair<int , int > loc;
};
std::vector<TOKEN> lexical_analyser(const std::string sourceCode , int & flag);
std::string reader(std::string filename);