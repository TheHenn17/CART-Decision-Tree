//#include "CART.h"
#include <chrono>
#include <iostream>
#include<cmath>
#include<vector>

//non-approximated sigmoid formula
double sigmoid (int x) {
    double total= 1 / (1 + exp(-x));
    return total;
} 