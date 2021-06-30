#include "MatrixMult3x3.h"

MatrixMult3x3::MatrixMult3x3(string treeGenerationFile, string testFile, int stop) 
                    : Function(treeGenerationFile, testFile, stop) {}

vector<double> MatrixMult3x3::compute() {
    vector<double> computes;
    vector<double> instance;
    double ans;

    for(int i = 0; i < tests.size(); i++) {
        instance = tests.at(i);
        ans = 0;
        ans += instance.at(0)*instance.at(3);
        ans += instance.at(1)*instance.at(4);
        ans += instance.at(2)*instance.at(5);
        computes.push_back(ans);
    }
    return computes;
}