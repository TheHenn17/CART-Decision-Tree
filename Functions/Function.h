#pragma once

#include <stdlib.h>
#include "../CART.h"

class Function {
    protected:
        CART* tree;
        vector<vector<double> > tests;
    public:
        Function(string treeGenerationFile, string testFile, int stop);
        virtual vector<double> compute() = 0;
        vector<double> approximate();
        void printTree();
        void createTreeFileFromTestFile(string file);
};