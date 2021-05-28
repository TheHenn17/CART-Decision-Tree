#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cfloat>
#include <math.h>

using namespace std;

struct Centroid {
    double r;
    double g;
    double b;
};

struct RgbPixel {
    double r;
    double g;
    double b;
};

struct node {
    string label; //stores the name of the input
    string type; //store the input type (discrete or continous)
    double threshold; //stores the threshold value or the leaf value
    int index; //holds the index of the input name, for comparing the threshold to new instances
    node* left; //left child
    node* right; //right child
};

class CART {
    private:
        node* root; //root of the tree
        vector<string> labels; //list of input names
        vector<string> types; //list of input types
        int depth; //depth of the tree
    public:
        //constructor: takes in training data file name and the desired depth of the tree
        CART(string input, int d);
        //~CART();
        node* getRoot() { return root; }
        void printTree();
    private:
        /*called by constructor. will find the attributes in the training data that improves
        the search the most (see calcImprovement). Then, it splits the input domain according
        to the attribute chose, and recursively calculates the child subtrees*/
        node* generateTree(vector<vector<string>> instances, int curDepth);

        /*given a potential split value, this function seperates the output domain by the instances
        that are less than or equal to the split value, and those that are greater*/
        void split(vector<vector<string>> instances, string splitValue, int attribute, vector<double>& left, vector<double>& right);

        //returns the output domain of the given set of instances
        vector<double> getOutputs(vector<vector<string>> instances);

        /*calcuates the improvement from the parents output domain to the childrens output domains
        using the sum of squares method. the more improvement, the better the split is*/
        double calcImprovement(vector<double> parent, vector<double> left, vector<double> right);

        //splits the input domain according to the best split value found, uses this split for the recursive call
        void getInstances(vector<vector<string>> instances, int bestI, int bestJ, vector<vector<string>>& leftInstances, vector<vector<string>>& rightInstances);

        //finds the average of a vector of doubles.
        double getAvg(vector<double> vec);

        //helper function to the tree print; prints tree recursively, using tabs according to the depth
        void printTree(node* n, int d);
};