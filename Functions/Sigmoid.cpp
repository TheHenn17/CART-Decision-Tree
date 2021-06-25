#include "Sigmoid.h"

Sigmoid::Sigmoid(string treeGenerationFile, string testFile, int depth) 
                    : Function(treeGenerationFile, testFile, depth) {}

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

