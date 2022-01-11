# ifndef _RANDOM_H_
# define _RANDOM_H_
#include <random>
#include <algorithm>

class Random {
public: 
    // generates random number from min to max inclusive
    static int getRand(int min, int max) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> uni(min, max);
        return uni(rng);
    }
};

# endif