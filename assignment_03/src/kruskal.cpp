#include "kruskal.h"

#include <algorithm>
#include <numeric>

using namespace std;


// ==================== DSU ====================

class DSU
{
private:
    vector<int> parent;
    vector<int> rankValue;

public:

    DSU(int n)
    {
        parent.resize(n);
        rankValue.assign(n, 0);

        iota(parent.begin(), parent.end(), 0);
    }

    int find(int vertex)
    {
        if (parent[vertex] != vertex)
        {
            parent[vertex] = find(parent[vertex]);
        }

        return parent[vertex];
    }

    bool unite(int a, int b)
    {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB)
        {
            return false;
        }

        if (rankValue[rootA] < rankValue[rootB])
        {
            parent[rootA] = rootB;
        }
        else if (rankValue[rootA] > rankValue[rootB])
        {
            parent[rootB] = rootA;
        }
        else
        {
            parent[rootB] = rootA;
            rankValue[rootA]++;
        }

        return true;
    }
};


// ==================== KRUSKAL ====================

MSTResult kruskal(
    int vertices,
    const vector<int>& rowPtr,
    const vector<int>& colIndex,
    const vector<int>& values
)
{
    vector<MSTEdge> edges;

    // Convert CSR representation into an edge list.
    // Since the graph is undirected, each edge appears twice.
    // We keep only one copy using u < v.

    for (int u = 0; u < vertices; u++)
    {
        for (int i = rowPtr[u];
             i < rowPtr[u + 1];
             i++)
        {
            int v = colIndex[i];
            int weight = values[i];

            if (u < v)
            {
                edges.push_back({u, v, weight});
            }
        }
    }

    // Sort edges by increasing weight.

    sort(
        edges.begin(),
        edges.end(),
        [](const MSTEdge& a, const MSTEdge& b)
        {
            return a.weight < b.weight;
        }
    );

    DSU dsu(vertices);

    MSTResult result;
    result.totalWeight = 0;
    result.connected = false;

    // Process edges from smallest weight to largest.

    for (const MSTEdge& edge : edges)
    {
        // If the endpoints are in different components,
        // adding this edge will not create a cycle.

        if (dsu.unite(edge.u, edge.v))
        {
            result.edges.push_back(edge);
            result.totalWeight += edge.weight;

            // An MST always contains V - 1 edges.

            if ((int)result.edges.size() == vertices - 1)
            {
                result.connected = true;
                break;
            }
        }
    }

    return result;
}