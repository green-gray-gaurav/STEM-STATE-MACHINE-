#include <queue>
#include <iostream>
//here goes the hyper queue
class hyperSq{
    public:
    struct hyperData
    {
        int cell_index = 0;
        //other data
        int i;
        double d;
        std::string s;
        long ref;
    };
    
    std::queue<hyperData> Q;
    //hyper functions
    void push(int cell_index , int i , double d , std::string s , long ref);
    void pop();
    hyperData pull();

};
