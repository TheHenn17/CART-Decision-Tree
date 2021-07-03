#include <chrono>
#include "Functions/Distance.h"
#include "Functions/Polynomial.h"
#include "Functions/ComplexPolynomial.h"
#include "Functions/Sigmoid.h"
#include "Functions/Tanh.h"
#include "Functions/MatrixMult3x3.h"
#include "Functions/Determinant.h"
#include "Functions/Norm3x3.h"
#include "Functions/Norm2x2.h"

void generate() {
    srand(time(NULL));
    ofstream outFS;
    double random;
    outFS.open("Test_Files/norm2x2Tests.dat");
    for(int i = 1; i <=100; i++) {
        for(int j = 0; j < 3; j++) {
            random = rand() % 10 + 1;
            outFS << random << ", ";
        }
        //random = rand() % 500 + 1;
        random = rand() % 10 + 1;
        outFS << random << endl;
    }
    outFS.close();
}
void doubleGenerate() {
    srand(time(NULL));
    ofstream outFS;
    outFS.open("Test_Files/complexPolynomialTests.dat");
    for(int i = 1; i <=100; i++) {
        outFS << rand() % 500 + 1 << endl;
        outFS << rand() % 500 + 1 << endl;
    }
    outFS.close();
}

int main() {
    int input;
    Function* function = 0;

    generate();

    cout << "Welcome to Cool Tree Program\n\n";
    cout << "Please enter the function you would like to approximate:\n";
    cout << "\t1. Distance\n";
    cout << "\t2. Polynomial\n";
    cout << "\t3. Complex Polynomial\n";
    cout << "\t4. Sigmoid\n";
    cout << "\t5. Tanh\n";
    cout << "\t6. MatrixMult3x3\n";
    cout << "\t7. Determinant\n";
    cout << "\t8. Norm2x2\n";
    cout << "\t9. Norm3x3\n";
    cin >> input;
    
    cout << "\nCalculating Tree...\n";
    switch(input) {
        case 1:
            function = new Distance("Tree_Generation_Files/distance.dat", "Test_Files/distanceTests.dat", 10);
            break;
        case 2:
            function = new Polynomial("Tree_Generation_Files/polynomial.dat", "Test_Files/polynomialTests.dat", 10);
            break;
        case 3:
            function = new ComplexPolynomial("Tree_Generation_Files/complexPolynomial.dat", "Test_Files/complexPolynomialTests.dat", 10);
            break;
        case 4:
            function = new Sigmoid("Tree_Generation_Files/sigmoid.dat", "Test_Files/sigmoidTests.dat", 10);
            break;
        case 5:
            function = new Tanh("Tree_Generation_Files/tanh.dat", "Test_Files/tanhTests.dat", 10);
            break;
        case 6:
            function = new MatrixMult3x3("Tree_Generation_Files/matrixMult3x3.dat", "Test_Files/matrixMult3x3Tests.dat", 10);
            break;
        case 7:
            function = new Determinant("Tree_Generation_Files/determinant.dat", "Test_Files/determinantTests.dat", 10);
            break;
        case 8:
            function = new Norm2x2("Tree_Generation_Files/norm2x2.dat", "Test_Files/norm2x2Tests.dat", 10);
            break;
        case 9:
            function = new Norm3x3("Tree_Generation_Files/norm3x3.dat", "Test_Files/norm3x3Tests.dat", 10);
            break;
        default:
            cout << "Error: Invalid input\n";
            exit(1);
            break;
    }
    cout << "Done.\n";

    //function->createTreeFileFromTestFile("Tree_Generation_Files/determinant.dat");

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
                    //cout << approximations.at(i) << " " << computations.at(i) << endl;
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