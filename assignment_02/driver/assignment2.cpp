#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

#include "../../assignment_01/src/CSR.h"
#include "../src/bellman_ford.h"
#include "../src/floyd_warshall.h"

using namespace std;

const long long INF =
    2305843009213693951LL;


// ==================== BELLMAN-FORD ====================

bool readBellmanFordInput(
    const string& filename,
    int& vertices,
    int& edges,
    vector<vector<int>>& adjacencyList,
    vector<int>& weights,
    int& source
)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
        return false;

    inputFile >> vertices >> edges;

    adjacencyList.resize(vertices);
    weights.clear();

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
            weights.push_back(weight);
        }
    }

    string sourceWord;
    inputFile >> sourceWord >> source;

    inputFile.close();

    return true;
}


void runBellmanFord()
{
    int testChoice;
    string filename;

    cout << "\n========== Bellman-Ford ==========\n";
    cout << "1. bf_10.txt\n";
    cout << "2. bf_100.txt\n";
    cout << "3. bf_10000.txt\n";
    cout << "4. bf_50000.txt\n";
    cout << "5. bf_100000.txt\n";
    cout << "6. Back\n";

    cout << "\nEnter your choice: ";
    cin >> testChoice;

    if (testChoice == 6)
        return;

    if (testChoice == 1)
        filename = "assignment_02/tests/bf_10.txt";
    else if (testChoice == 2)
        filename = "assignment_02/tests/bf_100.txt";
    else if (testChoice == 3)
        filename = "assignment_02/tests/bf_10000.txt";
    else if (testChoice == 4)
        filename = "assignment_02/tests/bf_50000.txt";
    else if (testChoice == 5)
        filename = "assignment_02/tests/bf_100000.txt";
    else
    {
        cout << "\nInvalid Test Case!\n";
        return;
    }

    int vertices;
    int edges;
    int source;

    vector<vector<int>> adjacencyList;
    vector<int> weights;

    if (!readBellmanFordInput(
            filename,
            vertices,
            edges,
            adjacencyList,
            weights,
            source))
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

    BellmanFordResult result =
        bellmanFord(
            vertices,
            rowPtr,
            colIndex,
            weights,
            source
        );

    auto end =
        chrono::high_resolution_clock::now();

    chrono::duration<double, milli> executionTime =
        end - start;

    cout << "\nAlgorithm: Bellman-Ford\n";
    cout << "Source: " << source << "\n";

    if (result.negativeCycle)
    {
        cout << "Negative cycle: true\n";
    }
    else
    {
        cout << "Vertex Distance\n";

        for (int vertex = 0;
             vertex < vertices;
             vertex++)
        {
            cout << vertex << " ";

            if (result.distance[vertex] >= INF)
                cout << "INF";
            else
                cout << result.distance[vertex];

            cout << "\n";
        }

        cout << "Negative cycle: none\n";
    }

    cout << "Execution time: "
         << executionTime.count()
         << " ms\n";
}
        
 // ==================== FLOYD-WARSHALL ====================

bool readFloydWarshallInput(
    const string& filename,
    int& vertices,
    vector<vector<long long>>& matrix
)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
        return false;

    inputFile >> vertices;

    matrix.assign(
        vertices,
        vector<long long>(vertices)
    );

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            string value;

            inputFile >> value;

            if (value == "INF")
                matrix[i][j] = INF;
            else
                matrix[i][j] = stoll(value);
        }
    }

    inputFile.close();

    return true;
}
bool crossCheck(
    const string& bfFile,
    const string& fwFile
)
{
    int vertices;
    int edges;
    int ignoredSource;

    vector<vector<int>> adjacencyList;
    vector<int> weights;

    if (!readBellmanFordInput(
            bfFile,
            vertices,
            edges,
            adjacencyList,
            weights,
            ignoredSource))
    {
        cout << "Error: Unable to open BF file.\n";
        return false;
    }

    int fwVertices;
    vector<vector<long long>> matrix;

    if (!readFloydWarshallInput(
            fwFile,
            fwVertices,
            matrix))
    {
        cout << "Error: Unable to open FW file.\n";
        return false;
    }

    if (vertices != fwVertices)
    {
        cout << "Cross-check failed: vertex counts differ.\n";
        return false;
    }

    vector<int> rowPtr;
    vector<int> colIndex;

    convertToCSR(
        adjacencyList,
        rowPtr,
        colIndex
    );

    FloydWarshallResult fwResult =
        floydWarshall(matrix);

    if (fwResult.negativeCycle)
    {
        cout << "Cross-check skipped: negative cycle detected.\n";
        return false;
    }

    for (int source = 0; source < vertices; source++)
    {
        BellmanFordResult bfResult =
            bellmanFord(
                vertices,
                rowPtr,
                colIndex,
                weights,
                source
            );

        if (bfResult.negativeCycle)
        {
            cout << "Cross-check failed: BF detected negative cycle.\n";
            return false;
        }

        for (int destination = 0;
             destination < vertices;
             destination++)
        {
            long long bfDistance =
                bfResult.distance[destination];

            long long fwDistance =
                fwResult.distance[source][destination];

            bool bfInf = (bfDistance >= INF);
            bool fwInf = (fwDistance >= INF);

            if (bfInf != fwInf ||
                (!bfInf && bfDistance != fwDistance))
            {
                cout << "Cross-check FAILED\n";
                cout << "Source: " << source << "\n";
                cout << "Destination: " << destination << "\n";
                cout << "Bellman-Ford: " << bfDistance << "\n";
                cout << "Floyd-Warshall: " << fwDistance << "\n";

                return false;
            }
        }
    }

    cout << "Cross-check PASSED for all "
         << vertices
         << " source vertices.\n";

    return true;
}

void runFloydWarshall()
{
    int testChoice;
    string filename;

    cout << "\n========== Floyd-Warshall ==========\n";
    cout << "1. fw_10.txt\n";
    cout << "2. fw_100.txt\n";
    cout << "3. fw_500.txt\n";
    cout << "4. fw_1000.txt\n";
    cout << "5. fw_2000.txt\n";
    cout << "6. Back\n";

    cout << "\nEnter your choice: ";
    cin >> testChoice;

    if (testChoice == 6)
        return;

    if (testChoice == 1)
        filename = "assignment_02/tests/fw_10.txt";
    else if (testChoice == 2)
        filename = "assignment_02/tests/fw_100.txt";
    else if (testChoice == 3)
        filename = "assignment_02/tests/fw_500.txt";
    else if (testChoice == 4)
        filename = "assignment_02/tests/fw_1000.txt";
    else if (testChoice == 5)
        filename = "assignment_02/tests/fw_2000.txt";
    else
    {
        cout << "\nInvalid Test Case!\n";
        return;
    }

    int vertices;
    vector<vector<long long>> matrix;

    if (!readFloydWarshallInput(
            filename,
            vertices,
            matrix))
    {
        cout << "\nError: Unable to open input file.\n";
        return;
    }

    auto start =
        chrono::high_resolution_clock::now();

    FloydWarshallResult result =
        floydWarshall(matrix);

    auto end =
        chrono::high_resolution_clock::now();

    chrono::duration<double, milli> executionTime =
        end - start;

    cout << "\nAlgorithm: Floyd-Warshall\n";

    if (result.negativeCycle)
    {
        cout << "Negative cycle: true\n";
    }
    else
    {
        cout << "Distance matrix:\n";

if (vertices <= 100)
{
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (result.distance[i][j] >= INF)
                cout << "INF";
            else
                cout << result.distance[i][j];

            if (j != vertices - 1)
                cout << " ";
        }

        cout << "\n";
    }
}
else
{
    cout << "Distance matrix omitted for large graph.\n";
}

        cout << "Negative cycle: none\n";
    }

 cout << "Execution time: "
     << executionTime.count()
     << " ms\n";

if (testChoice == 1)
{
    crossCheck(
        "assignment_02/tests/bf_10.txt",
        "assignment_02/tests/fw_10.txt"
    );
}
else if (testChoice == 2)
{
    crossCheck(
        "assignment_02/tests/bf_100.txt",
        "assignment_02/tests/fw_100.txt"
    );
}
}

// ==================== MAIN DRIVER ====================

int main()
{
    int choice;

    do
    {
        cout << "\n=====================================\n";
        cout << "       CS509 Assignment 2\n";
        cout << "=====================================\n";
        cout << "1. Bellman-Ford\n";
        cout << "2. Floyd-Warshall\n";
        cout << "3. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                runBellmanFord();
                break;

            case 2:
                runFloydWarshall();
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