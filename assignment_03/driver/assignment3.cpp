#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

#include "../../assignment_01/src/CSR.h"
#include "../src/kruskal.h"
#include "../src/prim.h"

using namespace std;


// ==================== READ MST INPUT ====================

bool readMSTInput(
    const string& filename,
    int& vertices,
    int& edges,
    vector<vector<int>>& adjacencyList,
    vector<int>& values
)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
        return false;

    inputFile >> vertices >> edges;

    adjacencyList.resize(vertices);
    values.clear();

    for (int u = 0; u < vertices; u++)
    {
        int vertex;
        int degree;

        inputFile >> vertex >> degree;

        for (int i = 0; i < degree; i++)
        {
            int neighbour;
            int weight;

            inputFile >> neighbour >> weight;

            adjacencyList[vertex].push_back(neighbour);
            values.push_back(weight);
        }
    }

    inputFile.close();

    return true;
}


// ==================== KRUSKAL ====================

void runKruskal()
{
    int testChoice;
    string filename;

    cout << "\n========== Kruskal's MST ==========\n";
    cout << "1. mst_10.txt\n";
    cout << "2. mst_100.txt\n";
    cout << "3. mst_10000.txt\n";
    cout << "4. mst_50000.txt\n";
    cout << "5. mst_100000.txt\n";
    cout << "6. Back\n";

    cout << "\nEnter your choice: ";
    cin >> testChoice;

    if (testChoice == 6)
        return;

    if (testChoice == 1)
        filename = "assignment_03/tests/mst_10.txt";
    else if (testChoice == 2)
        filename = "assignment_03/tests/mst_100.txt";
    else if (testChoice == 3)
        filename = "assignment_03/tests/mst_10000.txt";
    else if (testChoice == 4)
        filename = "assignment_03/tests/mst_50000.txt";
    else if (testChoice == 5)
        filename = "assignment_03/tests/mst_100000.txt";
    else
    {
        cout << "\nInvalid Test Case!\n";
        return;
    }

    int vertices;
    int edges;

    vector<vector<int>> adjacencyList;
    vector<int> values;

    if (!readMSTInput(
            filename,
            vertices,
            edges,
            adjacencyList,
            values))
    {
        cout << "\nError: Unable to open input file.\n";
        return;
    }

    // Reuse CSR conversion from Assignment 1.

    vector<int> rowPtr;
    vector<int> colIndex;

    convertToCSR(
        adjacencyList,
        rowPtr,
        colIndex
    );


    auto start =
        chrono::high_resolution_clock::now();

    MSTResult result =
        kruskal(
            vertices,
            rowPtr,
            colIndex,
            values
        );

    auto end =
        chrono::high_resolution_clock::now();

    chrono::duration<double, milli> executionTime =
        end - start;


    cout << "\nAlgorithm: Kruskal's MST\n";

    cout << "MST edges:\n";

    if (vertices <= 100)
    {
        for (const MSTEdge& edge : result.edges)
        {
            cout << edge.u << " "
                 << edge.v << " "
                 << edge.weight << "\n";
        }
    }
    else
    {
        cout << "MST edges omitted for large graph.\n";
    }

    if (result.connected)
    {
        cout << "Total MST weight: "
             << result.totalWeight
             << "\n";
    }
    else
    {
        cout << "Graph is not connected. MST does not exist.\n";
    }

    cout << "Execution time: "
         << executionTime.count()
         << " ms\n";
}


// ==================== PRIM ====================

void runPrim()
{
    int testChoice;
    string filename;

    cout << "\n========== Prim's MST ==========\n";
    cout << "1. mst_10.txt\n";
    cout << "2. mst_100.txt\n";
    cout << "3. mst_10000.txt\n";
    cout << "4. mst_50000.txt\n";
    cout << "5. mst_100000.txt\n";
    cout << "6. Back\n";

    cout << "\nEnter your choice: ";
    cin >> testChoice;

    if (testChoice == 6)
        return;

    if (testChoice == 1)
        filename = "assignment_03/tests/mst_10.txt";
    else if (testChoice == 2)
        filename = "assignment_03/tests/mst_100.txt";
    else if (testChoice == 3)
        filename = "assignment_03/tests/mst_10000.txt";
    else if (testChoice == 4)
        filename = "assignment_03/tests/mst_50000.txt";
    else if (testChoice == 5)
        filename = "assignment_03/tests/mst_100000.txt";
    else
    {
        cout << "\nInvalid Test Case!\n";
        return;
    }

    int vertices;
    int edges;

    vector<vector<int>> adjacencyList;
    vector<int> values;

    if (!readMSTInput(
            filename,
            vertices,
            edges,
            adjacencyList,
            values))
    {
        cout << "\nError: Unable to open input file.\n";
        return;
    }

    // Reuse CSR conversion from Assignment 1.

    vector<int> rowPtr;
    vector<int> colIndex;

    convertToCSR(
        adjacencyList,
        rowPtr,
        colIndex
    );


    auto start =
        chrono::high_resolution_clock::now();

    PrimResult result =
        prim(
            vertices,
            rowPtr,
            colIndex,
            values
        );

    auto end =
        chrono::high_resolution_clock::now();

    chrono::duration<double, milli> executionTime =
        end - start;


    cout << "\nAlgorithm: Prim's MST\n";

    cout << "MST edges:\n";

    if (vertices <= 100)
    {
        for (const PrimEdge& edge : result.edges)
        {
            cout << edge.u << " "
                 << edge.v << " "
                 << edge.weight << "\n";
        }
    }
    else
    {
        cout << "MST edges omitted for large graph.\n";
    }

    if (result.connected)
    {
        cout << "Total MST weight: "
             << result.totalWeight
             << "\n";
    }
    else
    {
        cout << "Graph is not connected. MST does not exist.\n";
    }

    cout << "Execution time: "
         << executionTime.count()
         << " ms\n";
}


// ==================== MAIN DRIVER ====================

int main()
{
    int choice;

    do
    {
        cout << "\n=====================================\n";
        cout << "       CS509 Assignment 3\n";
        cout << "=====================================\n";
        cout << "1. Kruskal's MST\n";
        cout << "2. Prim's MST\n";
        cout << "3. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                runKruskal();
                break;

            case 2:
                runPrim();
                break;

            case 3:
                cout << "\nExiting Program...\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while (choice != 3);

    return 0;
}