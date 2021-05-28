#include "CART.h"
#include <chrono>

const int TESTS = 100;

double distance(Centroid* c1, RgbPixel* p); //non-approximated distance formula
double distance(Centroid* c1, RgbPixel* p, CART* c); //approximated distance formula
Centroid* getRandomCentroid(); //generates a random centroid
RgbPixel* getRandomRgbPixel(); //generates a random rgb pixel
void generate(string input); //generates a file of 500 random centroids and pixels and their distances

int main() {
    srand (time(NULL)); //random number seed
    //generate("distance.dat");
    CART* c = new CART("distance.dat", 3); //create decision tree from 'distance.dat'
    c->printTree(); //print the tree

    //following code will generate 100 centroids and pixels for testing the tree
    vector<Centroid*> cents;
    vector<RgbPixel*> pixs;
    for(int i = 0; i < TESTS; i++) {
        cents.push_back(getRandomCentroid());
        pixs.push_back(getRandomRgbPixel());
    }

    //following code will run the non-approximated distance formula on the test cases and store the distances
    //also times how long this process takes
    vector<double> answers;
    auto start1 = std::chrono::steady_clock::now();
    for(int i = 0; i < TESTS; i++) {
        answers.push_back(distance(cents.at(i), pixs.at(i)));
    }
    auto stop1 = std::chrono::steady_clock::now();

    //following code will run the approximated distance formula on the test cases and store the distances
    //also times how long this process takes
    vector<double> approximations;
    auto start2 = std::chrono::steady_clock::now();
    for(int i = 0; i < TESTS; i++) {
        approximations.push_back(distance(cents.at(i), pixs.at(i), c));
    }
    auto stop2 = std::chrono::steady_clock::now();

    //following code will calcuate the average error of the decision tree's answers
    double sum = 0;
    for(int i = 0; i < TESTS; i++) {
        sum += (approximations.at(i)-answers.at(i))/answers.at(i);
    }
    cout << "Average error: " << sum / TESTS << endl;

    //following code will calculate the run-time of each distance function and output it
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
    cout << "Time taken by Formula: " << duration1.count() << " microseconds" << endl;
    cout << "Time taken by Tree: " << duration2.count() << " microseconds";

    return 0;
}

//non-approximated distance function
double distance(Centroid* c1, RgbPixel* p) {
    double r = 0;
    r += ((c1->r - p->r) * (c1->r - p->r));
    r += ((c1->g - p->g) * (c1->g - p->g));
    r += ((c1->b - p->b) * (c1->b - p->b));
    return sqrt(r);
}

//approximated distance function with decision tree
double distance(Centroid* c1, RgbPixel* p, CART* c) {
    node* search = c->getRoot(); //gets root of tree

    //stores the values of the centroid and rgbpixels
    vector<double> v;
    v.push_back(c1->r);
    v.push_back(c1->g);
    v.push_back(c1->b);
    v.push_back(p->r);
    v.push_back(p->g);
    v.push_back(p->b);

    //while not at a leaf, search left or right according to the threshold value and the given inputs
    while(search->index != -1) {
        if(v.at(search->index) <= search->threshold) {
            search = search->left;
        }
        else {
            search = search->right;
        }
    }

    return search->threshold; //return the leaf threshold (predicted value)
}

//generates a random centroid
Centroid* getRandomCentroid() {
    Centroid* c = new Centroid;
    c->r = rand() % 256;
    c->g = rand() % 256;
    c->b = rand() % 256;
    return c;
}

//generates a random rgb pixel
RgbPixel* getRandomRgbPixel() {
    RgbPixel* p = new RgbPixel;
    p->r = rand() % 256;
    p->g = rand() % 256;
    p->b = rand() % 256;
    return p;
}

//generates a file of 500 random centroids and pixels and their distances for training
void generate(string input) {
    ofstream outFS;
    outFS.open(input);
    outFS << "cR, cG, cB, pR, pG, pB, Distance\n";
    outFS << "Continous, Continous, Continous, Continous, Continous, Continous, Continous\n";
    Centroid* c;
    RgbPixel* p;
    for(int i = 0; i < 500; i++) {
        c = getRandomCentroid();
        p = getRandomRgbPixel();
        outFS << c->r << ", ";
        outFS << c->g << ", ";
        outFS << c->b << ", ";
        outFS << p->r << ", ";
        outFS << p->g << ", ";
        outFS << p->b << ", ";
        outFS << distance(c, p) << "\n";
        delete c;
        delete p;
    }
    outFS.close();
}