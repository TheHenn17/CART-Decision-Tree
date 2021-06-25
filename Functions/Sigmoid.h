#pragma once

#include "Function.h"

class Sigmoid : public Function {
    public:
        Sigmoid(string treeGenerationFile, string testFile, int depth);
        vector<double> compute();
};