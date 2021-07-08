#include "Sigmoid.h"

Sigmoid::Sigmoid(string treeGenerationFile, string testFile, int stop) 
                    : Function(treeGenerationFile, testFile, stop) {}

vector<double> Sigmoid::compute() {
    vector<double> computes;
    vector<double> instance;
    double total=0;

    for(int i = 0; i < tests.size(); i++) {
        instance = tests.at(i);
        total = 1 / (1 + exp(-instance.at(0)));
        computes.push_back(total);
    }
    return computes;
}

void Sigmoid::generateRandomTestFile(int instances) {
    srand(time(NULL));
    ofstream outFS;
    double random;
    outFS.open(tf);
    for(int i = 1; i <= instances; i++) {
        random = -6 + (double)(rand()) / ((double)(RAND_MAX/12));
        outFS << random << endl;
    }
    outFS.close();
}