#include "CART.h"

void printStringVector(vector<string> v);
void printDoubleVector(vector<double> v);

CART::CART(string input, int d) {
    depth = d;
    ifstream inFS;
    inFS.open(input);
    string data = "";
    stringstream SS;
    if(!inFS.is_open()) {
        cout << "Input file not found\n";
    }
    getline(inFS, data);
    SS << data;
    while(SS >> data) {
        if(data[data.length()-1] == ',') {
            data = data.substr(0, data.length()-1);
        }
        labels.push_back(data);
    }
    SS.clear();
    getline(inFS, data);
    SS << data;
    while(SS >> data) {
        if(data[data.length()-1] == ',') {
            data = data.substr(0, data.length()-1);
        }
        types.push_back(data);
    }
    SS.clear();
    if(getline(inFS, data)) {
        vector<vector<string>> instances;
        SS << data;
        while(SS >> data) {
            if(data[data.length()-1] == ',') {
                data = data.substr(0, data.length()-1);
            }
            vector<string> temp;
            temp.push_back(data);
            instances.push_back(temp);
        }
        SS.clear();
        int index = 0;
        while(getline(inFS, data)) {
            SS << data;
            index = 0;
            while(SS >> data) {
                if(data[data.length()-1] == ',') {
                    data = data.substr(0, data.length()-1);
                }
                instances.at(index).push_back(data);
                index++;
            }
            SS.clear();
        }
        root = generateTree(instances, 0);
    }
    else {
        root = 0;
    }
}

node* CART::generateTree(vector<vector<string>> instances, int curDepth) {
    node* treeRoot = new node;
    if(curDepth == depth || instances.at(0).size() == 1) {
        vector<double> output = getOutputs(instances);
        treeRoot->label = labels.at(labels.size()-1);
        treeRoot->type = types.at(types.size()-1);
        treeRoot->threshold = getAvg(output);
        treeRoot->index = -1;
        treeRoot->right = 0;
        treeRoot->left = 0;
        return treeRoot;
    }
    vector<double> left;
    vector<double> right;
    vector<double> parent;
    double improvement = -DBL_MAX;
    double maxImprovement = improvement;
    int bestI = -1;
    int bestJ = -1;
    for(int i = 0; i < instances.size()-1; i++) {
        for(int j = 0; j < instances.at(i).size(); j++) {
            left.clear();
            right.clear();
            parent.clear();
            split(instances, instances.at(i).at(j), i, left, right);
            improvement = calcImprovement(parent, left, right);
            if(improvement > maxImprovement) {
                maxImprovement = improvement;
                bestI = i;
                bestJ = j;
            }
        }
    }
    treeRoot->label = labels.at(bestI);
    treeRoot->type = types.at(bestI);
    treeRoot->threshold = stod(instances.at(bestI).at(bestJ));
    treeRoot->index = bestI;
    vector<vector<string>> leftInstances;
    vector<vector<string>> rightInstances;
    getInstances(instances, bestI, bestJ, leftInstances, rightInstances);
    node* leftNode = generateTree(leftInstances, curDepth+1);
    node* rightNode = generateTree(rightInstances, curDepth+1);
    treeRoot->left = leftNode;
    treeRoot->right = rightNode;
    return treeRoot;
}

void CART::split(vector<vector<string>> instances, string splitValue, int attribute, vector<double>& left, vector<double>& right) {
    double sv = stod(splitValue);
    for(int i = 0; i < instances.at(attribute).size(); i++) {
        if(stod(instances.at(attribute).at(i)) <= sv) {
            left.push_back(stod(instances.at(instances.size()-1).at(i)));
        }
        else {
            right.push_back(stod(instances.at(instances.size()-1).at(i)));
        }
    }
}

vector<double> CART::getOutputs(vector<vector<string>> instances) {
    vector<double> ret;
    for(int i = 0; i < instances.at(instances.size()-1).size(); i++) {
        ret.push_back(stod(instances.at(instances.size()-1).at(i)));
    }
    return ret;
}

double CART::calcImprovement(vector<double> parent, vector<double> left, vector<double> right) {
    double avgParent = getAvg(parent);
    double avgRight = getAvg(right);
    double avgLeft = getAvg(left);
    double sseParent = 0;
    double sseRight = 0;
    double sseLeft = 0;
    for(int i = 0; i < parent.size(); i++) {
        sseParent += ((parent.at(i)-avgParent) * (parent.at(i)-avgParent));
    }
    for(int i = 0; i < right.size(); i++) {
        sseRight += ((right.at(i)-avgRight) * (right.at(i)-avgRight));
    }
    for(int i = 0; i < left.size(); i++) {
        sseLeft += ((left.at(i)-avgLeft) * (left.at(i)-avgLeft));
    }
    return sseParent - sseRight - sseLeft;
}

void CART::getInstances(vector<vector<string>> instances, int bestI, int bestJ, vector<vector<string>>& leftInstances, vector<vector<string>>& rightInstances) {
    double sv = stod(instances.at(bestI).at(bestJ));
    for(int i = 0; i < instances.size(); i++) {
        vector<string> temp;
        leftInstances.push_back(temp);
        vector<string> temp2;
        rightInstances.push_back(temp2);
    }
    for(int i = 0; i < instances.size(); i++) {
        for(int j = 0; j < instances.at(i).size(); j++) {
            if(stod(instances.at(bestI).at(j)) <= sv) {
                leftInstances.at(i).push_back(instances.at(i).at(j));
            }
            else {
                rightInstances.at(i).push_back(instances.at(i).at(j));
            }
        }
    }
}

double CART::getAvg(vector<double> vec) {
    double avg = 0;
    for(int i = 0; i < vec.size(); i++) {
        avg += vec.at(i);
    }
    if(avg == 0) {
        return avg;
    }
    return avg / vec.size();
}

void CART::printTree() {
    node* n = root;
    printTree(n, 0);
}

void CART::printTree(node* n, int d) {
    if(n == 0) {
        cout << endl;
        return;
    }
    for(int i = 0; i < d; i++) {
        cout << "\t";
    }
    cout << n->label << endl;
    for(int i = 0; i < d; i++) {
        cout << "\t";
    }
    cout << n->type << endl;
    for(int i = 0; i < d; i++) {
        cout << "\t";
    }
    cout << n->threshold << endl;
    printTree(n->right, d+1);
    printTree(n->left, d+1);
}



void printStringVector(vector<string> v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v.at(i) << " ";
    }
    cout << endl;
}

void printDoubleVector(vector<double> v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v.at(i) << " ";
    }
    cout << endl;
}