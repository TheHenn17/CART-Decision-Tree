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

/*
//approximated sigmoid formula
double sigmoid(int x, CART* c){
  double total=0;
  double total= 1 / (1 + exp(-x));
  //ADD MORE FOR APPROXIMATION
  return total;
}
*/