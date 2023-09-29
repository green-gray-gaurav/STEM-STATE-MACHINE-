#include "hyperQ.hpp"

void hyperSq::push(int cell_index , int i , double d , std::string s , long ref)
{
    struct hyperData hd;
    hd.cell_index = cell_index;
    hd.d = d;
    hd.i = i;
    hd.s = s;
    hd.ref = ref;
    Q.push(hd);
}

void hyperSq::pop()
{
    Q.pop();
}

hyperSq::hyperData  hyperSq::pull()
{
    if(!Q.empty())
        return Q.front();
}
