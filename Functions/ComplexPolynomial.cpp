#include "ComplexPolynomial.h"

ComplexPolynomial::ComplexPolynomial(string treeGenerationFile, string testFile, int stop) 
                    : Function(treeGenerationFile, testFile, stop) {}

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

void ComplexPolynomial::generateRandomTestFile(int instances) {
    srand(time(NULL));
    ofstream outFS;
    double random;
    outFS.open(tf);
    for(int i = 1; i <= instances; i++) {
        random = -1 + (double)(rand()) / ((double)(RAND_MAX/2));
        outFS << random << ", 2" << endl;
    }
    outFS.close();
}