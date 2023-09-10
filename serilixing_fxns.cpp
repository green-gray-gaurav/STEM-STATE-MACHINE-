#include  "serilixing_fxns.hpp"

std::string deser_string(std::ifstream& inputFile) {
    
    size_t readSize;
    inputFile.read(reinterpret_cast<char*>(&readSize), sizeof(readSize));

    // Read the string from the binary file
    char* buffer = new char[readSize + 1];
    buffer[readSize] = '\0'; // Null-terminate the C-style string
    inputFile.read(buffer, readSize);

    // Convert the C-style string to a C++ string
    std::string readString(buffer);
    delete[] buffer;
    return readString;
    
}

void ser_string( std::string myString, std::ofstream& outputFile){
    size_t stringSize = myString.size();
    outputFile.write(reinterpret_cast<const char*>(&stringSize), sizeof(stringSize));
    outputFile.write(myString.c_str(), stringSize);
}

