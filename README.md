# CS509 Assignment 1 

## Team Member

- CSM1016

---

# Assignment 1

## Assignment

Implementation of:

- GEMM (Simple)
- GEMM (Blocking)
- CSR (Compressed Sparse Row)

---

## Folder Structure

```text
assignment_01/
│
├── src/
│   ├── CSR.cpp
│   ├── CSR.h
│   ├── gemm.cpp
│   ├── gemm.h
│   ├── generate_graph_tests.cpp
│   └── generate_gemm_tests.cpp
│
├── tests/
│   ├── graph_10.txt
│   ├── graph_100.txt
│   ├── graph_10000.txt
│   ├── graph_50000.txt
│   ├── graph_100000.txt
│   ├── gemm_test_01.txt
│   ├── gemm_test_02.txt
│   ├── gemm_test_03.txt
│   ├── gemm_test_04.txt
│   └── gemm_test_05.txt
│
└── wrapper/
    └── wrapper.cpp
```

---

## Compilation

Compile manually:

```bash
g++ -std=c++17 -I"assignment_01/src" assignment_01/wrapper/wrapper.cpp assignment_01/src/gemm.cpp assignment_01/src/CSR.cpp -o wrapper
```

---

## Execution

On Linux:

```bash
./wrapper
```

On Windows:

```bash
wrapper.exe
```

---

## Algorithms

### GEMM (Simple)

Standard triple nested-loop matrix multiplication.

**Time Complexity:** O(M × K × N)

### GEMM (Blocking)

Matrix multiplication using blocking to improve cache utilization.

**Time Complexity:** O(M × K × N)

**Block Size:** 16

### CSR

Converts an adjacency-list graph into Compressed Sparse Row format.

**Time Complexity:** O(V + E)

---

## Timing

Execution time includes only the algorithm execution.

The following are excluded:

- File reading
- Input parsing
- Output printing

---

## GEMM Results

| Test File | Input Size | Expected Output | Actual Output | Simple Time | Blocking Time | Block Size | Status |
|---|---|---|---|---|---|---:|---|
| gemm_test_01.txt | 2×3 and 3×2 | Correct Result Matrix | Correct | Measured | Measured | 16 | Pass |
| gemm_test_02.txt | Larger Matrix | Correct Result Matrix | Correct | Measured | Measured | 16 | Pass |
| gemm_test_03.txt | Large Matrix | Correct Result Matrix | Correct | Measured | Measured | 16 | Pass |
| gemm_test_04.txt | Large Matrix | Correct Result Matrix | Correct | Measured | Measured | 16 | Pass |
| gemm_test_05.txt | Largest Matrix | Correct Result Matrix | Correct | Measured | Measured | 16 | Pass |

---

## CSR Results

| Test File | Vertices | Input Type | Output | Status |
|---|---:|---|---|---|
| graph_10.txt | 10 | Adjacency List | CSR Generated | Pass |
| graph_100.txt | 100 | Adjacency List | CSR Generated | Pass |
| graph_10000.txt | 10000 | Adjacency List | CSR Generated | Pass |
| graph_50000.txt | 50000 | Adjacency List | CSR Generated | Pass |
| graph_100000.txt | 100000 | Adjacency List | CSR Generated | Pass |

---

## Sample Output

### GEMM

```text
Algorithm: GEMM Simple

58 64
139 154

Execution Time: <value> ms

Algorithm: GEMM Blocking

58 64
139 154

Execution Time: <value> ms
```

### CSR

```text
Algorithm: CSR

Vertices: 5

rowPtr:
0 2 4 5 6 6

colIndex:
1 2 0 3 4 4
```

---

# Assignment 2

## Algorithms

Implementation of:

- Bellman-Ford
- Floyd-Warshall

Bellman-Ford uses the CSR representation from Assignment 1.

Floyd-Warshall uses a dense adjacency matrix directly.

---

## Algorithm Complexity

### Bellman-Ford

**Time Complexity:** O(V × E)

**Space Complexity:** O(V + E)

### Floyd-Warshall

**Time Complexity:** O(V³)

**Space Complexity:** O(V²)

---

## Test Cases

### Bellman-Ford

| Test File | Vertices | Edges | Source | Negative Cycle |
|---|---:|---:|---:|---|
| bf_10.txt | 10 | 14 | 0 | No |
| bf_100.txt | 100 | 197 | 0 | No |
| bf_10000.txt | 10000 | 19997 | 0 | No |
| bf_50000.txt | 50000 | 99997 | 0 | No |
| bf_100000.txt | 100000 | 199997 | 0 | No |

### Floyd-Warshall

| Test File | Vertices | Edges | Source | Negative Cycle |
|---|---:|---:|---|---|
| fw_10.txt | 10 | 14 | N/A | No |
| fw_100.txt | 100 | 197 | N/A | No |
| fw_500.txt | 500 | 997 | N/A | No |
| fw_1000.txt | 1000 | 1997 | N/A | No |
| fw_2000.txt | 2000 | 3997 | N/A | No |

---

## Execution Time Results

| Algorithm | Test File | Vertices | Edges | Source | Negative Cycle | Expected Output | Actual Output | Execution Time | Status |
|---|---|---:|---:|---|---|---|---|---:|---|
| Bellman-Ford | bf_10.txt | 10 | 14 | 0 | No | Correct shortest distances | Correct | 0 ms | Pass |
| Bellman-Ford | bf_100.txt | 100 | 197 | 0 | No | Correct shortest distances | Correct | 0 ms | Pass |
| Bellman-Ford | bf_10000.txt | 10000 | 19997 | 0 | No | Correct shortest distances | Correct | 0 ms | Pass |
| Bellman-Ford | bf_50000.txt | 50000 | 99997 | 0 | No | Correct shortest distances | Correct | 4.671 ms | Pass |
| Bellman-Ford | bf_100000.txt | 100000 | 199997 | 0 | No | Correct shortest distances | Correct | 9.224 ms | Pass |
| Floyd-Warshall | fw_10.txt | 10 | 14 | N/A | No | Correct distance matrix | Correct | 0 ms | Pass |
| Floyd-Warshall | fw_100.txt | 100 | 197 | N/A | No | Correct distance matrix | Correct | 0 ms | Pass |
| Floyd-Warshall | fw_500.txt | 500 | 997 | N/A | No | Correct distance matrix | Correct | 310.523 ms | Pass |
| Floyd-Warshall | fw_1000.txt | 1000 | 1997 | N/A | No | Correct distance matrix | Correct | 2493.64 ms | Pass |
| Floyd-Warshall | fw_2000.txt | 2000 | 3997 | N/A | No | Correct distance matrix | Correct | 21912.6 ms | Pass |

---

## Correctness Verification

For the graph sizes where both algorithms are required, Bellman-Ford was run from every vertex and the resulting distances were compared with the corresponding rows of the Floyd-Warshall distance matrix.

| Vertices | Result |
|---:|---|
| 10 | Cross-check Passed |
| 100 | Cross-check Passed |

---

## Negative Weight Test

A separate negative-weight test was performed to verify that Bellman-Ford correctly handles negative edge weights.

### Observed Result

```text
Algorithm: Bellman-Ford
Source: 0

Vertex Distance
0 0
1 5
2 7
3 13
4 22

Negative cycle: none
```

The test completed successfully and no negative cycle was detected.

---

## Timing Method

For Bellman-Ford, CSR conversion is performed before the timer starts.

For Floyd-Warshall, the input matrix is loaded before the timer starts.

Therefore, the reported execution time measures only the algorithm execution.

The following are excluded:

- File reading
- Input parsing
- CSR conversion
- Matrix construction
- Output printing

---

## Output Handling

For smaller Floyd-Warshall graphs, the complete distance matrix is displayed.

For larger graphs, the distance matrix is omitted from the console output to avoid excessive output. The algorithm execution and negative-cycle check are still performed.

---

## Conclusion

Both Bellman-Ford and Floyd-Warshall were successfully implemented and tested on all required graph sizes.

The correctness checks passed, including the cross-check between Bellman-Ford and Floyd-Warshall for the 10-vertex and 100-vertex graphs. Negative-cycle detection was also verified, and a separate negative-edge test confirmed that Bellman-Ford correctly handles negative edge weights.

The recorded execution times demonstrate the expected performance difference between the two algorithms, with Floyd-Warshall becoming significantly more expensive as the number of vertices increases because of its O(V³) time complexity.

# Assignment 3

## Algorithms

Implementation of:

- Kruskal's Minimum Spanning Tree
- Prim's Minimum Spanning Tree

Both algorithms use the same weighted undirected graph input and operate on the CSR representation after conversion.

---

## Algorithm Complexity

### Kruskal

**Time Complexity:** O(E log E)

**Space Complexity:** O(V + E)

### Prim

Using a min-priority queue:

**Time Complexity:** O(E log V)

**Space Complexity:** O(V + E)

---

## Test Cases

| Test File | Vertices | Edges |
|---|---:|---:|
| mst_10.txt | 10 | 15 |
| mst_100.txt | 100 | 300 |
| mst_10000.txt | 10000 | 30000 |
| mst_50000.txt | 50000 | 150000 |
| mst_100000.txt | 100000 | 300000 |

---

## Execution Time Results

| Algorithm | Test File | Vertices | Edges | Expected MST Weight | Actual MST Weight | Execution Time | Status |
|---|---|---:|---:|---:|---:|---:|---|
| Kruskal | mst_10.txt | 10 | 15 | 26 | 26 | 0 ms | Pass |
| Kruskal | mst_100.txt | 100 | 300 | 1937 | 1937 | 0 ms | Pass |
| Kruskal | mst_10000.txt | 10000 | 30000 | 202020 | 202020 | 9.278 ms | Pass |
| Kruskal | mst_50000.txt | 50000 | 150000 | 1012305 | 1012305 | 46.603 ms | Pass |
| Kruskal | mst_100000.txt | 100000 | 300000 | 2035020 | 2035020 | 102.698 ms | Pass |
| Prim | mst_10.txt | 10 | 15 | 26 | 26 | 0 ms | Pass |
| Prim | mst_100.txt | 100 | 300 | 1937 | 1937 | 0 ms | Pass |
| Prim | mst_10000.txt | 10000 | 30000 | 202020 | 202020 | 18.156 ms | Pass |
| Prim | mst_50000.txt | 50000 | 150000 | 1012305 | 1012305 | 104.015 ms | Pass |
| Prim | mst_100000.txt | 100000 | 300000 | 2035020 | 2035020 | 222.009 ms | Pass |

---

## Correctness Verification

Both Kruskal's and Prim's algorithms were executed on the same graph inputs.

The total MST weight produced by both algorithms was identical for every test case.

| Test File | Kruskal MST Weight | Prim MST Weight | Result |
|---|---:|---:|---|
| mst_10.txt | 26 | 26 | Pass |
| mst_100.txt | 1937 | 1937 | Pass |
| mst_10000.txt | 202020 | 202020 | Pass |
| mst_50000.txt | 1012305 | 1012305 | Pass |
| mst_100000.txt | 2035020 | 2035020 | Pass |

Different MST edge sets may occur when multiple valid MSTs exist, but the total MST weight remains the same.

---

## Timing Method

The following operations are performed before the timer starts:

- File reading
- Input parsing
- Adjacency-list construction
- Conversion from adjacency list to CSR

The timer measures only the execution of the selected MST algorithm.

Output printing is also outside the timed region.

---

## Output Handling

For smaller graphs, the selected MST edges are displayed.

For larger graphs, the MST edges are omitted from the console output to avoid excessive output. The total MST weight and execution time are still displayed.

---

## Sample Output

### Kruskal

```text
Algorithm: Kruskal's MST
MST edges:
4 5 1
1 2 2
5 6 2
8 9 2
2 3 3
7 8 3
0 1 4
4 7 4
2 5 5

Total MST weight: 26
Execution time: 0 ms
Prim
Algorithm: Prim's MST
MST edges:
0 1 4
1 2 2
2 3 3
2 5 5
5 4 1
5 6 2
4 7 4
7 8 3
8 9 2


Total MST weight: 26
Execution time: 0 ms
Compilation

Compile manually from the repository root:

g++ assignment_03/driver/assignment3.cpp assignment_03/src/kruskal.cpp assignment_03/src/prim.cpp assignment_01/src/CSR.cpp -o assignment3.exe
Execution

On Windows:

.\assignment3.exe

The driver provides a menu for selecting:

Kruskal's MST
Prim's MST
Exit

Each algorithm provides a menu for selecting the required MST test file.

Conclusion

Both Kruskal's and Prim's Minimum Spanning Tree algorithms were successfully implemented and tested using the same weighted undirected graph inputs.

All five required graph sizes produced the expected MST weights, and the total MST weights obtained from Kruskal's and Prim's algorithms matched for every test case.

The execution times were recorded separately for both algorithms, with file reading, input parsing, CSR conversion, and output printing excluded from the timed region.