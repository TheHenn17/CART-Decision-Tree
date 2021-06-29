#include <chrono>
#include "Functions/Distance.h"
#include "Functions/Polynomial.h"
#include "Functions/ComplexPolynomial.h"
#include "Functions/Sigmoid.h"
#include "Functions/Tanh.h"
#include "Functions/MatrixMult3x3.h"

void generate() {
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

//dont delete
vector<vector<double> > gm() {
    srand(time(NULL));
    vector<vector<double> > ret;
    vector<double> r1;
    r1.push_back(rand()%51);
    r1.push_back(rand()%51);
    r1.push_back(rand()%51);
    ret.push_back(r1);
    vector<double> r2;
    r2.push_back(rand()%51);
    r2.push_back(rand()%51);
    r2.push_back(rand()%51);
    ret.push_back(r2);
    vector<double> r3;
    r3.push_back(rand()%51);
    r3.push_back(rand()%51);
    r3.push_back(rand()%51);
    ret.push_back(r3);
    return ret;
}

//dont delete
void generate3MTF() {
    ofstream outFS;
    vector<vector<double> > mat1;
    vector<vector<double> > mat2;
    //double ans;
    outFS.open("Test_Files/matrixMult3x3Tests.dat");
    //outFS.open("Tree_Generation_Files/matrixMult3x3.dat");
    //outFS << "Ax1, Ax2, Ax3, B1x, B2x, B3x, Cxx\nContinous, Continous, Continous, Continous, Continous, Continous, Continous\n";
    for(int i = 1; i <=50; i++) {
        mat1 = gm();
        mat2 = gm();

        outFS << mat1.at(0).at(0) << ", " << mat1.at(0).at(1) << ", " << mat1.at(0).at(2) << ", ";
        outFS << mat2.at(0).at(0) << ", " << mat2.at(1).at(0) << ", " << mat2.at(2).at(0) << ", ";
        //ans = (mat1.at(0).at(0)*mat2.at(0).at(0)) + (mat1.at(0).at(1)*mat2.at(1).at(0)) + (mat1.at(0).at(2)*mat2.at(2).at(0));
        //outFS << ans << endl;
        outFS << endl;

        outFS << mat1.at(0).at(0) << ", " << mat1.at(0).at(1) << ", " << mat1.at(0).at(2) << ", ";
        outFS << mat2.at(0).at(1) << ", " << mat2.at(1).at(1) << ", " << mat2.at(2).at(1) << ", ";
        //ans = (mat1.at(0).at(0)*mat2.at(0).at(1)) + (mat1.at(0).at(1)*mat2.at(1).at(1)) + (mat1.at(0).at(2)*mat2.at(2).at(1));
        //outFS << ans << endl;
        outFS << endl;
        
        outFS << mat1.at(0).at(0) << ", " << mat1.at(0).at(1) << ", " << mat1.at(0).at(2) << ", ";
        outFS << mat2.at(0).at(2) << ", " << mat2.at(1).at(2) << ", " << mat2.at(2).at(2) << ", ";
        //ans = (mat1.at(0).at(0)*mat2.at(0).at(2)) + (mat1.at(0).at(1)*mat2.at(1).at(2)) + (mat1.at(0).at(2)*mat2.at(2).at(2));
        //outFS << ans << endl;
        outFS << endl;
        
        outFS << mat1.at(1).at(0) << ", " << mat1.at(1).at(1) << ", " << mat1.at(1).at(2) << ", ";
        outFS << mat2.at(0).at(0) << ", " << mat2.at(1).at(0) << ", " << mat2.at(2).at(0) << ", ";
        //ans = (mat1.at(1).at(0)*mat2.at(0).at(0)) + (mat1.at(1).at(1)*mat2.at(1).at(0)) + (mat1.at(1).at(2)*mat2.at(2).at(0));
        //outFS << ans << endl;
        outFS << endl;

        outFS << mat1.at(1).at(0) << ", " << mat1.at(1).at(1) << ", " << mat1.at(1).at(2) << ", ";
        outFS << mat2.at(0).at(1) << ", " << mat2.at(1).at(1) << ", " << mat2.at(2).at(1) << ", ";
        //ans = (mat1.at(1).at(0)*mat2.at(0).at(1)) + (mat1.at(1).at(1)*mat2.at(1).at(1)) + (mat1.at(1).at(2)*mat2.at(2).at(1));
        //outFS << ans << endl;
        outFS << endl;
        
        outFS << mat1.at(1).at(0) << ", " << mat1.at(1).at(1) << ", " << mat1.at(1).at(2) << ", ";
        outFS << mat2.at(0).at(2) << ", " << mat2.at(1).at(2) << ", " << mat2.at(2).at(2) << ", ";
        //ans = (mat1.at(1).at(0)*mat2.at(0).at(2)) + (mat1.at(1).at(1)*mat2.at(1).at(2)) + (mat1.at(1).at(2)*mat2.at(2).at(2));
        //outFS << ans << endl;
        outFS << endl;
        
        outFS << mat1.at(2).at(0) << ", " << mat1.at(2).at(1) << ", " << mat1.at(2).at(2) << ", ";
        outFS << mat2.at(0).at(0) << ", " << mat2.at(1).at(0) << ", " << mat2.at(2).at(0) << ", ";
        //ans = (mat1.at(2).at(0)*mat2.at(0).at(0)) + (mat1.at(2).at(1)*mat2.at(1).at(0)) + (mat1.at(2).at(2)*mat2.at(2).at(0));
        //outFS << ans << endl;
        outFS << endl;

        outFS << mat1.at(2).at(0) << ", " << mat1.at(2).at(1) << ", " << mat1.at(2).at(2) << ", ";
        outFS << mat2.at(0).at(1) << ", " << mat2.at(1).at(1) << ", " << mat2.at(2).at(1) << ", ";
        //ans = (mat1.at(2).at(0)*mat2.at(0).at(1)) + (mat1.at(2).at(1)*mat2.at(1).at(1)) + (mat1.at(2).at(2)*mat2.at(2).at(1));
        //outFS << ans << endl;
        outFS << endl;
        
        outFS << mat1.at(2).at(0) << ", " << mat1.at(2).at(1) << ", " << mat1.at(2).at(2) << ", ";
        outFS << mat2.at(0).at(2) << ", " << mat2.at(1).at(2) << ", " << mat2.at(2).at(2) << ", ";
        //ans = (mat1.at(2).at(0)*mat2.at(0).at(2)) + (mat1.at(2).at(1)*mat2.at(1).at(2)) + (mat1.at(2).at(2)*mat2.at(2).at(2));
        //outFS << ans << endl;
        outFS << endl;
    }
    outFS.close();
}

int main() {
    int input;
    unsigned depth;
    Function* function = 0;

    //generate();
    generate3MTF();

    cout << "Welcome to Cool Tree Program\n\n";
    cout << "Please enter the function you would like to approximate:\n";
    cout << "\t1. Distance\n";
    cout << "\t2. Polynomial\n";
    cout << "\t3. Complex Polynomial\n";
    cout << "\t4. Sigmoid\n";
    cout << "\t5. Tanh\n";
    cout << "\t6. MatrixMult3x3\n";
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
        case 6:
            function = new MatrixMult3x3("Tree_Generation_Files/matrixMult3x3.dat", "Test_Files/matrixMult3x3Tests.dat", depth);
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