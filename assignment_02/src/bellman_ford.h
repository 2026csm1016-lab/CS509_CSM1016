#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <vector>

using namespace std;

struct BellmanFordResult
{
    vector<long long> distance;
    bool negativeCycle;
};

BellmanFordResult bellmanFord(
    int vertices,
    const vector<int>& rowPtr,
    const vector<int>& colIndex,
    const vector<int>& values,
    int source
);

#endif