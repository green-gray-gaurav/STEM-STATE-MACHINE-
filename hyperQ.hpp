#include <queue>
//here goes the hyper queue
class hyperSq{
    public:
    struct hyperData
    {
        int cell_index = 0;
        //other data
    };
    
    std::queue<hyperData> Q;
    //hyper functions
    void push(int cell_index);
    void pop();
    hyperData pull();

};
