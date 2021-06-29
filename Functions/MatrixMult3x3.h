#pragma once

#include "Function.h"

class MatrixMult3x3 : public Function {
    public:
        MatrixMult3x3(string treeGenerationFile, string testFile, int depth);
        vector<double> compute();
};