#ifndef CSR_H
#define CSR_H

#include <vector>
#include <string>

using namespace std;

// Reads graph from adjacency-list file
bool readGraph(
    const string& filename,
    vector<vector<int>>& adjacencyList,
    int& vertices
);

// Converts adjacency list to CSR format
void convertToCSR(
    const vector<vector<int>>& adjacencyList,
    vector<int>& rowPtr,
    vector<int>& colIndex
);

// Prints adjacency list
void printAdjacencyList(
    const vector<vector<int>>& adjacencyList
);

// Prints CSR arrays
void printCSR(
    const vector<int>& rowPtr,
    const vector<int>& colIndex
);

#endif