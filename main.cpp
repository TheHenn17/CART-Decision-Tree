#include <chrono>
#include "Functions/Distance.h"
#include "Functions/Polynomial.h"
#include "Functions/ComplexPolynomial.h"
#include "Functions/Sigmoid.h"
#include "Functions/Tanh.h"

void generate() {
    srand(time(NULL));
    ofstream outFS;
    double total;
    outFS.open("Tree_Generation_Files/sigmoid.dat");
    for(double i = -6; i <=6; i = i + .02) {
        total = 1 / (1 + exp(-i));
        outFS << i << ", " << total << endl;
    }
    outFS.close();
}

void generate2() {
    srand(time(NULL));
    ofstream outFS;
    double random;
    outFS.open("Test_Files/sigmoidTests.dat");
    for(int i = 1; i <=100; i++) {
        random = (double)rand();
        random = -6 + random / ((double)RAND_MAX/12);
        outFS << random << endl;
    }
    outFS.close();
}

int main() {
    int input;
    unsigned depth;
    Function* function = 0;

    generate();
    //generate2();

    cout << "Welcome to Cool Tree Program\n\n";
    cout << "Please enter the function you would like to approximate:\n";
    cout << "\t1. Distance\n";
    cout << "\t2. Polynomial\n";
    cout << "\t3. Complex Polynomial\n";
    cout << "\t4. Sigmoid\n";
    cout << "\t5. Tanh\n";
    cin >> input;
    cout << "\nPlease enter the depth of the tree (make this dynamic later?): ";
    cin >> depth;
    
    cout << "\nCalculating Tree...\n";
    switch(input) {
        case 1:
            function = new Distance("Tree_Generation_Files/distance.dat", "Test_Files/distanceTests.dat", depth);
            break;
        case 2:
            function = new Polynomial("Tree_Generation_Files/polynomial.dat", "Test_Files/polynomialTests.dat", depth);
            break;
        case 3:
            function = new ComplexPolynomial("Tree_Generation_Files/complexPolynomial.dat", "Test_Files/complexPolynomialTests.dat", depth);
            break;
        case 4:
            function = new Sigmoid("Tree_Generation_Files/sigmoid.dat", "Test_Files/sigmoidTests.dat", depth);
            break;
        case 5:
            function = new Tanh("Tree_Generation_Files/tanh.dat", "Test_Files/tanhTests.dat", depth);
            break;
        default:
            cout << "Error: Invalid input\n";
            exit(1);
            break;
    }
    cout << "Done.\n";

    vector<double> computations;
    vector<double> approximations;

    while(true) {
        cout << "\nWhat would you like to do?\n";
        cout << "\t1. Print Tree\n";
        cout << "\t2. Find computation time\n";
        cout << "\t3. Find approximation time\n";
        cout << "\t4. Find computation time, approximation time, and percent error\n";
        cout << "\t5. Quit\n";
        cin >> input;
        cout << endl;

        switch(input) {
            case 1:
                function->printTree();
                break;
            case 2:
            {
                auto start = std::chrono::steady_clock::now();
                computations = function->compute();
                auto stop = std::chrono::steady_clock::now();
                auto computationDuration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                cout << "Time taken by computing: " << computationDuration.count() << " microseconds\n";
                break;
            }
            case 3:
            {
                auto start = std::chrono::steady_clock::now();
                approximations = function->approximate();
                auto stop = std::chrono::steady_clock::now();
                auto approximationDuration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                cout << "Time taken by approximating: " << approximationDuration.count() << " microseconds\n";
                break;
            }
            case 4:
            {
                auto start1 = std::chrono::steady_clock::now();
                computations = function->compute();
                auto stop1 = std::chrono::steady_clock::now();
                auto computationDuration = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);

                auto start2 = std::chrono::steady_clock::now();
                approximations = function->approximate();
                auto stop2 = std::chrono::steady_clock::now();
                auto approximationDuration = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

                cout << "Time taken by computing: " << computationDuration.count() << " microseconds\n";
                cout << "Time taken by approximating: " << approximationDuration.count() << " microseconds\n";
                double sum = 0;
                for(int i = 0; i < computations.size(); i++) {
                    sum += abs((approximations.at(i)-computations.at(i))/computations.at(i));
                }
                cout << "Average error: " << sum / computations.size() << endl;
                break;
            }
            case 5:
                exit(0);
                break;
            default:
                cout << "Error: Invalid input\n";
                exit(1);
                break;
        }
    }

    return 0;
}