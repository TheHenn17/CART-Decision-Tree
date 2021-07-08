#pragma once

#include "Function.h"

class Tanh : public Function {
    public:
        Tanh(string treeGenerationFile, string testFile, int stop);
        vector<double> compute();
        void generateRandomTestFile(int instances);
};