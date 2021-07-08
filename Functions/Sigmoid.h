#pragma once

#include "Function.h"

class Sigmoid : public Function {
    public:
        Sigmoid(string treeGenerationFile, string testFile, int stop);
        vector<double> compute();
        void generateRandomTestFile(int instances);
};