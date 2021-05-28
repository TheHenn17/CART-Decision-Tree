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
    string label;
    string type;
    double threshold;
    int index;
    node* left;
    node* right;
};

class CART {
    private:
        node* root;
        vector<string> labels;
        vector<string> types;
        int depth;
    public:
        CART(string input, int d);
        //~CART();
        node* getRoot() { return root; }
        void printTree();
    private:
        node* generateTree(vector<vector<string>> instances, int curDepth);
        void split(vector<vector<string>> instances, string splitValue, int attribute, vector<double>& left, vector<double>& right);
        vector<double> getOutputs(vector<vector<string>> instances);
        double calcImprovement(vector<double> parent, vector<double> left, vector<double> right);
        void getInstances(vector<vector<string>> instances, int bestI, int bestJ, vector<vector<string>>& leftInstances, vector<vector<string>>& rightInstances);
        double getAvg(vector<double> vec);
        void printTree(node* n, int d);
};