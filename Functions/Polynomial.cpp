#include "Polynomial.h"

Polynomial::Polynomial(string treeGenerationFile, string testFile, int stop) 
                    : Function(treeGenerationFile, testFile, stop) {}

vector<double> Polynomial::compute() {
    vector<double> computes;
    vector<double> instance;
    double total=0;

    for(int i = 0; i < tests.size(); i++) {
        instance = tests.at(i);
        total = (1/4.00) + instance.at(0) * (9/8.00)- pow(instance.at(0),2) * (15/8.00)+ pow(instance.at(0),3) * (5/4.00);
        computes.push_back(total);
    }
    return computes;
}