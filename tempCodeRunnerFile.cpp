int main(){

    std::string sc = reader("source_code");
    int flag = 0;
    std::vector< TOKEN> tb = lexical_analyser(sc , flag);

    std::cout << flag ;
    
    for(auto t : tb){
        std::cout << flag << t.token_name << " " << t.raw_data << std::endl;
    }


    return 0;
}