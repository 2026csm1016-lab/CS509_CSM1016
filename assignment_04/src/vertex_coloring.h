#ifndef VERTEX_COLORING_H
#define VERTEX_COLORING_H

#include <vector>

struct ColoringResult
{
    std::vector<int> colors;
    int colorsUsed;
    bool valid;
};

ColoringResult greedyVertexColoring(
    int vertices,
    const std::vector<int>& rowPtr,
    const std::vector<int>& colIndex
);

#endif
