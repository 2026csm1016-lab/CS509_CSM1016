#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <random>

using namespace std;

struct Edge
{
    int u;
    int v;
    int weight;
};

int main()
{
    int V, E;
    string filename;

    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter output file name: ";
    cin >> filename;

    if (V <= 0 || E < V - 1)
    {
        cout << "Invalid graph size.\n";
        return 1;
    }

   if ((long long)E > (long long)V * (V - 1) / 2)
    {
        cout << "Too many edges for a simple undirected graph.\n";
        return 1;
    }

    vector<Edge> edges;
    set<pair<int, int>> used;

    mt19937 rng(42);
    uniform_int_distribution<int> vertexDist(0, V - 1);
    uniform_int_distribution<int> weightDist(1, 100);

    // First create a spanning tree so the graph is connected.

    for (int v = 1; v < V; v++)
    {
        int u = vertexDist(rng) % v;

        int a = min(u, v);
        int b = max(u, v);

        used.insert({a, b});

        edges.push_back({a, b, weightDist(rng)});
    }

    // Add remaining random edges.

    while ((int)edges.size() < E)
    {
        int u = vertexDist(rng);
        int v = vertexDist(rng);

        if (u == v)
        {
            continue;
        }

        int a = min(u, v);
        int b = max(u, v);

        if (used.count({a, b}))
        {
            continue;
        }

        used.insert({a, b});

        edges.push_back({a, b, weightDist(rng)});
    }

    // Build undirected adjacency lists.

    vector<vector<pair<int, int>>> adjacency(V);

    for (const Edge& edge : edges)
    {
        adjacency[edge.u].push_back({edge.v, edge.weight});
        adjacency[edge.v].push_back({edge.u, edge.weight});
    }

    ofstream output(filename);

    if (!output.is_open())
    {
        cout << "Error: Could not create output file.\n";
        return 1;
    }

    output << V << " " << E << "\n";

    for (int u = 0; u < V; u++)
    {
        output << u << " " << adjacency[u].size();

        for (const auto& neighbour : adjacency[u])
        {
            output << " "
                   << neighbour.first
                   << " "
                   << neighbour.second;
        }

        output << "\n";
    }

    output.close();

    cout << "Generated " << filename << "\n";
    cout << "Vertices: " << V << "\n";
    cout << "Edges: " << E << "\n";

    return 0;
}