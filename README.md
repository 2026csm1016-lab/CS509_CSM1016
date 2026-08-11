# CS509 Assignment 1

## Team Member

- CSM1016

---

# Assignment

Implementation of:

- GEMM (Simple)
- GEMM (Blocking)
- CSR (Compressed Sparse Row)

---

# Folder Structure

```
assignment_01/
│
├── src/
│   ├── csr.cpp
│   ├── csr.h
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

README.md
makefile
```

---

# Compilation

Compile manually

```bash
g++ -std=c++17 -I"assignment_01/src" assignment_01/wrapper/wrapper.cpp assignment_01/src/gemm.cpp assignment_01/src/csr.cpp -o wrapper
```

Or using the Makefile

```bash
mingw32-make
```

---

# Execution

```bash
./wrapper
```

or on Windows

```bash
wrapper.exe
```

---

# Algorithms

## GEMM (Simple)

Standard triple nested-loop matrix multiplication.

Time Complexity:

```
O(M × K × N)
```

---

## GEMM (Blocking)

Matrix multiplication using blocking to improve cache utilization.

Time Complexity:

```
O(M × K × N)
```

Block Size:

```
16
```

---

## CSR

Converts an adjacency-list graph into Compressed Sparse Row format.

Time Complexity:

```
O(V + E)
```

---

# Timing

Execution time includes only the algorithm execution.

The following are excluded:

- File reading
- Input parsing
- Output printing

---

# GEMM Results

| Test File | Input Size | Expected Output | Actual Output | Simple Time | Blocking Time | Block Size | Status |
|-----------|------------|-----------------|---------------|-------------|---------------|------------|--------|
| gemm_test_01.txt | 2×3 and 3×2 | Correct Result Matrix | Correct | Measured | Measured | 16 | Pass |
| gemm_test_02.txt | Larger Matrix | Correct Result Matrix | Correct | Measured | Measured | 16 | Pass |
| gemm_test_03.txt | Large Matrix | Correct Result Matrix | Correct | Measured | Measured | 16 | Pass |
| gemm_test_04.txt | Large Matrix | Correct Result Matrix | Correct | Measured | Measured | 16 | Pass |
| gemm_test_05.txt | Largest Matrix | Correct Result Matrix | Correct | Measured | Measured | 16 | Pass |

---

# CSR Results

| Test File | Vertices | Input Type | Output | Status |
|-----------|---------:|------------|--------|--------|
| graph_10.txt | 10 | Adjacency List | CSR Generated | Pass |
| graph_100.txt | 100 | Adjacency List | CSR Generated | Pass |
| graph_10000.txt | 10000 | Adjacency List | CSR Generated | Pass |
| graph_50000.txt | 50000 | Adjacency List | CSR Generated | Pass |
| graph_100000.txt | 100000 | Adjacency List | CSR Generated | Pass |

---

# Sample Output

## GEMM

```
Algorithm: GEMM Simple

58 64
139 154

Execution Time: <value> ms

Algorithm: GEMM Blocking

58 64
139 154

Execution Time: <value> ms
```

## CSR

```
Algorithm: CSR

Vertices: 5

rowPtr:
0 2 4 5 6 6

colIndex:
1 2 0 3 4 4
```
---

# CS509 Assignment 2

## Algorithms

- Bellman-Ford
- Floyd-Warshall

Bellman-Ford uses the CSR representation from Assignment 1.

Floyd-Warshall uses a dense adjacency matrix directly.

---

## Complexity

### Bellman-Ford

Time Complexity: O(V × E)

Space Complexity: O(V + E)

### Floyd-Warshall

Time Complexity: O(V³)

Space Complexity: O(V²)

---

## Assignment 2 Test Files

### Bellman-Ford

| Test File | Vertices | Edges | Source | Negative Cycle | Status |
|---|---:|---:|---:|---|---|
| bf_10.txt | 10 | 17 | 0 | No | Pass |
| bf_100.txt | 100 | 197 | 0 | No | Pass |
| bf_10000.txt | 10000 | 19997 | 0 | No | Pass |
| bf_50000.txt | 50000 | 99997 | 0 | No | Pass |
| bf_100000.txt | 100000 | 199997 | 0 | No | Pass |

### Floyd-Warshall

| Test File | Vertices | Edges | Negative Cycle | Status |
|---|---:|---:|---|---|
| fw_10.txt | 10 | 17 | No | Pass |
| fw_100.txt | 100 | 197 | No | Pass |
| fw_500.txt | 500 | 997 | No | Pass |
| fw_1000.txt | 1000 | 1997 | No | Pass |
| fw_2000.txt | 2000 | 3997 | No | Pass |

---

## Assignment 2 Results

### Bellman-Ford

| Test File | Expected Output | Actual Output | Execution Time | Status |
|---|---|---|---:|---|
| bf_10.txt | Correct shortest distances | Correct | 0 ms | Pass |
| bf_100.txt | Correct shortest distances | Correct | 0 ms | Pass |
| bf_10000.txt | Correct shortest distances | Correct | 0 ms | Pass |
| bf_50000.txt | Correct shortest distances | Correct | 4.671 ms | Pass |
| bf_100000.txt | Correct shortest distances | Correct | 9.224 ms | Pass |

### Floyd-Warshall

| Test File | Expected Output | Actual Output | Execution Time | Status |
|---|---|---|---:|---|
| fw_10.txt | Correct distance matrix | Correct | 0 ms | Pass |
| fw_100.txt | Correct distance matrix | Correct | 0 ms | Pass |
| fw_500.txt | Correct distance matrix | Correct | 310.523 ms | Pass |
| fw_1000.txt | Correct distance matrix | Correct | 2493.64 ms | Pass |
| fw_2000.txt | Correct distance matrix | Correct | 21912.6 ms | Pass |

---

## Cross-Check

For the graph sizes where both algorithms are required, Bellman-Ford was run from every vertex and compared with the corresponding Floyd-Warshall row.

| Vertices | Result |
|---:|---|
| 10 | Cross-check Passed |
| 100 | Cross-check Passed |

---

## Negative Weight Test

A separate negative-weight test was performed to verify that Bellman-Ford correctly handles negative edge weights.

Result:

```text
Algorithm: Bellman-Ford
Source: 0
0 0
1 5
2 7
3 13
4 22
Negative cycle: none