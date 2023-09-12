#include "cell_memory_table.hpp"


//here it should be made nough efficent to retive data


int Cell_table::add(std::string cell_name, std::string map_name)
{
    this->table[this->counter++] = Cell_table::entry( map_name ,cell_name);//this crates an entry in th table
    return this->counter--;
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
