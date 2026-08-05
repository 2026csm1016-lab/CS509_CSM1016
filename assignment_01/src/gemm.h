#ifndef GEMM_H
#define GEMM_H

#include <vector>
#include <string>

using namespace std;

// Reads matrices from input file
bool readMatrices(
    const string& filename,
    vector<vector<int>>& A,
    vector<vector<int>>& B,
    int& M,
    int& K,
    int& N
);

// Prints a matrix
void printMatrix(const vector<vector<int>>& matrix);

// Simple GEMM
vector<vector<int>> simpleGEMM(
    const vector<vector<int>>& A,
    const vector<vector<int>>& B
);

// Blocking GEMM
vector<vector<int>> blockingGEMM(
    const vector<vector<int>>& A,
    const vector<vector<int>>& B,
    int blockSize
);

#endif