#pragma once

#include "../CART.h"

class Function {
    protected:
        CART* tree;
        vector<vector<double> > tests;
        string tgf;
        string tf;
    public:
        Function(string treeGenerationFile, string testFile, int stop);
        virtual vector<double> compute() = 0;
        virtual void generateRandomTestFile(int instances) = 0;
        void createTreeFileFromTestFile();
        vector<double> approximate();
        void printTree();
};