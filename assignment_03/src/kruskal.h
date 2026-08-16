#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>

using namespace std;

struct MSTEdge
{
    int u;
    int v;
    int weight;
};

struct MSTResult
{
    vector<MSTEdge> edges;
    long long totalWeight;
    bool connected;
};

MSTResult kruskal(
    int vertices,
    const vector<int>& rowPtr,
    const vector<int>& colIndex,
    const vector<int>& values
);

#endif