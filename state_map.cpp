#include "state_map.hpp"
#include <sstream>



  std::vector<std::string> State_map::runMap()
{
    //this is te real deal man
    while(this->sequencer.size() > this->currentSquenceState){

       
            // std::cout << SELECTED_CELL.first << std::endl;
        
        //find and evalur the current state
        std::pair<int, int> stateLoc = (this->sequencer[this->currentSquenceState]);
        State::StateData stateData =  this->STATES[stateLoc.first][stateLoc.second].bufferQueue.front();
        
        //debgginh
        // std::cout << stateData.raw_data << " " << stateData.state_type << std::endl;

        if(stateData.state_type == "CELL"){
            //this is the state secltion cell of the map
            //here you knida chose the current vairable of operation
            int status = this->cellTable->getIdByCellNameAndMap(stateData.raw_data , this->map_name);
            if(status==-1){
                
                  int id_ = cellTable->add(stateData.raw_data , this->map_name);
                  SELECTED_CELL.first = id_;
                  SELECTED_CELL.second = stateData.raw_data;
                //std::cout << id_ << " " << stateData.raw_data << std::endl;
                //adding the selecte cell in recent recent active
                recentSelectedStack->put(id_);

            }
            else{
                SELECTED_CELL.first = status;
                SELECTED_CELL.second = stateData.raw_data; 
                //adding in recnt stack 
                recentSelectedStack->put(status);
            }
            
        }
        else if(stateData.state_type == "PHASE"){ // here is th another selction cell for the phase state
        
            if(stateData.raw_data == "F")  CELL_PAHSE = F;
            else if(stateData.raw_data == "S")  CELL_PAHSE = S;
            else if(stateData.raw_data == "I")  CELL_PAHSE = I;
            else {
                //rintime error error invalid phase;
                return std::vector<std::string>({"E"});
            }
        }
        else if(stateData.state_type == "FEED"){ //sate user //
            //this ont is feed brackets
            // std::cout << "DK: " << D_KEY_TYPE << std::endl;
            
            if (stateData.raw_data[0] == '$')
                { 
                std::string cellName = stateData.raw_data.substr(1, stateData.raw_data.length() - 1);
                Cell_table::entry e = cellTable->searchByCellNameAndMap(cellName, this->map_name);
                   if(D_KEY_TYPE == MOVE)
                   { // cell value // inderting feeding
                    

                    if (CELL_PAHSE == F) // if float phase selcted
                    {
                        cellTable->table[SELECTED_CELL.first].VALUE.decimal = e.VALUE.decimal;
                    }
                    else if (CELL_PAHSE == I)
                    {
                        cellTable->table[SELECTED_CELL.first].VALUE.integer = e.VALUE.integer;
                    }
                    else if (CELL_PAHSE = S)
                    {
                        cellTable->table[SELECTED_CELL.first].VALUE.str = e.VALUE.str;
                    }
                    else if(CELL_PAHSE == R)
                    {
                        //gets the direct refernce
                        int id = cellTable->getIdByCellNameAndMap(cellName , this->map_name);
                        cellTable->table[SELECTED_CELL.first].VALUE.ref = id;
                    }}


                //arithmetics
                else if(D_KEY_TYPE == ADD){
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer += e.VALUE.integer;
                    }
                    else if(CELL_PAHSE == F){
                        cellTable->table[SELECTED_CELL.first].VALUE.decimal += e.VALUE.decimal;
                    }
                    else if(CELL_PAHSE == S){
                        cellTable->table[SELECTED_CELL.first].VALUE.str += e.VALUE.str;
                    }
                }
                else if(D_KEY_TYPE == SUB){
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer -= e.VALUE.integer;
                    }
                    else if(CELL_PAHSE == F){
                        cellTable->table[SELECTED_CELL.first].VALUE.decimal -= e.VALUE.decimal;
                    }
                    
                }
                else if(D_KEY_TYPE == MUL){
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer *= e.VALUE.integer;
                    }
                    else if(CELL_PAHSE == F){
                        cellTable->table[SELECTED_CELL.first].VALUE.decimal *= e.VALUE.decimal;
                    }
                    
                }
                else if(D_KEY_TYPE == DIV){
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer /= e.VALUE.integer;
                    }
                    else if(CELL_PAHSE == F){
                        cellTable->table[SELECTED_CELL.first].VALUE.decimal /= e.VALUE.decimal;
                    }
                    
                }
                //selection process
               else if( D_KEY_TYPE == SELECT){
                    

                    if(cellTable->table[SELECTED_CELL.first].VALUE.integer){
                        cellTable->table[SELECTED_CELL.first].VALUE.str = e.VALUE.str;
                    }
                    
              } 
            

              //realtion code for the vairable conparison

                 //relational operators
            else if (D_KEY_TYPE == GREATER){
               
            
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.integer > e.VALUE.integer;
                    }
                    else if(CELL_PAHSE == F){

                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.decimal > e.VALUE.decimal;
                    }
              }
            else if (D_KEY_TYPE == SMALLER){
                    
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.integer < e.VALUE.integer;
                    }
                    else if(CELL_PAHSE == F){

                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.decimal < e.VALUE.decimal;
                    }

              }
            else if (D_KEY_TYPE == GEQUAL){
                     
            
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer = (cellTable->table[SELECTED_CELL.first].VALUE.integer >= e.VALUE.integer);
                    }
                    else if(CELL_PAHSE == F){

                        cellTable->table[SELECTED_CELL.first].VALUE.integer = (cellTable->table[SELECTED_CELL.first].VALUE.decimal >= e.VALUE.decimal);
                    }

              }
            else if (D_KEY_TYPE == SEQUAL){
                  
            
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.integer <= e.VALUE.integer;
                    }
                    else if(CELL_PAHSE == F){

                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.decimal <= e.VALUE.decimal;
                    }

              }
            else if (D_KEY_TYPE ==  EQUAL){
                  
            
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.integer == e.VALUE.integer;
                    }
                    else if(CELL_PAHSE == F){

                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.decimal == e.VALUE.decimal;
                    }

              }
            else if (D_KEY_TYPE == DIFFERENT){
                   
            
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.integer != e.VALUE.integer
                        ;
                    }
                    else if(CELL_PAHSE == F){

                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.decimal != e.VALUE.decimal;
                    }


              }
            
            }

            else{//constant
                  
                std::string str_data = stateData.raw_data;
                std::stringstream ss;

                // std::cout << ": " << D_KEY_TYPE << str_data << std::endl;
                if (D_KEY_TYPE == MOVE)
                {
                         if (CELL_PAHSE == F) // if float phase selcted
                         {
                             ss << str_data;
                             double d_value;
                             ss >> d_value;
                             cellTable->table[SELECTED_CELL.first].VALUE.decimal = d_value;
                         }
                         else if (CELL_PAHSE == I)
                         {
                             ss << str_data;
                             int intValue;
                             ss >> intValue;
                             cellTable->table[SELECTED_CELL.first].VALUE.integer = intValue;
                         }
                         else if (CELL_PAHSE = S)
                         {
                             cellTable->table[SELECTED_CELL.first].VALUE.str = str_data;
                         }
                         

                }
                else if(D_KEY_TYPE == RECSTACK){

                         if (CELL_PAHSE == R) // if float phase selcted
                         {
                             ss << str_data;
                             double d_value;
                             ss >> d_value;
                             int id_ = (recentSelectedStack->get(d_value)).cell_index;
                             if(id_>0)
                                cellTable->table[SELECTED_CELL.first].VALUE.ref = id_;
                         }   
                }
                else if(D_KEY_TYPE == GETCELLVAL){

                    std::string map_cell_name  = str_data; //here we have this control string

                    int p = map_cell_name.find(":");
                    std::string map_name_ = map_cell_name.substr(0, p);
                    std::string cell_name_ = map_cell_name.substr(p+1 , map_cell_name.length()-p-1);


                    Cell_table::entry e = cellTable->searchByCellNameAndMap(cell_name_ , map_name_);
                    
                    // std::cout << e.VALUE.decimal << " " << e.VALUE.integer << "  " << e.VALUE.str << std::endl; 

                    if (CELL_PAHSE == F) // if float phase selcted
                    {
                        cellTable->table[SELECTED_CELL.first].VALUE.decimal = e.VALUE.decimal;
                    }
                    else if (CELL_PAHSE == I)
                    {
                        cellTable->table[SELECTED_CELL.first].VALUE.integer = e.VALUE.integer;
                    }
                    else if (CELL_PAHSE == S)
                    {
                        cellTable->table[SELECTED_CELL.first].VALUE.str = e.VALUE.str;
                    }

                }
                else if(D_KEY_TYPE == PUTCELLVAL){
                    //here the cell data will be added  to the map of other cell
                    
                    std::string map_cell_name  = str_data; //here we have this control string

                    int p = map_cell_name.find(":");
                    std::string map_name_ = map_cell_name.substr(0, p);
                    std::string cell_name_ = map_cell_name.substr(p+1 , map_cell_name.length()-p-1);
                    int id_ = cellTable->getIdByCellNameAndMap(cell_name_ , map_name_);
                    // std::cout << id_ << std::endl;

                    if (CELL_PAHSE == F) // if float phase selcted
                    {
                        cellTable->table[id_].VALUE.decimal = cellTable->table[SELECTED_CELL.first].VALUE.decimal;
                    }
                    else if (CELL_PAHSE == I)
                    {
                        cellTable->table[id_].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.integer;
                    }
                    else if (CELL_PAHSE == S)
                    {
                        cellTable->table[id_].VALUE.str = cellTable->table[SELECTED_CELL.first].VALUE.str;
                    }


                }
                
                //arithmetics
                else if(D_KEY_TYPE == ADD){

                    ss << str_data; double d_value; ss >> d_value;
                    

                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer += d_value;
                    }
                    else if(CELL_PAHSE == F){
                        cellTable->table[SELECTED_CELL.first].VALUE.decimal += d_value;
                    }
                    else if(CELL_PAHSE == S){
                        cellTable->table[SELECTED_CELL.first].VALUE.str += str_data;
                    }
                }
                else if(D_KEY_TYPE == SUB){
                    ss << str_data; double d_value; ss >> d_value;
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer -= d_value;
                    }
                    else if(CELL_PAHSE == F){
                        cellTable->table[SELECTED_CELL.first].VALUE.decimal -= d_value;
                    }
                    
                }
                else if(D_KEY_TYPE == MUL){
                    ss << str_data; double d_value; ss >> d_value;
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer *= d_value;
                    }
                    else if(CELL_PAHSE == F){
                        cellTable->table[SELECTED_CELL.first].VALUE.decimal *= d_value;
                    }
                    
                }
                else if(D_KEY_TYPE == DIV){
                    ss << str_data; double d_value; ss >> d_value;
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer /= int(d_value);
                    }
                    else if(CELL_PAHSE == F){
                        cellTable->table[SELECTED_CELL.first].VALUE.decimal /=d_value;
                    }
                    
                }

              //here is the importatnt select statemt//conditinll move 
              else if( D_KEY_TYPE == SELECT){
                    if(cellTable->table[SELECTED_CELL.first].VALUE.integer){
                        cellTable->table[SELECTED_CELL.first].VALUE.str = str_data;
                    }
                    
              } 

              //relational operators
            else if (D_KEY_TYPE == GREATER){
                ss << str_data; double d_value; ss >> d_value;
            
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.integer > int(d_value);
                    }
                    else if(CELL_PAHSE == F){

                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.decimal > d_value;
                    }
              }
            else if (D_KEY_TYPE == SMALLER){
                     ss << str_data; double d_value; ss >> d_value;
            
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.integer < int(d_value);
                    }
                    else if(CELL_PAHSE == F){

                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.decimal < d_value;
                    }

              }
            else if (D_KEY_TYPE == GEQUAL){
                     ss << str_data; double d_value; ss >> d_value;
            
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer = (cellTable->table[SELECTED_CELL.first].VALUE.integer >= int(d_value));
                    }
                    else if(CELL_PAHSE == F){

                        cellTable->table[SELECTED_CELL.first].VALUE.integer = (cellTable->table[SELECTED_CELL.first].VALUE.decimal >= d_value);
                    }

              }
            else if (D_KEY_TYPE == SEQUAL){
                     ss << str_data; double d_value; ss >> d_value;
            
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.integer <= int(d_value);
                    }
                    else if(CELL_PAHSE == F){

                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.decimal <= d_value;
                    }

              }
            else if (D_KEY_TYPE ==  EQUAL){
                     ss << str_data; double d_value; ss >> d_value;
            
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.integer == int(d_value);
                    }
                    else if(CELL_PAHSE == F){

                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.decimal == d_value;
                    }

              }
            else if (D_KEY_TYPE == DIFFERENT){
                     ss << str_data; double d_value; ss >> d_value;
            
                    if(CELL_PAHSE == I){
                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.integer != int(d_value);
                    }
                    else if(CELL_PAHSE == F){

                        cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[SELECTED_CELL.first].VALUE.decimal != d_value;
                    }


              }
              
               
 
                


                //here are some more tranformers
            }
        }
        else if(stateData.state_type=="DKEY"){
            
            // if(stateData.raw_data == "IADD"){
            //     if(CELL_PAHSE= F)
            //         cellTable->table[SELECTED_CELL.first].VALUE.decimal += 
            // }
            if(stateData.raw_data == "MOVE") D_KEY_TYPE = MOVE;
            if(stateData.raw_data == "ADD") D_KEY_TYPE = ADD;
            if(stateData.raw_data == "SUB") D_KEY_TYPE = SUB;
            if(stateData.raw_data == "MUL") D_KEY_TYPE = MUL;
            if(stateData.raw_data == "DIV") D_KEY_TYPE = DIV;
            
            if(stateData.raw_data == "GETCELL") D_KEY_TYPE = GETCELLVAL;
            if(stateData.raw_data == "PUTCELL") D_KEY_TYPE = PUTCELLVAL;    
            
            if(stateData.raw_data == "SELECT") D_KEY_TYPE = SELECT;
            if(stateData.raw_data == "SELECTVAL") D_KEY_TYPE = SELECT_VAL;

            if(stateData.raw_data == "GEQL") D_KEY_TYPE = GEQUAL;
            if(stateData.raw_data == "SEQL") D_KEY_TYPE = SEQUAL;
            if(stateData.raw_data == "EQL") D_KEY_TYPE = EQUAL;
            if(stateData.raw_data == "GREATER") D_KEY_TYPE = GREATER;
            if(stateData.raw_data == "SMALLER") D_KEY_TYPE = SMALLER;
            if(stateData.raw_data == "DIFFERENT") D_KEY_TYPE = DIFFERENT;
            // std::cerr << "data: " <<  D_KEY_TYPE <<stateData.raw_data << std::endl;
            // if(stateData.raw_data == "") D_KEY_TYPE = MOVE;
        }
        else if(stateData.state_type =="IKEY"){
            //independent key

            if(stateData.raw_data == "display"){ // this is the display 

                if(CELL_PAHSE==F)
                    std::cout << cellTable->table[SELECTED_CELL.first].VALUE.decimal;
                
                if(CELL_PAHSE==I)
                    std::cout << cellTable->table[SELECTED_CELL.first].VALUE.integer;
                
                if(CELL_PAHSE==S)
                    {   
                        
                        std::string s = cellTable->table[SELECTED_CELL.first].VALUE.str;
                        std::cout << s; //normal string handling
                    
                    }
            }
            //newline 
            else if(stateData.raw_data == "newline"){
                std::cout << std::endl;
            }
            


            else if(stateData.raw_data == "read"){ // this is the read key
                 if(CELL_PAHSE==F)
                    std::cin >>cellTable->table[SELECTED_CELL.first].VALUE.decimal;
                
                if(CELL_PAHSE==I)
                    std::cin >> cellTable->table[SELECTED_CELL.first].VALUE.integer;
                
                if(CELL_PAHSE==S)
                    std::cin >> cellTable->table[SELECTED_CELL.first].VALUE.str;

            }
            //hyper quue  // dynamic type
            else if(stateData.raw_data == "pull"){
                hyperSq::hyperData hd = hyperStateQueue->pull();
                // std::cout << "value: " << hd.cell_index <<cellTable->table[hd.cell_index].VALUE.str << std::endl; 
                if (CELL_PAHSE == F)
                    cellTable->table[SELECTED_CELL.first].VALUE.decimal = cellTable->table[hd.cell_index].VALUE.decimal;
                if (CELL_PAHSE == S)
                    cellTable->table[SELECTED_CELL.first].VALUE.str = cellTable->table[hd.cell_index].VALUE.str;
                if (CELL_PAHSE == I)
                    cellTable->table[SELECTED_CELL.first].VALUE.integer = cellTable->table[hd.cell_index].VALUE.integer;
                
            }
            else if (stateData.raw_data == "pulls"){

                hyperSq::hyperData hd = hyperStateQueue->pull();
                // std::cout << "value: " << hd.cell_index <<cellTable->table[hd.cell_index].VALUE.str << std::endl; 
                if (CELL_PAHSE == F)
                    {cellTable->table[SELECTED_CELL.first].VALUE.decimal = hd.d;}
                if (CELL_PAHSE == S)
                    {cellTable->table[SELECTED_CELL.first].VALUE.str = hd.s;}
                if (CELL_PAHSE == I)
                   { cellTable->table[SELECTED_CELL.first].VALUE.integer = hd.i;}
                

            }

            else if(stateData.raw_data == "pop"){ //hyper pop
                    hyperStateQueue->pop();
            } 
            else if(stateData.raw_data == "push"){//hyper pop
                    //getting the cell entry
                    Cell_table::entry e = cellTable->searchByCellNameAndMap(SELECTED_CELL.second, this->map_name);
                    hyperStateQueue->push(SELECTED_CELL.first , e.VALUE.integer , e.VALUE.decimal , e.VALUE.str , e.VALUE.ref);

            }
            else if (stateData.raw_data == "refer") // refence type cell state key
            {
                CELL_VALUE_PHASE = REFER;
            }
            else if(stateData.raw_data == "self"){ // self type cell state key
                
                CELL_VALUE_PHASE = SELF;
            }

        }
        else if(stateData.state_type =="INCLUDE"){
            //inclusiong of maps
            return std::vector<std::string>({"REQ_MAP_ADD" , stateData.raw_data});

        }
        else if(stateData.state_type == "CHOOK"){
             //map itself cant handle it so it will bw handle by enternal function
           
            //check the condition
            if(cellTable->table[SELECTED_CELL.first].VALUE.integer)
                {
                    std::string mapName = cellTable->table[SELECTED_CELL.first].VALUE.str;
                    return std::vector<std::string>({"REQ" , mapName});
                }

 

        }
        else if(stateData.state_type == "HOOK"){
            //map itself cant handle it so it will bw handle by enternal function
            this->currentSquenceState++;   
            //get the map name from tht active cell
            std::string mapName = cellTable->table[SELECTED_CELL.first].VALUE.str;
            //
             return std::vector<std::string>({"REQ" , mapName});

        }
        //poping the exectuted state cell
        this->STATES[stateLoc.first][stateLoc.second].bufferQueue.pop(); 
        //going to next state in sequence
        this->currentSquenceState++;
    }

    //end of the loop means // map is successfully evaluates
    
    return std::vector<std::string>({"D" , map_name});

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

