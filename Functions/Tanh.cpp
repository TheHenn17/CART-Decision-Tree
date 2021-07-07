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

void Tanh::generateRandomTestFile(int instances) {
    srand(time(NULL));
    ofstream outFS;
    double random;
    cout << tf;
    outFS.open(tf);
    for(int i = 1; i <= instances; i++) {
        random = -1 + (double)(rand()) / ((double)(RAND_MAX/2));
        outFS << random << endl;
    }
    outFS.close();
}