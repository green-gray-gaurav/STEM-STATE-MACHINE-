#include <vector>
//here goes the hyper queue
class RCS{
    public:
    struct cellData
    {
        int cell_index = 0;

        //inital data frame
        
        //other data
    };
    std::vector<cellData> stk;
    //hyper functions
    void flush();
    cellData get(int index);
    void put(int index);
};
