#include <fstream>
#include <iostream>

using namespace std;

void generateGraph(string filename, int vertices)
{
    ofstream out(filename);

    out << vertices << endl;

    for (int i = 0; i < vertices; i++)
    {
        if (i == vertices - 1)
        {
            out << 0 << endl;
        }
        else if (i == vertices - 2)
        {
            out << 1 << " " << i + 1 << endl;
        }
        else
        {
            out << 2 << " "
                << i + 1 << " "
                << i + 2 << endl;
        }
    }

    out.close();

    cout << filename << " generated.\n";
}

int main()
{
    generateGraph("input/graph_100.txt",100);
    generateGraph("input/graph_10000.txt",10000);
    generateGraph("input/graph_50000.txt",50000);
    generateGraph("input/graph_100000.txt",100000);

    return 0;
}