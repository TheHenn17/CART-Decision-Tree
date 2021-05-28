#include "CART.h"

//constructor: takes in training data file name and the desired depth of the tree
CART::CART(string input, int d) {
    depth = d; //set depth to desired depth
    ifstream inFS;
    inFS.open(input); //open the input file
    string data = "";
    stringstream SS;
    if(!inFS.is_open()) {
        cout << "Input file not found\n";
    }
    getline(inFS, data); //get first line of file, contains the labels
    SS << data;
    //parse the line and store the labels
    while(SS >> data) {
        if(data[data.length()-1] == ',') {
            data = data.substr(0, data.length()-1);
        }
        labels.push_back(data);
    }
    SS.clear();
    getline(inFS, data); //get second line of file, contains the types
    SS << data;
    //parse the line and store the types
    while(SS >> data) {
        if(data[data.length()-1] == ',') {
            data = data.substr(0, data.length()-1);
        }
        types.push_back(data);
    }
    SS.clear();
    if(getline(inFS, data)) {
        vector<vector<string>> instances; //stores the instances by attributes (inputs)
        SS << data;
        //adds the first instance, special case that needs to push the vectors into the 2D vector
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
        //adds the remaining instances
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
        root = generateTree(instances, 0); //generates the tree and returns the root
    }
    else {
        root = 0;
    }
}

/*called by constructor. will find the attributes in the training data that improves
the search the most (see calcImprovement). Then, it splits the input domain according
to the attribute chose, and recursively calculates the child subtrees*/
node* CART::generateTree(vector<vector<string>> instances, int curDepth) {
    node* treeRoot = new node; //create a new node

    //if true, this call produces a leaf, calculate average of output domain and store as leaf value (in threshold)
    if(curDepth == depth || instances.at(0).size() == 1) {
        vector<double> output = getOutputs(instances); //find output space
        treeRoot->label = labels.at(labels.size()-1); //last label is the output name
        treeRoot->type = types.at(types.size()-1); //last type is the output type
        treeRoot->threshold = getAvg(output);
        treeRoot->index = -1; //-1 indicates leaf
        treeRoot->right = 0;
        treeRoot->left = 0;
        return treeRoot;
    }
    vector<double> left; //will store output space of instances <= potential split value
    vector<double> right; //will store output space of instances > potential split value
    vector<double> parent = getOutputs(instances); //will store output space of all given instances for this call
    double improvement = -DBL_MAX;
    double maxImprovement = improvement;
    int bestI = -1;
    int bestJ = -1;

    //nested for loop will try every value for every attribute in input domain as a potential split
    for(int i = 0; i < instances.size()-1; i++) {
        for(int j = 0; j < instances.at(i).size(); j++) {
            left.clear(); //clear old values
            right.clear(); //clear old values
            split(instances, instances.at(i).at(j), i, left, right); //split output domain according to potential value
            improvement = calcImprovement(parent, left, right); //calculate improvement of output space

            //finds max improvement in this input space
            if(improvement > maxImprovement) {
                maxImprovement = improvement;
                bestI = i;
                bestJ = j;
            }
        }
    }
    //found split value with most improvement, will split tree accordingly and recursively call each subtree
    treeRoot->label = labels.at(bestI);
    treeRoot->type = types.at(bestI);
    treeRoot->threshold = stod(instances.at(bestI).at(bestJ));
    treeRoot->index = bestI;
    vector<vector<string>> leftInstances;
    vector<vector<string>> rightInstances;
    getInstances(instances, bestI, bestJ, leftInstances, rightInstances); //splits input domains into left and right
    node* leftNode = generateTree(leftInstances, curDepth+1); //generates left tree
    node* rightNode = generateTree(rightInstances, curDepth+1); //generates right tree
    treeRoot->left = leftNode; //append subtree
    treeRoot->right = rightNode; //append subtree
    return treeRoot;
}

/*given a potential split value, this function seperates the output domain by the instances
that are less than or equal to the split value, and those that are greater*/
void CART::split(vector<vector<string>> instances, string splitValue, int attribute, vector<double>& left, vector<double>& right) {
    double sv = stod(splitValue); //convert split value to a double

    //loop through all instances
    for(int i = 0; i < instances.at(attribute).size(); i++) {
        if(stod(instances.at(attribute).at(i)) <= sv) { //if this instance is <= split, add instance output to left output domain
            left.push_back(stod(instances.at(instances.size()-1).at(i)));
        }
        else { //if this instance is > split, add instance output to right output domain
            right.push_back(stod(instances.at(instances.size()-1).at(i)));
        }
    }
}

//returns the output domain of the given set of instances
vector<double> CART::getOutputs(vector<vector<string>> instances) {
    vector<double> ret;
    for(int i = 0; i < instances.at(instances.size()-1).size(); i++) {
        ret.push_back(stod(instances.at(instances.size()-1).at(i)));
    }
    return ret;
}

/*calcuates the improvement from the parents output domain to the childrens output domains
using the sum of squares method. the more improvement, the better the split is
Formula: Improvement = sum(parent(i)-parent(avg))^2 - sum(left(i)-left(avg))^2 - sum(right(i)-right(avg))^2
https://machinelearningmastery.com/classification-and-regression-trees-for-machine-learning/*/
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

//splits the input domain according to the best split value found, uses this split for the recursive call
void CART::getInstances(vector<vector<string>> instances, int bestI, int bestJ, vector<vector<string>>& leftInstances, vector<vector<string>>& rightInstances) {
    double sv = stod(instances.at(bestI).at(bestJ)); //convert string to double

    //initialize 2D vectors
    for(int i = 0; i < instances.size(); i++) {
        vector<string> temp;
        leftInstances.push_back(temp);
        vector<string> temp2;
        rightInstances.push_back(temp2);
    }

    //loop through the entire input space
    for(int i = 0; i < instances.size(); i++) {
        for(int j = 0; j < instances.at(i).size(); j++) {
            if(stod(instances.at(bestI).at(j)) <= sv) { //if instance <= split value, add to left child instances
                leftInstances.at(i).push_back(instances.at(i).at(j));
            }
            else { //if instance > split value, add to right child instances
                rightInstances.at(i).push_back(instances.at(i).at(j));
            }
        }
    }
}

//finds the average of a vector of doubles.
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

//prints tree (using private print tree not accessible to user)
void CART::printTree() {
    node* n = root;
    printTree(n, 0);
}

//prints tree recursively, using tabs according to the depth
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