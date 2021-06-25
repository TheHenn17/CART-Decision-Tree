#include "ComplexPolynomial.h"

ComplexPolynomial::ComplexPolynomial(string treeGenerationFile, string testFile, int depth) 
                    : Function(treeGenerationFile, testFile, depth) {}

vector<double> ComplexPolynomial::compute() {
    vector<double> computes;
    vector<double> instance;
    double total=0;

    for(int i = 0; i < tests.size(); i++) {
        instance = tests.at(i);
        total = (exp(instance.at(1) * instance.at(0) / 2) - exp(instance.at(1) * instance.at(0) / -2)) / (exp(instance.at(1) * instance.at(0)/ 2) + exp(instance.at(1) * instance.at(0) / -2));
        computes.push_back(total);
    }
    return computes;
}
