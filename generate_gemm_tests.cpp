#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateTestFile(string filename, int M, int K, int N)
{
    ofstream file(filename);

    if (!file)
    {
        cout << "Unable to create " << filename << endl;
        return;
    }

    file << M << " " << K << " " << N << "\n";

    // Matrix A
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < K; j++)
        {
            file << rand() % 10 + 1;

            if (j != K - 1)
                file << " ";
        }

        file << "\n";
    }

    // Matrix B
    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < N; j++)
        {
            file << rand() % 10 + 1;

            if (j != N - 1)
                file << " ";
        }

        file << "\n";
    }

    file.close();

    cout << filename << " created successfully.\n";
}

int main()
{
    srand(time(NULL));

    generateTestFile("input/gemm_test_02.txt", 10, 10, 10);
    generateTestFile("input/gemm_test_03.txt", 50, 50, 50);
    generateTestFile("input/gemm_test_04.txt", 100, 100, 100);
    generateTestFile("input/gemm_test_05.txt", 200, 200, 200);

    cout << "\nAll GEMM test cases generated successfully!\n";

    return 0;
}