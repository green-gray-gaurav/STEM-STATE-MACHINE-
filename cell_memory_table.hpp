#pragma
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>

//cell table singleton
class Cell_table{
    class entry{
       int map_id;
       int map_name;
       int cell_name;
       std::vector<int>  ref_ids;
    }; 

    std::map<int , entry> table;
    public:
        Cell_table();
        void add(std::string cell_name , int map_id , std::string map_name);
        void removeByCellName(std::string cell_name);
        void removeById(int id);

        entry searchByCellName(std::string cell_name);
        entry getMapBycellName(std::string cell_name);

};