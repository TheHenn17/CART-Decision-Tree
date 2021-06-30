#include "Tanh.h"

Tanh::Tanh(string treeGenerationFile, string testFile, int stop) 
                    : Function(treeGenerationFile, testFile, stop) {}

vector<double> Tanh::compute() {
    vector<double> computes;
    vector<double> instance;
    double total=0;

    for(int i = 0; i < tests.size(); i++) {
        instance = tests.at(i);
        total = (exp(instance.at(0)) - exp(-instance.at(0))) / (exp(instance.at(0)) + exp(-instance.at(0)));
        computes.push_back(total);
    }
    return computes;
}
