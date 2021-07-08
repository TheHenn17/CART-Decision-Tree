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

void EuclideanNorm::generateRandomTestFile(int instances) {
    srand(time(NULL));
    ofstream outFS;
    double random;
    outFS.open(tf);
    for(int i = 1; i <= instances; i++) {
        for(int j = 0; j < 8; j++) {
            random = rand() % 10 + 1;
            outFS << random << ", ";
        }
        random = rand() % 10 + 1;
        outFS << random << endl;
    }
    outFS.close();
}