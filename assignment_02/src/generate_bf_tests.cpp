#include <fstream>
#include <iostream>

using namespace std;

void generateGraph(const string& filename, int vertices)
{
    ofstream out(filename);

    int edges = 0;

    for (int i = 0; i < vertices; i++)
    {
        if (i == vertices - 1)
            edges += 0;
        else if (i == vertices - 2)
            edges += 1;
        else
            edges += 2;
    }

    out << vertices << " " << edges << "\n";

    for (int i = 0; i < vertices; i++)
    {
        if (i == vertices - 1)
        {
            out << i << " 0\n";
        }
        else if (i == vertices - 2)
        {
            out << i << " 1 " << i + 1 << " 1\n";
        }
        else
        {
            out << i << " 2 "
                << i + 1 << " 1 "
                << i + 2 << " 2\n";
        }
    }

    out << "SOURCE 0\n";

    out.close();

    cout << filename << " generated.\n";
}

int main()
{
    generateGraph(
        "assignment_02/tests/bf_10000.txt",
        10000
    );

    generateGraph(
        "assignment_02/tests/bf_50000.txt",
        50000
    );

    generateGraph(
        "assignment_02/tests/bf_100000.txt",
        100000
    );

    return 0;
}