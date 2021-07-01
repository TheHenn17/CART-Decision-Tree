#pragma once

#include "Function.h"

class Determinant : public Function {
    public:
        Determinant(string treeGenerationFile, string testFile, int stop);
        vector<double> compute();
    private:
        double calcDet(vector<double> mat);
};