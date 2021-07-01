#include "Determinant.h"

Determinant::Determinant(string treeGenerationFile, string testFile, int stop) 
                    : Function(treeGenerationFile, testFile, stop) {}

vector<double> Determinant::compute() {
    vector<double> computes;
    vector<double> instance;
    double sq, det;

    for(int i = 0; i < tests.size(); i++) {
        instance = tests.at(i);
        sq = sqrt(instance.size());
        if(sq - floor(sq) == 0) {
            det = calcDet(instance);
        }
        else {
            cout << "Error: Determinant of a non-square matrix cannot be computed";
            exit(1);
        }
        computes.push_back(det);
    }
    return computes;
}

double Determinant::calcDet(vector<double> mat) {
    if(mat.size() == 0) {
        return 0;
    }
    if(mat.size() == 1) {
        return mat.at(0);
    }
    if(mat.size() == 4) {
        return (mat.at(0)*mat.at(3)) - (mat.at(1)*mat.at(2));
    }
    else {
        int sq = sqrt(mat.size());
        double det = 0;
        vector<double> temp;
        for(int i = 0; i < sq; i++) {
            temp.clear();
            for(int j = sq; j < mat.size(); j++) {
                if(j%sq != i) {
                    temp.push_back(mat.at(j));
                }
            }
            if(i%2 == 0) {
                det += mat.at(i)*calcDet(temp);
            }
            else {
                det -= mat.at(i)*calcDet(temp);
            }
        }
        return det;
    }
}