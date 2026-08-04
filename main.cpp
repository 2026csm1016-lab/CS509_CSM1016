#include "gemm.h"
#include "csr.h"
#include <chrono>
#include <iostream>

using namespace std;
void runGEMM();
void runCSR();
int main()
{
    int choice;

    do
    {
        cout << "\n=====================================\n";
        cout << "       CS509 Assignment 1\n";
        cout << "=====================================\n";
        cout << "1. GEMM (Simple + Blocking)\n";
        cout << "2. CSR\n";
        cout << "3. BFS\n";
        cout << "4. DFS\n";
        cout << "5. SSSP\n";
        cout << "0. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

    switch (choice)
    {
    case 1:
        runGEMM();
        break;

    case 2:
        runCSR();
        break;

    case 3:
        cout << "\nBFS module not implemented yet.\n";
        break;

    case 4:
        cout << "\nDFS module not implemented yet.\n";
        break;

    case 5:
        cout << "\nSSSP module not implemented yet.\n";
        break;

    case 0:
        cout << "\nExiting Program...\n";
        break;

    default:
        cout << "\nInvalid Choice!\n";
    }
    } while (choice != 0);

    return 0;
}
void runGEMM()
{
    int testChoice;
    string filename;

    cout << "\n========== GEMM ==========\n";
    cout << "1. gemm_test_01.txt\n";
    cout << "2. gemm_test_02.txt\n";
    cout << "3. gemm_test_03.txt\n";
    cout << "4. gemm_test_04.txt\n";
    cout << "5. gemm_test_05.txt\n";
    cout << "0. Back\n";

    cout << "\nEnter your choice: ";
    cin >> testChoice;

    if (testChoice == 0)
        return;

    if (testChoice == 1)
        filename = "input/gemm_test_01.txt";
    else if (testChoice == 2)
        filename = "input/gemm_test_02.txt";
    else if (testChoice == 3)
        filename = "input/gemm_test_03.txt";
    else if (testChoice == 4)
        filename = "input/gemm_test_04.txt";
    else if (testChoice == 5)
        filename = "input/gemm_test_05.txt";
    else
    {
        cout << "\nInvalid Test Case!\n";
        return;
    }

    vector<vector<int>> matrixA;
    vector<vector<int>> matrixB;

    int rowsA;
    int commonDimension;
    int colsB;

    if (!readMatrices(filename,
                      matrixA,
                      matrixB,
                      rowsA,
                      commonDimension,
                      colsB))
    {
        cout << "Error: Unable to open input file." << endl;
        return;
    }

   /*/ cout << "\nMatrix A:\n";
    printMatrix(matrixA);

    cout << "\nMatrix B:\n";
    printMatrix(matrixB);*/
    cout << "\nMatrix A:\n";

if (rowsA <= 10 && commonDimension <= 10)
{
    printMatrix(matrixA);
}
else
{
    cout << "Matrix A is too large to display.\n";
}

cout << "\nMatrix B:\n";

if (commonDimension <= 10 && colsB <= 10)
{
    printMatrix(matrixB);
}
else
{
    cout << "Matrix B is too large to display.\n";
} // till here

    auto startSimple = chrono::high_resolution_clock::now();

    vector<vector<int>> simpleResult = simpleGEMM(matrixA, matrixB);

    auto endSimple = chrono::high_resolution_clock::now();

    auto startBlock = chrono::high_resolution_clock::now();

    vector<vector<int>> blockResult = blockingGEMM(matrixA, matrixB, 16);

    auto endBlock = chrono::high_resolution_clock::now();

    //cout << "\nAlgorithm: GEMM Simple\n";
    //printMatrix(simpleResult);
    cout << "\nAlgorithm: GEMM Simple\n";

if (rowsA <= 10 && colsB <= 10)
{
    printMatrix(simpleResult);
}
else
{
    cout << "Result matrix is too large to display.\n";
} //till here
    chrono::duration<double, milli> simpleTime = endSimple - startSimple;

    cout << "\nExecution Time: "
         << simpleTime.count()
         << " ms\n";

    //cout << "\nAlgorithm: GEMM Blocking\n";
    //printMatrix(blockResult);
    cout << "\nAlgorithm: GEMM Blocking\n";

if (rowsA <= 10 && colsB <= 10)
{
    printMatrix(blockResult);
}
else
{
    cout << "Result matrix is too large to display.\n";
}//till here

    chrono::duration<double, milli> blockTime = endBlock - startBlock;

    cout << "\nExecution Time: "
         << blockTime.count()
         << " ms\n";
}
void runCSR()
{
    int testChoice;
    string filename;

    cout << "\n========== CSR ==========\n";
    cout << "1. graph_10.txt\n";
    cout << "2. graph_100.txt\n";
    cout << "3. graph_10000.txt\n";
    cout << "4. graph_50000.txt\n";
    cout << "5. graph_100000.txt\n";
    cout << "0. Back\n";

    cout << "\nEnter your choice: ";
    cin >> testChoice;

    if (testChoice == 0)
        return;

    if (testChoice == 1)
        filename = "input/graph_10.txt";
    else if (testChoice == 2)
        filename = "input/graph_100.txt";
    else if (testChoice == 3)
        filename = "input/graph_10000.txt";
    else if (testChoice == 4)
        filename = "input/graph_50000.txt";
    else if (testChoice == 5)
        filename = "input/graph_100000.txt";
    else
    {
        cout << "\nInvalid Test Case!\n";
        return;
    }

    vector<vector<int>> adjacencyList;
    vector<int> rowPtr;
    vector<int> colIndex;

    int vertices;

    if (!readGraph(filename,
                   adjacencyList,
                   vertices))
    {
        cout << "\nError: Unable to open input file.\n";
        return;
    }

    cout << "\nNumber of Vertices : " << vertices << endl;

    if (vertices <= 10)
    {
        printAdjacencyList(adjacencyList);
    }
    else
    {
        cout << "\nGraph is too large to display.\n";
    }

    convertToCSR(adjacencyList,
                 rowPtr,
                 colIndex);

    if (vertices <= 10)
    {
        printCSR(rowPtr,
                 colIndex);
    }
    else
    {
        cout << "\nCSR conversion completed successfully.\n";
    }
}