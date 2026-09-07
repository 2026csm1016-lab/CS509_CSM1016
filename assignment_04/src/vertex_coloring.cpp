#include "vertex_coloring.h"

#include <algorithm>
#include <numeric>

ColoringResult greedyVertexColoring(
    int vertices,
    const std::vector<int>& rowPtr,
    const std::vector<int>& colIndex)
{
    ColoringResult result;
    result.colors.assign(vertices, -1);
    result.colorsUsed = 0;
    result.valid = true;

    // Welsh-Powell: process vertices in non-increasing degree order.
    std::vector<int> order(vertices);
    std::iota(order.begin(), order.end(), 0);

    std::sort(order.begin(), order.end(), [&](int a, int b)
    {
        int degreeA = rowPtr[a + 1] - rowPtr[a];
        int degreeB = rowPtr[b + 1] - rowPtr[b];
        if (degreeA != degreeB)
            return degreeA > degreeB;
        return a < b;
    });

    std::vector<int> usedColor(vertices, -1);

    for (int vertex : order)
    {
        // Mark colors already used by colored neighbours.
        for (int i = rowPtr[vertex]; i < rowPtr[vertex + 1]; ++i)
        {
            int neighbour = colIndex[i];
            if (neighbour >= 0 && neighbour < vertices && result.colors[neighbour] >= 0)
                usedColor[result.colors[neighbour]] = vertex;
        }

        int color = 0;
        while (color < vertices && usedColor[color] == vertex)
            ++color;

        result.colors[vertex] = color;
        result.colorsUsed = std::max(result.colorsUsed, color + 1);
    }

    // Verify correctness.
    for (int vertex = 0; vertex < vertices && result.valid; ++vertex)
    {
        for (int i = rowPtr[vertex]; i < rowPtr[vertex + 1]; ++i)
        {
            int neighbour = colIndex[i];
            if (neighbour >= 0 && neighbour < vertices &&
                result.colors[vertex] == result.colors[neighbour])
            {
                result.valid = false;
                break;
            }
        }
    }

    return result;
}
