#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include <vector>

using namespace std;

struct FloydWarshallResult
{
    vector<vector<long long>> distance;
    bool negativeCycle;
};

FloydWarshallResult floydWarshall(
    const vector<vector<long long>>& matrix
);

#endif