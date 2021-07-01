#pragma once

#include "Function.h"

class ComplexPolynomial : public Function {
    public:
        ComplexPolynomial(string treeGenerationFile, string testFile, int stop);
        vector<double> compute();
};