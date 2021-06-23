#pragma once

#include "Function.h"

class Distance : public Function {
    public:
        Distance(string treeGenerationFile, string testFile, int depth);
        vector<double> compute();
};