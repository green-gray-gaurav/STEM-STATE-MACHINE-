#include "RCS.hpp"

void RCS::flush()
{
    stk.clear();

}

RCS::cellData RCS::get(int index)
{
    if(index < stk.size()){
     std::vector<RCS::cellData>::iterator itr = stk.end()-1;
     while(index--){
        itr--;
     }   
     return *itr;
    }

    RCS::cellData d;
    d.cell_index = -1;
    return d;

}

void RCS::put(int cell_index){
    int limits = 20;
    if(stk.size() >= limits){
        //reducing the stak removing the bottom elm
        //reducing the stack
        stk.erase(stk.begin());

    }
    RCS::cellData cd;
    cd.cell_index = cell_index;
    stk.push_back(cd);
    //put cell daat in the stk

}
