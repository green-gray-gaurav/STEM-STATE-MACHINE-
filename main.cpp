#include <iostream>
#include "state_map.hpp"
#include <stack>


void loadMapTable(std::map<std::string , State_map> &mt ,std::string & fileName){
        std::ifstream infile(fileName, std::ios::binary);

        if (!infile) {
            std::cerr << "Error opening file for reading" << std::endl;
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

std::map<std::string , std::map<std::string , State_map>> LIBS;

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
            // int p = map.find(".");
            // std::string map_name_ = map.substr(0, p);
            // std::string cell_name_ = map_cell_name.substr(p+1 , map_cell_name.length()-p-1);
            
            // std::cout << "empty: " <<map.STATES[map.sequencer[0].first][map.sequencer[0].second].bufferQueue.front().raw_data << std::endl;
            map.map_name = statusCodeObj[1];
            MAPSTACK.push(map);

        }
        else if (statusCode == "REQ_MAP"){
                    std::string filename_map = statusCodeObj[1];
                    size_t p = filename_map.find(".");
                    if(p != std::string::npos) //a map from the  external libs
                    {
                        std::string filename = filename_map.substr(0, p);
                        std::string map = filename_map.substr(p+1 , filename_map.length()-p-1);
                        State_map mp = LIBS[filename][map];
                        mp.map_name = map;
                        mp.domain = filename;
                        MAPSTACK.push(mp);


                    }
                    else{ // a mpa from the source file
                        std::string domain_name = statusCodeObj[2];

                        if(domain_name == ""){ // is current domain is root
                          
                            State_map map = map_table[statusCodeObj[1]];
                            map.map_name = statusCodeObj[1];
                            MAPSTACK.push(map);  

                        }
                        else{
                            // toher than root domaiin
                            State_map mp = LIBS[domain_name][statusCodeObj[1]];
                            mp.map_name = statusCodeObj[1];
                            mp.domain = domain_name;
                            MAPSTACK.push(mp);
                        }
                    }

                    
        }
        else if(statusCode == "REQ_MAP_ADD"){
            //here is the request to link a library map /custom map with the map table
            //dynaminc link
            std::map<std::string , State_map> add_table;

            std::string filename = statusCodeObj[1] + "_.dat";
            loadMapTable(add_table , filename);

            for(auto map : add_table){
                LIBS[statusCodeObj[1]][map.first] = map.second;
            }




        }
    }




    return 0;

}