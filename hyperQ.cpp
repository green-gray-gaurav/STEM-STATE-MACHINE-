#include "hyperQ.hpp"

void hyperSq::push(int cell_index)
{
    struct hyperData hd;
    hd.cell_index = cell_index;
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
