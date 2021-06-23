//#include "CART.h"
#include <chrono>
#include <iostream>
#include<cmath>

using namespace std;

//non-approximated polynomial formula
double polynomial(int x){
  double total=0;
  total= (1/4.00)+ x * (9/8.00)- pow(x,2) * (15/8.00)+ pow(x,3) * (5/4.00);
  return total;
}

/*
//approximated polynomial formula
double polynomial(int x, CART* c){
  double total=0;
  total= (1/4.00)+ x * (9/8.00)- pow(x,2) * (15/8.00)+ pow(x,3) * (5/4.00);
  //ADD MORE FOR APPROXIMATION
  return total;
}
*/