#include "Norm2x2.h"

Norm2x2::Norm2x2(string treeGenerationFile, string testFile, int stop) 
                    : Function(treeGenerationFile, testFile, stop) {}

vector<double> Norm2x2::compute() {
    vector<double> computes;
    vector<double> instance;
    double total=0;
    double first=0;
    double second= 0;
    double third=0;

    for(int i = 0; i < tests.size(); i++) {
        instance = tests.at(i);
        total=(instance.at(0)*instance.at(3)) - (instance.at(1)*instance.at(2));
        computes.push_back(total);
    }
    return computes;
}

/*
0A1, 1A2, 2B1, 3B2
[a1][a2]
[b1][b2]

*/