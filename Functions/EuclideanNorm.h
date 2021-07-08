#pragma once

#include "Function.h"

class EuclideanNorm : public Function {
    public:
        EuclideanNorm(string treeGenerationFile, string testFile, int stop);
        vector<double> compute();
        void generateRandomTestFile(int instances);
};