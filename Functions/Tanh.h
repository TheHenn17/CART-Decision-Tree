#pragma once

#include "Function.h"

class Tanh : public Function {
    public:
        Tanh(string treeGenerationFile, string testFile, int depth);
        vector<double> compute();
};