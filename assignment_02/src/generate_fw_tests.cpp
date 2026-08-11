#include <fstream>
#include <iostream>

using namespace std;

void generateGraph(const string& filename, int vertices)
{
    ofstream out(filename);

    out << vertices << "\n";

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (i == j)
                out << "0";
            else if (j == i + 1)
                out << "1";
            else if (j == i + 2)
                out << "2";
            else
                out << "INF";

            if (j != vertices - 1)
                out << " ";
        }

        out << "\n";
    }

    out.close();

    cout << filename << " generated.\n";
}

int main()
{
    generateGraph("assignment_02/tests/fw_500.txt", 500);
    generateGraph("assignment_02/tests/fw_1000.txt", 1000);
    generateGraph("assignment_02/tests/fw_2000.txt", 2000);

    return 0;
}