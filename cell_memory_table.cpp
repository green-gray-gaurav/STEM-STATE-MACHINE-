#include "cell_memory_table.hpp"


//here it should be made nough efficent to retive data


int Cell_table::add(std::string cell_name, std::string map_name)
{
    counter++;
    this->table[counter] = Cell_table::entry( map_name ,cell_name);//this crates an entry in th table
   
    return counter;
}

void Cell_table::removeByCellName(std::string cell_name)
{
   //search the map o(n)
   for(auto e : this->table){
        if(e.second.cell_name == cell_name){
            this->table.erase(e.first);
        break;
        }
   }
}
void Cell_table::removeByCellNameAndMap(std::string cell_name , std::string map_name)
{
   //search the map o(n)
   if(cell_name!="") //remove by cell name and mapname
    {   for(auto e : this->table){
            if(e.second.cell_name == cell_name && e.second.map_name == map_name){
                this->table.erase(e.first);
            break;
            }
   }}
   else{//remove by map_name only
        for(auto e : this->table){
            if(e.second.map_name == map_name){
                this->table.erase(e.first);
            break;
            }
        }    
   }
}

void Cell_table::removeById(int id)
{
    this->table.erase(id);
}

Cell_table::entry Cell_table::searchByCellName(std::string cell_name)
{
    //compledity 0n
    for(auto e : this->table){
        if(e.second.cell_name == cell_name){
            return e.second;
        }
    }
  
}
Cell_table::entry Cell_table::searchByCellNameAndMap(std::string cell_name , std::string mapName)
{
    //compledity 0n
    for(auto e : this->table){
        if(e.second.cell_name == cell_name && e.second.map_name == mapName){
            return e.second;
        }
    }
  
}


int Cell_table::getIdByCellName(std::string cell_name)
{
     //compledity 0n
    for(auto e : this->table){
        if(e.second.cell_name == cell_name){
            return e.first;
        }
    }
   return -1;
}
int Cell_table::getIdByCellNameAndMap(std::string cell_name , std::string map_name)
{
     //compledity 0n
    for(auto e : this->table){
        if(e.second.cell_name == cell_name && e.second.map_name == map_name) {
            return e.first;
        }
    }
   return -1;
}


bool Cell_table::doEntryExist(std::string cell_name)
{
    //compledity 0n
    for(auto e : this->table){
        if(e.second.cell_name == cell_name){
            return true;
        }
    }
   return false;

}
