#pragma once

#include "Function.h"

class ComplexPolynomial : public Function {
    public:
        ComplexPolynomial(string treeGenerationFile, string testFile, int depth);
        vector<double> compute();
};