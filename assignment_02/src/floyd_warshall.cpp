#include "floyd_warshall.h"

#include <limits>

using namespace std;

FloydWarshallResult floydWarshall(
    const vector<vector<long long>>& matrix
)
{
    const long long INF =
        numeric_limits<long long>::max() / 4;

    int vertices = static_cast<int>(matrix.size());

    vector<vector<long long>> distance = matrix;

    for (int k = 0; k < vertices; k++)
    {
        for (int i = 0; i < vertices; i++)
        {
            if (distance[i][k] == INF)
                continue;

            for (int j = 0; j < vertices; j++)
            {
                if (distance[k][j] == INF)
                    continue;

                if (distance[i][k] + distance[k][j]
                    < distance[i][j])
                {
                    distance[i][j] =
                        distance[i][k] + distance[k][j];
                }
            }
        }
    }

    bool negativeCycle = false;

    for (int i = 0; i < vertices; i++)
    {
        if (distance[i][i] < 0)
        {
            negativeCycle = true;
            break;
        }
    }

    return {distance, negativeCycle};
}