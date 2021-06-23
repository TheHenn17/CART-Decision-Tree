//#include "CART.h"
#include <chrono>
#include <iostream>
#include<cmath>

using namespace std;

//non-approximated complexPolynomial formula
double complexPolynomial(int x, int n){
  int total=0;
  total= (exp(n * x / 2) - exp(n * x / -2)) / (exp(n * x / 2) + exp(n * x / -2));
  return total;
}

/*
//approximated complexPolynomial formula
double complexPolynomial(int x, int, n, CART* c){
  int total=0;
  total= (exp(n * x / 2) - exp(n * x / -2)) / (exp(n * x / 2) + exp(n * x / -2));
  //ADD MORE FOR APPROXIMATION
  return total;
}
*/