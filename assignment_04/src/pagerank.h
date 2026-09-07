#ifndef PAGERANK_H
#define PAGERANK_H

#include <vector>

struct PageRankResult
{
    std::vector<double> ranks;
    int iterations;
    bool converged;
};

PageRankResult pageRank(
    int vertices,
    const std::vector<int>& rowPtr,
    const std::vector<int>& colIndex,
    double damping,
    double tolerance,
    int maxIterations
);

#endif
