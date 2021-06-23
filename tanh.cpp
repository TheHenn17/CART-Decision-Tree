//#include "CART.h"
#include <chrono>
#include <iostream>
#include<cmath>

using namespace std;

//non-approximated tanh formula
double tanh(int x, int n){
  int total=0;
  total= (exp(x) - exp(-x)) / (exp(x) + exp(-x));
  return total;
}

/*
//approximated tanh formula
double tanh(int x, int, n, CART* c){
  int total=0;
  total= (exp(x) - exp(-x)) / (exp(x) + exp(-x));
  return total;
}
*/