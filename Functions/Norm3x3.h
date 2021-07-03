#pragma once

#include "Function.h"

class Norm3x3 : public Function {
    public:
        Norm3x3(string treeGenerationFile, string testFile, int stop);
        vector<double> compute();
};