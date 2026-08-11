#include "bellman_ford.h"

#include <limits>

using namespace std;

BellmanFordResult bellmanFord(
    int vertices,
    const vector<int>& rowPtr,
    const vector<int>& colIndex,
    const vector<int>& values,
    int source
)
{
    const long long INF =
        numeric_limits<long long>::max() / 4;

    vector<long long> distance(vertices, INF);

    distance[source] = 0;

    // Relax all edges V-1 times
    for (int iteration = 0;
         iteration < vertices - 1;
         iteration++)
    {
        bool changed = false;

        for (int u = 0; u < vertices; u++)
        {
            if (distance[u] == INF)
                continue;

            for (int edge = rowPtr[u];
                 edge < rowPtr[u + 1];
                 edge++)
            {
                int v = colIndex[edge];
                int weight = values[edge];

                if (distance[u] + weight < distance[v])
                {
                    distance[v] =
                        distance[u] + weight;

                    changed = true;
                }
            }
        }

        if (!changed)
            break;
    }

    // Extra pass for negative-cycle detection
    bool negativeCycle = false;

    for (int u = 0; u < vertices; u++)
    {
        if (distance[u] == INF)
            continue;

        for (int edge = rowPtr[u];
             edge < rowPtr[u + 1];
             edge++)
        {
            int v = colIndex[edge];
            int weight = values[edge];

            if (distance[u] + weight < distance[v])
            {
                negativeCycle = true;
                break;
            }
        }

        if (negativeCycle)
            break;
    }

    return {distance, negativeCycle};
}