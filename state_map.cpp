#pragma
#include "state_map.hpp"

State_map::State_map()
{
}

void State_map::runMap()
{
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

