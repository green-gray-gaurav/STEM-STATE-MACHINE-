#include <iostream>
#include "serilixing_fxns.hpp"
#include "state_map.hpp"
#include "cell_memory_table.hpp"


void loadMapTable(std::map<std::string , State_map> &mt ,std::string & fileName){
        std::ifstream infile(fileName, std::ios::binary);

        if (!infile) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return ;
        }

        size_t s;
        infile.read(reinterpret_cast< char *>(&(s)) , sizeof(s));
        
        while(s--){

            std::string map_name;
            // infile.read(reinterpret_cast< char *>(&(map_name)) , sizeof(map_name));
            map_name  = deser_string(infile);
            mt[map_name].loadMap(infile , fileName);
            // std::cout << map_name << std::endl;
        }
        infile.close();

}

//this is the map table;
std::map<std::string , State_map> map_table;

int main(int argc , char * argv[]){

    //session one loading the file
        //here is the loadin code
        std::string saved_file_name = std::string(argv[1]) + "_.dat";
        //loading the map table from binaries
        loadMapTable(map_table , saved_file_name);

    //yeah map table is ready



    return 0;

}