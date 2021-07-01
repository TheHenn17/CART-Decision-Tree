#pragma once

#include "Function.h"

class Polynomial : public Function {
    public:
        Polynomial(string treeGenerationFile, string testFile, int stop);
        vector<double> compute();
};