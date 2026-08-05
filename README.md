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