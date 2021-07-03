#include "Norm3x3.h"

Norm3x3::Norm3x3(string treeGenerationFile, string testFile, int stop) 
                    : Function(treeGenerationFile, testFile, stop) {}

vector<double> Norm3x3::compute() {
    vector<double> computes;
    vector<double> instance;
    double total=0;
    double first=0;
    double second= 0;
    double third=0;

    for(int i = 0; i < tests.size(); i++) {
        instance = tests.at(i);
        first=instance.at(0)*((instance.at(4)*instance.at(8)) - (instance.at(5)*instance.at(7)));
        second=instance.at(1)*((instance.at(3)*instance.at(8)) - (instance.at(5)*instance.at(6)));
        third=instance.at(2)*((instance.at(3)*instance.at(7)) - (instance.at(4)*instance.at(6)));
        total= sqrt((first*first) + (second*second) + (third*third));
        computes.push_back(total);
    }
    return computes;
}

/*
0A1, 1A2, 2A3, 3B1, 4B2, 5B3, 6C1, 7C2, 8C3
[a1][a2][a3]
[b1][b2][b3]
[c1][c2][c3]
*/