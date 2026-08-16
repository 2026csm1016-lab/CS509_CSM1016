#include "prim.h"

#include <queue>
#include <limits>

using namespace std;

PrimResult prim(
    int vertices,
    const vector<int>& rowPtr,
    const vector<int>& colIndex,
    const vector<int>& values
)
{
    const int INF = numeric_limits<int>::max();

    vector<int> key(vertices, INF);
    vector<int> parent(vertices, -1);
    vector<bool> inMST(vertices, false);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    PrimResult result;
    result.totalWeight = 0;
    result.connected = false;

    // Assignment requires starting Prim from vertex 0.
    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
        {
            continue;
        }

        inMST[u] = true;

        // Add the edge that connected u to the MST.
        if (parent[u] != -1)
        {
            result.edges.push_back({
                parent[u],
                u,
                key[u]
            });

            result.totalWeight += key[u];
        }

        // Examine all neighbours of u using CSR.
        for (int i = rowPtr[u];
             i < rowPtr[u + 1];
             i++)
        {
            int v = colIndex[i];
            int weight = values[i];

            if (!inMST[v] && weight < key[v])
            {
                key[v] = weight;
                parent[v] = u;

                pq.push({key[v], v});
            }
        }
    }

    if ((int)result.edges.size() == vertices - 1)
    {
        result.connected = true;
    }

    return result;
}