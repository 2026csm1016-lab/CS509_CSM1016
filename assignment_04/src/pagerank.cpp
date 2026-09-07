#include "pagerank.h"

#include <cmath>
#include <algorithm>

PageRankResult pageRank(
    int vertices,
    const std::vector<int>& rowPtr,
    const std::vector<int>& colIndex,
    double damping,
    double tolerance,
    int maxIterations)
{
    PageRankResult result;
    result.ranks.assign(vertices, 0.0);
    result.iterations = 0;
    result.converged = false;

    if (vertices <= 0)
    {
        result.converged = true;
        return result;
    }

    const double initialRank = 1.0 / vertices;
    result.ranks.assign(vertices, initialRank);

    std::vector<double> nextRanks(vertices, 0.0);

    for (int iteration = 1; iteration <= maxIterations; ++iteration)
    {
        // Base teleportation contribution.
        std::fill(nextRanks.begin(), nextRanks.end(),
                  (1.0 - damping) / vertices);

        double danglingRank = 0.0;

        // Distribute rank from each source vertex.
        for (int source = 0; source < vertices; ++source)
        {
            int outDegree = rowPtr[source + 1] - rowPtr[source];

            if (outDegree == 0)
            {
                danglingRank += result.ranks[source];
                continue;
            }

            double contribution = damping * result.ranks[source] / outDegree;
            for (int i = rowPtr[source]; i < rowPtr[source + 1]; ++i)
            {
                int destination = colIndex[i];
                if (destination >= 0 && destination < vertices)
                    nextRanks[destination] += contribution;
            }
        }

        // Treat a dangling vertex as linking uniformly to every vertex.
        double danglingContribution = damping * danglingRank / vertices;
        for (double& rank : nextRanks)
            rank += danglingContribution;

        double change = 0.0;
        for (int v = 0; v < vertices; ++v)
            change += std::abs(nextRanks[v] - result.ranks[v]);

        result.ranks.swap(nextRanks);
        result.iterations = iteration;

        if (change <= tolerance)
        {
            result.converged = true;
            break;
        }
    }

    return result;
}
