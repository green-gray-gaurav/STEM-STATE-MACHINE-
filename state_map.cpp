#include "state_map.hpp"
#include <sstream>



std::string State_map::runMap()
{
    //this is te real deal man
    while(this->sequencer.size() > this->currentSquenceState){

        //find and evalur the current state
        std::pair<int, int> stateLoc = (this->sequencer[this->currentSquenceState]);
        State::StateData stateData =  this->STATES[stateLoc.first][stateLoc.second].bufferQueue.front();
        this->STATES[stateLoc.first][stateLoc.second].bufferQueue.pop(); // removinf and deqinf the state
        
        //debgginh
        // std::cout << stateData.raw_data << " " << stateData.state_type << std::endl;

        if(stateData.state_type == "CELL"){
            //this is the state secltion cell of the map
            //here you knida chose the current vairable of operation
            int status = this->cellTable->getIdByCellName(stateData.raw_data);
            if(status==-1){
                  int id_ = cellTable->add(stateData.raw_data , this->map_name);
                  SELECTED_CELL.first = id_;
                  SELECTED_CELL.second = stateData.raw_data;
                     
            }
            else{
                SELECTED_CELL.first = status;
                SELECTED_CELL.second = stateData.raw_data;  
            }
            
        }
        else if(stateData.state_type == "PHASE"){ // here is th another selction cell for the phase state
        
            if(stateData.raw_data == "F")  CELL_PAHSE = F;
            else if(stateData.raw_data == "S")  CELL_PAHSE = S;
            else if(stateData.raw_data == "I")  CELL_PAHSE = I;
            else {
                //rintime error error invalid phase;
                return "E";
            }
        }
        else if(stateData.state_type == "FEED"){ //sate user //
            //this ont is feed brackets
            if(stateData.raw_data[0]=='$'){//cell value // inderting feeding
                std::string cellName = stateData.raw_data.substr(1,stateData.raw_data.length()-1);
                Cell_table::entry e = cellTable->searchByCellName(cellName);

                if(CELL_PAHSE==F) //if float phase selcted
                    {
                        cellTable->table[SELECTED_CELL.first].VALUE.decimal =  e.VALUE.decimal;
                    }
                else if(CELL_PAHSE == I)
                    {
                         cellTable->table[SELECTED_CELL.first].VALUE.integer =  e.VALUE.integer;
                    }
                else if(CELL_PAHSE = S)
                    {
                         cellTable->table[SELECTED_CELL.first].VALUE.str =  e.VALUE.str;
                    }

            }
            else{//constant
                  
                std::string str_data = stateData.raw_data;
                std::stringstream ss;

                // std::cout << ": " << str_data << std::endl;
                    
                if(CELL_PAHSE==F) //if float phase selcted
                    {
                        ss << str_data;
                        double d_value; ss >> d_value;
                        cellTable->table[SELECTED_CELL.first].VALUE.decimal =  d_value;
                    }
                else if(CELL_PAHSE == I)
                    {
                        ss << str_data;
                        int intValue; ss >> intValue;
                        cellTable->table[SELECTED_CELL.first].VALUE.integer =  intValue;
                    }
                else if(CELL_PAHSE = S)
                    {
                        
                         cellTable->table[SELECTED_CELL.first].VALUE.str =  str_data;
                    }                    
        
            }
        }
        else if(stateData.state_type=="DKEY"){

        }
        else if(stateData.state_type =="IKEY"){
            //independent key
            if(stateData.raw_data == "display"){

                if(CELL_PAHSE==F)
                    std::cout << cellTable->table[SELECTED_CELL.first].VALUE.decimal;
                
                if(CELL_PAHSE==I)
                    std::cout << cellTable->table[SELECTED_CELL.first].VALUE.integer;
                
                if(CELL_PAHSE==S)
                    std::cout << cellTable->table[SELECTED_CELL.first].VALUE.str;
            }


            else if(stateData.raw_data == "read"){
                 if(CELL_PAHSE==F)
                    std::cin >>cellTable->table[SELECTED_CELL.first].VALUE.decimal;
                
                if(CELL_PAHSE==I)
                    std::cin >> cellTable->table[SELECTED_CELL.first].VALUE.integer;
                
                if(CELL_PAHSE==S)
                    std::cin >> cellTable->table[SELECTED_CELL.first].VALUE.str;

            }


        }
        else if(stateData.state_type =="INCLUDE"){

        }
        else if(stateData.state_type == "CHOOK"){

        }
        else if(stateData.state_type == "HOOK"){

        }


        //going to next state in sequence
        this->currentSquenceState++;
    }

    //end of the loop means
    return "D";
}

bool State_map::isEvaluated()
{
    if(this->currentSquenceState == this->sequencer.size()){
        return true;
    }
    else{
        return false;
    }
}

void State_map::saveMap(std::ofstream& outFile , std::string& filename){
    
    outFile.write(reinterpret_cast<char*>(&currentSquenceState) , sizeof(currentSquenceState));

    size_t s = sequencer.size();
    outFile.write(reinterpret_cast<char*>(&s) , sizeof(s));

    for(std::pair<int, int >  pair : sequencer){
        outFile.write(reinterpret_cast<char*>(&pair) , sizeof(pair));

    }

    for(int i = 0 ; i < 5 ; i++){
        for (int j = 0 ; j < 5 ; j++){

            //first saving teh sie of the queue
            size_t s = STATES[i][j].bufferQueue.size();
            outFile.write(reinterpret_cast<char*>(&s) , sizeof(s));

            //then asving the ontent
            while(! STATES[i][j].bufferQueue.empty()){


                State::StateData object = STATES[i][j].bufferQueue.front();
                
                ser_string(object.raw_data , outFile);
                ser_string(object.state_type , outFile);

                STATES[i][j].bufferQueue.pop();
            
            
            }
        }
    }
    
}

void State_map::loadMap(std::ifstream& inFile , std::string& filename) {
    
    
    inFile.read(reinterpret_cast<char*>(&currentSquenceState), sizeof(currentSquenceState));
    
    size_t s;
    inFile.read(reinterpret_cast<char*>(&s), sizeof(s));

    sequencer.clear();
    while(s--)
        {
            std::pair<int ,int> p;
            inFile.read(reinterpret_cast<char*>(&p), sizeof(p));
            sequencer.push_back(p);
        }

     for(int i = 0 ; i < 5 ; i++){
        for (int j = 0 ; j < 5 ; j++){

            //first reading the size of the queue;

            size_t s;
            inFile.read(reinterpret_cast<char*>(&s) , sizeof(s));


            //then asving the ontent
            while(s--){
                State::StateData object;
                object.raw_data = deser_string(inFile);
                object.state_type = deser_string(inFile);
                STATES[i][j].bufferQueue.push(object);
            }
        }
    }
    
    
}

