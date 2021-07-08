#pragma once

#include "Function.h"

class Distance : public Function {
    public:
        Distance(string treeGenerationFile, string testFile, int stop);
        vector<double> compute();
        void generateRandomTestFile(int instances);
};