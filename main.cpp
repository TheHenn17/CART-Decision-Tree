#include "CART.h"
#include <chrono>

double distance(Centroid* c1, RgbPixel* p);
double distance(Centroid* c1, RgbPixel* p, CART* c);
Centroid* getRandomCentroid();
RgbPixel* getRandomRgbPixel();
void generate(string input);

int main() {
    srand (time(NULL));
    //generate("distance.dat");
    CART* c = new CART("distance.dat", 4);
    c->printTree();

    vector<Centroid*> cents;
    vector<RgbPixel*> pixs;
    for(int i = 0; i < 100; i++) {
        cents.push_back(getRandomCentroid());
        pixs.push_back(getRandomRgbPixel());
    }

    vector<double> answers;
    auto start1 = std::chrono::steady_clock::now();
    for(int i = 0; i < 100; i++) {
        answers.push_back(distance(cents.at(i), pixs.at(i)));
    }
    auto stop1 = std::chrono::steady_clock::now();

    vector<double> error;
    auto start2 = std::chrono::steady_clock::now();
    for(int i = 0; i < 100; i++) {
        error.push_back((distance(cents.at(i), pixs.at(i), c) - answers.at(i))/answers.at(i));
    }
    auto stop2 = std::chrono::steady_clock::now();

    double sum = 0;
    for(int i = 0; i < error.size(); i++) {
        sum += error.at(i);
    }
    cout << "Average error: " << sum / error.size() << endl;
    auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop1 - start1);
    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop2 - start2);
  
    cout << "Time taken by Formula: " << duration1.count() << " nanoseconds" << endl;
    cout << "Time taken by Tree: " << duration2.count() << " nanoseconds";
    return 0;
}

double distance(Centroid* c1, RgbPixel* p) {
    double r = 0;
    r += ((c1->r - p->r) * (c1->r - p->r));
    r += ((c1->g - p->g) * (c1->g - p->g));
    r += ((c1->b - p->b) * (c1->b - p->b));
    return sqrt(r);
}

double distance(Centroid* c1, RgbPixel* p, CART* c) {
    node* search = c->getRoot();
    vector<double> v;
    v.push_back(c1->r);
    v.push_back(c1->g);
    v.push_back(c1->b);
    v.push_back(p->r);
    v.push_back(p->g);
    v.push_back(p->b);
    while(search->index != -1) {
        if(v.at(search->index) <= search->threshold) {
            search = search->left;
        }
        else {
            search = search->right;
        }
    }
    return search->threshold;
}

Centroid* getRandomCentroid() {
    Centroid* c = new Centroid;
    c->r = rand() % 256;
    c->g = rand() % 256;
    c->b = rand() % 256;
    return c;
}

RgbPixel* getRandomRgbPixel() {
    RgbPixel* p = new RgbPixel;
    p->r = rand() % 256;
    p->g = rand() % 256;
    p->b = rand() % 256;
    return p;
}

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