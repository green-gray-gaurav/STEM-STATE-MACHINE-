#pragma
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>

//cell table singleton
class Cell_table{
    public:
    class entry{
        public:

        entry(){

        }
        entry(std::string mname , std::string cellname){
            //meta data
            this->map_name = mname;
            this->cell_name = cellname;
        }
       std::string map_name;
       std::string cell_name;
       std::vector<int>  ref_ids;
       //set get function to maintain the refecne in the entry

            //cell value
        struct  value
        {
               int integer;
               float decimal;
               std::string str;

        };
        struct value VALUE;
       void setRef(std::vector<int> rf){
            ref_ids = rf;
       }
       std::vector<int> getRef(){
            return ref_ids;
       }

    }; 
    //cell id to entry refernce in teh table
    std::map<int , entry> table;

    int counter = 0;
    public:
       
        int add(std::string cell_name  , std::string map_name);

        
        void removeByCellName(std::string cell_name);
        void removeById(int id);

        entry searchByCellName(std::string cell_name);
        int getIdByCellName(std::string cell_name);

        bool doEntryExist(std::string cell_name);
        // entry getMapBycellName(std::string cell_name);

        

};