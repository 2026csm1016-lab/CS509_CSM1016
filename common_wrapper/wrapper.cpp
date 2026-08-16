#include <iostream>
#include <cstdlib>

using namespace std;


// ==================== COMPILE ASSIGNMENT 1 ====================

void compileAssignment1()
{
    cout << "\nCompiling Assignment 1...\n";

    int result = system(
        "g++ -std=c++17 "
        "-I\"assignment_01/src\" "
        "assignment_01/wrapper/wrapper.cpp "
        "assignment_01/src/gemm.cpp "
        "assignment_01/src/CSR.cpp "
        "-o assignment1.exe"
    );

    if (result != 0)
    {
        cout << "\nError: Assignment 1 compilation failed.\n";
        return;
    }

    cout << "Assignment 1 compiled successfully.\n";

    cout << "\nStarting Assignment 1...\n\n";

    system(".\\assignment1.exe");
}


// ==================== COMPILE ASSIGNMENT 2 ====================

void compileAssignment2()
{
    cout << "\nCompiling Assignment 2...\n";

    int result = system(
        "g++ -std=c++17 "
        "assignment_02/driver/assignment2.cpp "
        "assignment_02/src/bellman_ford.cpp "
        "assignment_02/src/floyd_warshall.cpp "
        "assignment_01/src/CSR.cpp "
        "-o assignment2.exe"
    );

    if (result != 0)
    {
        cout << "\nError: Assignment 2 compilation failed.\n";
        return;
    }

    cout << "Assignment 2 compiled successfully.\n";

    cout << "\nStarting Assignment 2...\n\n";

    system(".\\assignment2.exe");
}


// ==================== COMPILE ASSIGNMENT 3 ====================

void compileAssignment3()
{
    cout << "\nCompiling Assignment 3...\n";

    int result = system(
        "g++ -std=c++17 "
        "assignment_03/driver/assignment3.cpp "
        "assignment_03/src/kruskal.cpp "
        "assignment_03/src/prim.cpp "
        "assignment_01/src/CSR.cpp "
        "-o assignment3.exe"
    );

    if (result != 0)
    {
        cout << "\nError: Assignment 3 compilation failed.\n";
        return;
    }

    cout << "Assignment 3 compiled successfully.\n";

    cout << "\nStarting Assignment 3...\n\n";

    system(".\\assignment3.exe");
}


// ==================== MAIN ====================

int main()
{
    int choice;

    while (true)
    {
        cout << "\n=====================================\n";
        cout << "       CS509 Laboratory Wrapper\n";
        cout << "=====================================\n";
        cout << "1. Assignment 1\n";
        cout << "2. Assignment 2\n";
        cout << "3. Assignment 3\n";
        cout << "0. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            compileAssignment1();
        }
        else if (choice == 2)
        {
            compileAssignment2();
        }
        else if (choice == 3)
        {
            compileAssignment3();
        }
        else if (choice == 0)
        {
            cout << "\nExiting Program...\n";
            break;
        }
        else
        {
            cout << "\nInvalid choice!\n";
        }
    }

    return 0;
}