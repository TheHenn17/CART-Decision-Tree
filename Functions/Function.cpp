#include "Function.h"

Function::Function(string treeGenerationFile, string testFile, int stop) {
    tgf = treeGenerationFile;
    tf = testFile;
    ifstream inFS;
    string data;
    inFS.open(testFile);
    stringstream SS;

    if(!inFS.is_open()) {
        cout << "Error: File " << testFile << " does not exist\n";
        exit(1);
    }

    while(getline(inFS, data)) {
        SS << data;
        vector<double> v;
        while(SS >> data) {
            if(data[data.length()-1] == ',') {
                data = data.substr(0, data.length()-1);
            }
            v.push_back(stod(data));
        }
        tests.push_back(v);
        SS.clear();
    }

    inFS.close();
    tree = new CART(treeGenerationFile, stop);
}

vector<double> Function::approximate() {
    node* search;
    vector<double> approx;

    for(int i = 0; i < tests.size(); i++) {
        search = tree->getRoot();
        while(search->index != -1) {
            if(tests.at(i).at(search->index) <= search->threshold) {
                search = search->left;
            }
            else {
                search = search->right;
            }
        }
        approx.push_back(search->threshold);
    }

    return approx;
}

void Function::printTree() {
    tree->printTree();
}

void Function::createTreeFileFromTestFile() {
    vector<double> computes = compute();
    ofstream outFS;
    ifstream inFS;
    string data, ftl;
    inFS.open(tgf);
    if(!inFS.is_open()) {
        cout << "Error: File " << tgf << " does not exist\n";
        exit(1);
    }
    getline(inFS, data);
    ftl = data + "\n";
    getline(inFS, data);
    ftl += data;
    inFS.close();

    outFS.open(tgf);
    outFS << ftl << endl;
    vector<double> instance;

    for(int i = 0; i < tests.size(); i++) {
        instance = tests.at(i);
        for(int j = 0; j < instance.size(); j++) {
            outFS << instance.at(j) << ", ";
        }
        outFS << computes.at(i) << endl;
    }
    outFS.close();
}