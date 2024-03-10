
#ifndef Time_hpp
#define Time_hpp

#include <chrono>
#include <iostream>

class Time{
public:
    Time(){
        start = std::chrono::high_resolution_clock::now();
    }
    
    ~Time(){
        const auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - start).count();
        std::cout << duration << " ms \n";
    }
    
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};


#endif /* Time_hpp */
