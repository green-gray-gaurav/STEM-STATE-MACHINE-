//this is the tokenizer file 
//lexical analyser
#include "tokenizer.hpp"
#include <iostream>

bool isUppercase(std::string& str) {
    return std::all_of(str.begin(), str.end(), [](char c) {
        return std::isupper(c);
    });
}

bool containsOnlyAlphabets(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c)) {
            return false; // Found a non-alphabetic character
        }
    }
    return true; // All characters are alphabetic
}
bool containsOnlyAlphanumeric(const std::string& str) {
    for (char c : str) {
        if (!std::isalnum(c)) {
            return false; // Found a non-alphanumeric character
        }
    }
    return true; // All characters are alphanumeric
}

bool containsOnlyLowercase(const std::string& str) {
    for (char c : str) {
        if (!std::islower(c)) {
            return false; // Found a non-lowercase character
        }
    }
    return true; // All characters are lowercase
}


std::vector<TOKEN> lexical_analyser(const std::string sourceCode , int & flag){
    std::vector<TOKEN> TOKEN_BAG;

    std::string token = "";
    for(int i = 0 ; i < sourceCode.length()+1 ; i++){ //givin a bias to len to get all tokens
        
        if(token.length()>0 && (sourceCode[i]==' ' || sourceCode[i] == '\n' || i==sourceCode.length())){//if white space encountred
            
            if(token[0]=='$' && containsOnlyAlphanumeric(token.substr(1 , token.length()-1))  ){ // its a cell selection state

                    TOKEN_BAG.push_back({"CELL" , (token.substr(1 , token.length()-1))  , std::make_pair(0,1) });
            }
            else if(token.length() ==1  && token[0] <= 'Z' && token[0] >= 'A'){ // its a phase selction state
                    TOKEN_BAG.push_back({"PHASE" , token , std::make_pair(0,2)});
            }
            else if (token[0]=='[' && token[token.length()-1] == ']'){ // its a feeding state // use state 
                    TOKEN_BAG.push_back({"FEED" , token.substr(1,token.length()-2) , std::make_pair(0,3)});

            }
            else if(token == "HOOK"){ // branching / selection /loop // control
                    TOKEN_BAG.push_back({"HOOK" , token , std::make_pair(0,4)});

            }
            else if(token == "CHOOK"){
                     TOKEN_BAG.push_back({"CHOOK" , token , std::make_pair(1,0)});

            }
            else if(token.length()>1 && containsOnlyAlphabets(token) &&isUppercase(token)){ // here is the dependent key seletion state
                     TOKEN_BAG.push_back({"DKEY" , token , std::make_pair(1,1)});

            }
            else if(token.length()>1 && containsOnlyAlphabets(token) && containsOnlyLowercase(token)){ // this is the indeendent key selection/use state
                    TOKEN_BAG.push_back({"IKEY" , token , std::make_pair(1,2)});

            } 
            else if(token[0] == '@' && containsOnlyAlphanumeric(token.substr(1 , token.length()-1)) ){ // this is the map selction state
                     TOKEN_BAG.push_back({"MAP" , token.substr(1 , token.length()-1) , std::make_pair(1,3)});

            }
            else if(token[0]=='{' && token[token.length()-1] == '}'){
                    TOKEN_BAG.push_back({"INCLUDE" , token.substr(1 , token.length()-2) , std::make_pair(1,4)});
 
            }
            else{
                flag = 1; // error // in valied token
            }
            
            token="" ;//get the next token
        }
        else{   //else // otherwise
            if(sourceCode[i]!=' ' && sourceCode[i] !='\n')
                token += sourceCode[i];
            }
    }
    return TOKEN_BAG;
}

std::string reader(std::string filename){
    std::ifstream file(filename);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

// int main(){

//     std::string sc = reader("source_code.txt");
//     int flag = 0;
//     std::vector<TOKEN> tb = lexical_analyser(sc , flag);

//     std::cout << flag ;
    
//     for(auto t : tb){
//         std::cout << t.token_name << " " << t.raw_data << std::endl;
//     }


//     return 0;
// }

