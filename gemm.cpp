#include "gemm.h"
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

bool readMatrices(
    const string& filename,
    vector<vector<int>>& firstMatrix,
    vector<vector<int>>& secondMatrix,
    int& rowsA,
    int& commonDimension,
    int& colsB)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        return false;
    }

    inputFile >> rowsA >> commonDimension >> colsB;

    firstMatrix.resize(rowsA, vector<int>(commonDimension));
    secondMatrix.resize(commonDimension, vector<int>(colsB));

    for (int row = 0; row < rowsA; row++)
    {
        for (int column = 0; column < commonDimension; column++)
        {
            inputFile >> firstMatrix[row][column];
        }
    }

    for (int row = 0; row < commonDimension; row++)
    {
        for (int column = 0; column < colsB; column++)
        {
            inputFile >> secondMatrix[row][column];
        }
    }

    inputFile.close();

    return true;
}
void printMatrix(const vector<vector<int>>& matrix)
{
    for (size_t row = 0; row < matrix.size(); row++)
    {
        for (size_t column = 0; column < matrix[row].size(); column++)
        {
            cout << matrix[row][column] << " ";
        }

        cout << endl;
    }
}
vector<vector<int>> simpleGEMM(
    const vector<vector<int>>& firstMatrix,
    const vector<vector<int>>& secondMatrix)
{
    int rows = firstMatrix.size();
    int commonDimension = firstMatrix[0].size();
    int columns = secondMatrix[0].size();

    vector<vector<int>> result(
        rows,
        vector<int>(columns, 0)
    );

    for (int row = 0; row < rows; row++)
        {
            for (int column = 0; column < columns; column++)
            {
                 int sum = 0;

                 for (int index = 0; index < commonDimension; index++)
                {
                sum += firstMatrix[row][index] * secondMatrix[index][column];
                }

             result[row][column] = sum;
            }
        }
    return result;
}

vector<vector<int>> blockingGEMM(
    const vector<vector<int>>& firstMatrix,
    const vector<vector<int>>& secondMatrix,
    int blockSize)
{
    int rows = firstMatrix.size();
    int commonDimension = firstMatrix[0].size();
    int columns = secondMatrix[0].size();

    vector<vector<int>> result(
        rows,
        vector<int>(columns, 0)
    );
    
    for (int blockRow = 0; blockRow < rows; blockRow += blockSize)
    {
        for (int blockColumn = 0; blockColumn < columns; blockColumn += blockSize)
        {
            for (int blockIndex = 0; blockIndex < commonDimension; blockIndex += blockSize)
            { for (int row = blockRow;
     row < min(blockRow + blockSize, rows);
     row++)
{
    for (int column = blockColumn;
         column < min(blockColumn + blockSize, columns);
         column++)
    {
        for (int index = blockIndex;
             index < min(blockIndex + blockSize, commonDimension);
             index++)
        {
            result[row][column] +=
                firstMatrix[row][index] *
                secondMatrix[index][column];
        }
    }
}

            }
        }
    }
return result;
}