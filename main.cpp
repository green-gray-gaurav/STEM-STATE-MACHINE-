#include <iostream>
#include "state_map.hpp"
#include <stack>


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



void linking( std::map<std::string , State_map> &mp1 ,  std::string name_space_prefix , std::map<std::string , State_map> &mp2){
    //here we are mergin the mp1 and map2
    for(auto mp : mp2){ //goinf over the map table // using the dot for prefix connection
        if(mp1.find(name_space_prefix + "." + mp.first) == mp1.end())
            mp1[name_space_prefix + "." + mp.first] = mp.second; //id that map dont already exists
        else{
            ///error since the name confilt happeded
            std::cerr << "LINKING ERROR:: MAP NAME CONFLICT" << std::endl;
            std::cerr << "IN LIB FILE: " << name_space_prefix << " has map of name: " << mp.first << std::endl;
            break;
        }
    }   
}

//this is the map table;
std::map<std::string , State_map> map_table;
//here we have out map stack
std::stack<State_map> MAPSTACK;

//here is cell table 
Cell_table CELLTABLE;

//here is hyper queue
hyperSq HYPERSTATEQ;

//cell logger

RCS RecentCellStack;


int main(int argc , char * argv[]){
        std::cerr << "static --- linked SUCCESFULLY_________________________________" << std:: endl;
        
    //session one loading the file
        //here is the loadin code
        std::string saved_file_name = std::string(argv[1]) + "_.dat";
        //loading the map table from binaries
        loadMapTable(map_table , saved_file_name);

    //yeah map table is ready nope!!
    //linking is must thus cant go with out it
    // (1,4) ----> is the state cell for inclusion (libhooks)
    //lets test out with the before mergining

    //setting the map stack
    //here we are stacking up the primary map (main map)
    std::cerr << "loaded SUCCESFULLY_________________________________" << std:: endl;
    State_map main_map = map_table["main"];
    main_map.map_name = "main";
    MAPSTACK.push(main_map);

    // std::cout << main_map.STATES[0][3].bufferQueue.front().raw_data << std::endl;


    //now its run time

    while(!MAPSTACK.empty()){ // this is the main loop


        State_map * current_map_snapshot = &(MAPSTACK.top());


        // std::cout << current_map_snapshot->currentSquenceState << std::endl;
        
        //here show this snapshot the current instance of the cell table and huperQ
        current_map_snapshot->loadRefernces(&CELLTABLE , &HYPERSTATEQ , &RecentCellStack);

        //run this snapshot
        std::vector<std::string> statusCodeObj = current_map_snapshot->runMap();
        //handel the result object
       
        //here is the extrenal handling
        //other stauts codes
        // std::cout << MAPSTACK.empty() << " "   << statusCodeObj[0] << std::endl;
        //here is the removal if m ap is not pending has completed the execturiotn
        std::string statusCode = statusCodeObj[0];

        if(statusCode == "D")//donw with map execution
            {   
                //delete the associated cells 
                //berttr method is using threads---->
                //but for now
                CELLTABLE.removeByCellNameAndMap("" , statusCodeObj[1]); 
                MAPSTACK.pop();
            }

        else if(statusCode == "E"){//error status
            //add extra info 
            std::cout << "FAILED" << std::endl;
            return 0;
        }
        else if (statusCode == "REQ"){ //normal hook request

            State_map map = map_table[statusCodeObj[1]];
            // std::cout <<statusCodeObj[1]<< std::endl;
            
            // std::cout << "empty: " <<map.STATES[map.sequencer[0].first][map.sequencer[0].second].bufferQueue.front().raw_data << std::endl;
            map.map_name = statusCodeObj[1];
            MAPSTACK.push(map);

        }
        else if(statusCode == "REQ_MAP_ADD"){
            //here is the request to link a library map /custom map with the map table
            //dynaminc link


        }
    }




    return 0;

}