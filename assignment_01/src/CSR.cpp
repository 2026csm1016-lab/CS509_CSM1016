#include "CSR.h"

#include <fstream>
#include <iostream>

using namespace std;
bool readGraph(
    const string& filename,
    vector<vector<int>>& adjacencyList,
    int& vertices
)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        return false;
    }

    inputFile >> vertices;

    adjacencyList.resize(vertices);

    for (int vertex = 0; vertex < vertices; vertex++)
    {
        int neighbours;
        inputFile >> neighbours;

        for (int i = 0; i < neighbours; i++)
        {
            int adjacentVertex;
            inputFile >> adjacentVertex;

            adjacencyList[vertex].push_back(adjacentVertex);
        }
    }

    inputFile.close();

    return true;
}
void convertToCSR(
    const vector<vector<int>>& adjacencyList,
    vector<int>& rowPtr,
    vector<int>& colIndex
)
{
    rowPtr.clear();
    colIndex.clear();

    rowPtr.push_back(0);

    for (size_t vertex = 0; vertex < adjacencyList.size(); vertex++)
    {
        for (size_t neighbour = 0;
             neighbour < adjacencyList[vertex].size();
             neighbour++)
        {
            colIndex.push_back(
                adjacencyList[vertex][neighbour]
            );
        }

        rowPtr.push_back(colIndex.size());
    }
}
void printAdjacencyList(
    const vector<vector<int>>& adjacencyList
)
{
    cout << "\nAdjacency List:\n";

    for (size_t vertex = 0; vertex < adjacencyList.size(); vertex++)
    {
        cout << vertex << " : ";

        for (size_t neighbour = 0;
             neighbour < adjacencyList[vertex].size();
             neighbour++)
        {
            cout << adjacencyList[vertex][neighbour] << " ";
        }

        cout << endl;
    }
}
void printCSR(
    const vector<int>& rowPtr,
    const vector<int>& colIndex
)
{
    cout << "\nCSR Representation\n";

    cout << "\nrowPtr : ";

    for (size_t i = 0; i < rowPtr.size(); i++)
    {
        cout << rowPtr[i] << " ";
    }

    cout << "\ncolIndex : ";

    for (size_t i = 0; i < colIndex.size(); i++)
    {
        cout << colIndex[i] << " ";
    }

    cout << endl;
}