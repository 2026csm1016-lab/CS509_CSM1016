#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../../assignment_01/src/CSR.h"
#include "../src/vertex_coloring.h"
#include "../src/pagerank.h"

using namespace std;

// Assignment 4 graph input is V E followed by vertex, degree, neighbours.
// This parser prepares the adjacency list; CSR conversion is reused from Assignment 1.
bool readGraphA4(
    const string& filename,
    int& vertices,
    int& edges,
    vector<vector<int>>& adjacencyList)
{
    ifstream inputFile(filename);
    if (!inputFile.is_open())
        return false;

    if (!(inputFile >> vertices >> edges) || vertices <= 0 || edges < 0)
        return false;

    adjacencyList.assign(vertices, {});

    for (int i = 0; i < vertices; ++i)
    {
        int vertex, degree;
        if (!(inputFile >> vertex >> degree) ||
            vertex < 0 || vertex >= vertices || degree < 0)
            return false;

        adjacencyList[vertex].reserve(degree);

        for (int j = 0; j < degree; ++j)
        {
            int neighbour;
            if (!(inputFile >> neighbour) ||
                neighbour < 0 || neighbour >= vertices || neighbour == vertex)
                return false;
            adjacencyList[vertex].push_back(neighbour);
        }
    }

    return true;
}

bool readPageRankInput(
    const string& filename,
    int& vertices,
    int& edges,
    vector<vector<int>>& adjacencyList,
    double& damping,
    double& tolerance,
    int& maxIterations)
{
    if (!readGraphA4(filename, vertices, edges, adjacencyList))
        return false;

    // Re-open because readGraphA4 intentionally reads only the graph portion.
    ifstream inputFile(filename);
    if (!inputFile.is_open())
        return false;

    int dummyV, dummyE;
    inputFile >> dummyV >> dummyE;
    for (int i = 0; i < vertices; ++i)
    {
        int vertex, degree;
        inputFile >> vertex >> degree;
        for (int j = 0; j < degree; ++j)
        {
            int neighbour;
            inputFile >> neighbour;
        }
    }

    string label;
    if (!(inputFile >> label >> damping) || label != "DAMPING")
        return false;
    if (!(inputFile >> label >> tolerance) || label != "TOLERANCE")
        return false;
    if (!(inputFile >> label >> maxIterations) || label != "MAX_ITERATIONS")
        return false;

    return damping > 0.0 && damping < 1.0 &&
           tolerance > 0.0 && maxIterations > 0;
}

void runVertexColoring(const string& filename)
{
    int vertices, edges;
    vector<vector<int>> adjacencyList;

    if (!readGraphA4(filename, vertices, edges, adjacencyList))
    {
        cout << "\nError: Invalid or missing Vertex Coloring input file.\n";
        return;
    }

    vector<int> rowPtr, colIndex;
    convertToCSR(adjacencyList, rowPtr, colIndex);

    auto start = chrono::high_resolution_clock::now();
    ColoringResult result = greedyVertexColoring(vertices, rowPtr, colIndex);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> executionTime = end - start;

    cout << "\nAlgorithm: Greedy Vertex Coloring\n";
    if (vertices <= 100)
    {
        cout << "Vertex colors:\n";
        for (int v = 0; v < vertices; ++v)
            cout << v << " " << result.colors[v] << "\n";
    }
    else
    {
        cout << "Vertex colors omitted for large graph.\n";
    }

    cout << "Colors used: " << result.colorsUsed << "\n";
    cout << "Valid: " << (result.valid ? "true" : "false") << "\n";
    cout << fixed << setprecision(3);
    cout << "Execution time: " << executionTime.count() << " ms\n";
}

void runPageRank(const string& filename)
{
    int vertices, edges, maxIterations;
    double damping, tolerance;
    vector<vector<int>> adjacencyList;

    if (!readPageRankInput(
            filename, vertices, edges, adjacencyList,
            damping, tolerance, maxIterations))
    {
        cout << "\nError: Invalid or missing PageRank input file.\n";
        return;
    }

    vector<int> rowPtr, colIndex;
    convertToCSR(adjacencyList, rowPtr, colIndex);

    auto start = chrono::high_resolution_clock::now();
    PageRankResult result = pageRank(
        vertices, rowPtr, colIndex,
        damping, tolerance, maxIterations);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> executionTime = end - start;

    cout << "\nAlgorithm: PageRank\n";
    cout << fixed << setprecision(6);
    cout << "Damping: " << damping << "\n";

    if (vertices <= 100)
    {
        cout << "Vertex ranks:\n";
        for (int v = 0; v < vertices; ++v)
            cout << v << " " << result.ranks[v] << "\n";
    }
    else
    {
        int top = min(vertices, 10);
        vector<int> order(vertices);
        for (int v = 0; v < vertices; ++v)
            order[v] = v;
        partial_sort(order.begin(), order.begin() + top, order.end(),
                     [&](int a, int b)
                     {
                         if (result.ranks[a] != result.ranks[b])
                             return result.ranks[a] > result.ranks[b];
                         return a < b;
                     });
        cout << "Top 10 vertices:\n";
        for (int i = 0; i < top; ++i)
            cout << order[i] << " " << result.ranks[order[i]] << "\n";
    }

    double sum = 0.0;
    for (double rank : result.ranks)
        sum += rank;

    cout << "Sum of ranks: " << sum << "\n";
    cout << "Iterations: " << result.iterations << "\n";
    cout << "Converged: " << (result.converged ? "true" : "false") << "\n";
    cout << "Execution time: " << executionTime.count() << " ms\n";
}

string chooseColorFile()
{
    int choice;
    cout << "\n========== Vertex Coloring ==========\n"
         << "1. color_10.txt\n"
         << "2. color_100.txt\n"
         << "3. color_10000.txt\n"
         << "4. color_50000.txt\n"
         << "5. color_100000.txt\n"
         << "6. Back\n\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) return "assignment_04/tests/color_10.txt";
    if (choice == 2) return "assignment_04/tests/color_100.txt";
    if (choice == 3) return "assignment_04/tests/color_10000.txt";
    if (choice == 4) return "assignment_04/tests/color_50000.txt";
    if (choice == 5) return "assignment_04/tests/color_100000.txt";
    return "";
}

string choosePageRankFile()
{
    int choice;
    cout << "\n========== PageRank ==========\n"
         << "1. pagerank_10.txt\n"
         << "2. pagerank_100.txt\n"
         << "3. pagerank_1000.txt\n"
         << "4. pagerank_10000.txt\n"
         << "5. pagerank_50000.txt\n"
         << "6. Back\n\nEnter your choice: ";
    cin >> choice;

    if (choice == 1) return "assignment_04/tests/pagerank_10.txt";
    if (choice == 2) return "assignment_04/tests/pagerank_100.txt";
    if (choice == 3) return "assignment_04/tests/pagerank_1000.txt";
    if (choice == 4) return "assignment_04/tests/pagerank_10000.txt";
    if (choice == 5) return "assignment_04/tests/pagerank_50000.txt";
    return "";
}

int main()
{
    while (true)
    {
        int choice;
        cout << "\n=====================================\n"
             << "          Assignment 4\n"
             << "=====================================\n"
             << "1. Vertex Coloring\n"
             << "2. PageRank\n"
             << "0. Exit\n\n"
             << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string filename = chooseColorFile();
            if (!filename.empty()) runVertexColoring(filename);
        }
        else if (choice == 2)
        {
            string filename = choosePageRankFile();
            if (!filename.empty()) runPageRank(filename);
        }
        else if (choice == 0)
        {
            cout << "\nExiting Assignment 4...\n";
            break;
        }
        else
        {
            cout << "\nInvalid choice!\n";
        }
    }

    return 0;
}
