#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <fstream>
#include "serilixing_fxns.hpp"
#include "cell_memory_table.hpp"
#include "hyperQ.hpp"


class State{
    public:
    class StateData{
        public:
        // std::string data_type;
        std::string state_type;
        std::string raw_data;
        StateData(){

        }

        StateData(std::string state_type , std::string raw_data ){
            this->state_type = state_type;
            this->raw_data = raw_data;
        }
        
    };
    // std::string label;
    std::queue<State::StateData> bufferQueue;

};


class State_map{

    public:
        std::string map_name; //this is the map name
        
        //mkaing a 5 x 5 map



        State STATES[5][5];
        std::vector<std::pair<int , int>> sequencer; //thit is an imort tant part
        int currentSquenceState = 0; // starting state null

        //some pointers
        Cell_table * cellTable =NULL;
        hyperSq * hyperStateQueue = NULL;

        //internal states // selction cell
         std::pair<int , std::string> SELECTED_CELL; //cell
        enum{F,I,S} CELL_PAHSE = I;
        std::string D_KEY;

        //some other states ehecihc are e\ye tto decode

        

    std::string runMap();

    bool isEvaluated();

    void saveMap( std::ofstream& outFile, std::string& filename);

    void loadMap(std:: ifstream& inFile , std::string& filename);


    //this is import part where you load the ref from the 
    void loadRefernces(Cell_table * cellTable , hyperSq * hyperStateQueue){
        this->cellTable = cellTable;
        this->hyperStateQueue = hyperStateQueue;
    }

};