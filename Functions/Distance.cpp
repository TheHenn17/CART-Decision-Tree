#include "Distance.h"

Distance::Distance(string treeGenerationFile, string testFile, int stop) 
                    : Function(treeGenerationFile, testFile, stop) {}

vector<double> Distance::compute() {
    double r;
    vector<double> computes;
    vector<double> instance;

    for(int i = 0; i < tests.size(); i++) {
        r = 0;
        instance = tests.at(i);
        r += ((instance.at(0) - instance.at(3)) * (instance.at(0) - instance.at(3)));
        r += ((instance.at(1) - instance.at(4)) * (instance.at(1) - instance.at(4)));
        r += ((instance.at(2) - instance.at(5)) * (instance.at(2) - instance.at(5)));
        computes.push_back(sqrt(r));
    }
    return computes;
}

void Distance::generateRandomTestFile(int instances) {
    srand(time(NULL));
    ofstream outFS;
    double random;
    outFS.open(tf);
    for(int i = 1; i <= instances; i++) {
        for(int j = 0; j < 5; j++) {
            random = rand() % 256;
            outFS << random << ", ";
        }
        random = rand() % 256;
        outFS << random << endl;
    }
    outFS.close();
}