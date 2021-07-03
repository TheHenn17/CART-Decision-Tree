#pragma once

#include "Function.h"

class Norm2x2 : public Function {
    public:
        Norm2x2(string treeGenerationFile, string testFile, int stop);
        vector<double> compute();
};