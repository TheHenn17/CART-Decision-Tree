#include "EuclideanNorm.h"

EuclideanNorm::EuclideanNorm(string treeGenerationFile, string testFile, int stop) 
                    : Function(treeGenerationFile, testFile, stop) {}

vector<double> EuclideanNorm::compute() {
    vector<double> computes;
    vector<double> instance;
    double total = 0;
    double sq;

    for(int i = 0; i < tests.size(); i++) {
        instance = tests.at(i);
        sq = sqrt(instance.size());
        if(sq - floor(sq) == 0) {
            for(int j = 0; j < instance.size(); j++) {
                total += instance.at(j)*instance.at(j);
            }
            computes.push_back(sqrt(total));
        }
        else {
            cout << "Error: Norm of a non-square matrix cannot be computed";
            exit(1);
        }
    }
    return computes;
}

/*
0A1, 1A2, 2B1, 3B2
[a1][a2]
[b1][b2]

*/