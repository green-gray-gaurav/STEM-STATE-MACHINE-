//this is the map builer
//a compiler kinda code generator
#pragma
#include "state_map.hpp"
#include "tokenizer.hpp"
#include <iostream>

//here fisst we have to build state map class


std::map<std::string , State_map> buildMap(struct std::vector<TOKEN> token_bag){
    std::map< std::string  , State_map> map_table; //table of all the maps
    
    int id = 0;//map ids sequnce
    const std::string main_map = "main";
    
    std::string selected_map = main_map; //initallay the main map is selcted

    for(auto t : token_bag){

        if(t.token_name=="MAP"){    //map selction token make the extension/building of new map
            selected_map = t.raw_data;
        }
        else
        {
            // std::cout << t.loc.first << " " << t.loc.second << std::endl;
            map_table[selected_map].sequencer.push_back(t.loc); //set the sequnce of teh states
            //fill the state queue
            map_table[selected_map].STATES[t.loc.first][t.loc.second].bufferQueue.push(State::StateData(t.token_name  ,t.raw_data));
        }
    }

    

    return map_table;
}



void saveMapTable(std::map<std::string , State_map> map_table , std::string & fileName){
    std::ofstream outFile(fileName, std::ios::binary);

        if (!outFile) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }
        size_t s = map_table.size();
        outFile.write(reinterpret_cast<const char *>(&(s)) , sizeof(s));


        for(std::pair<std::string , State_map> p : map_table){
            
            // outFile.write(reinterpret_cast<const char *>(&(p.first)) , sizeof(p.first));
            ser_string(p.first , outFile);
            p.second.saveMap( outFile , fileName);
            // std::cout << "saving.." << std::endl;

        }

        outFile.close();

}

//main 


int main(int argc , char * argv[]){

   
    if(argc<2){
        std::cerr << "NO FILE SELECTED";
    }
    else{
        
        std::string filename = argv[1];
        std::string source_code = reader(filename);

        std::string folder = std::string(argv[2]);
        std::string saved_file_name;
        if(folder != ".")
            saved_file_name = folder+"\\"+filename+"_.dat";
        else 
            saved_file_name = filename+"_.dat";


      
        int flag = 0;
        std::vector<TOKEN> tb = lexical_analyser(source_code , flag );
     
        if(flag){
            std::cerr << "LEXICAL ERROR" << std::endl;
            exit(1);
        }
        else{

            //here is teh success scanning of the code
            std::map<std::string , State_map> mt = buildMap(tb);


            saveMapTable(mt , saved_file_name);


            
   

        }

    }
  


return 0;
}

