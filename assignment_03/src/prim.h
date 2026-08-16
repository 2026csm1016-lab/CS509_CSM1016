#ifndef PRIM_H
#define PRIM_H

#include <vector>

using namespace std;

struct PrimEdge
{
    int u;
    int v;
    int weight;
};

struct PrimResult
{
    vector<PrimEdge> edges;
    long long totalWeight;
    bool connected;
};

PrimResult prim(
    int vertices,
    const vector<int>& rowPtr,
    const vector<int>& colIndex,
    const vector<int>& values
);

#endif