# CS509_CSM1016 

# Name
* Harshita Mahor

---

# Overview

This assignment implements:

1. General Matrix Multiplication (GEMM)

   * Simple GEMM
   * Blocking GEMM

2. Compressed Sparse Row (CSR) Representation

   * Adjacency List Input
   * Conversion to CSR Format

The project also includes a menu-driven wrapper for selecting algorithms and test cases.

---

# Folder Structure

```
.
├── input/
│   ├── gemm_test_01.txt
│   ├── gemm_test_02.txt
│   ├── gemm_test_03.txt
│   ├── gemm_test_04.txt
│   ├── gemm_test_05.txt
│   ├── graph_10.txt
│   ├── graph_100.txt
│   ├── graph_10000.txt
│   ├── graph_50000.txt
│   └── graph_100000.txt
│
├── main.cpp
├── gemm.cpp
├── gemm.h
├── csr.cpp
├── csr.h
├── Makefile
└── README.md
```

---

# Algorithms Implemented

## 1. GEMM

Two implementations are provided:

* Simple Matrix Multiplication
* Blocking Matrix Multiplication

Execution time for both implementations is measured separately.

---

## 2. CSR

Graph input is provided as an adjacency list.

The program converts the adjacency list into Compressed Sparse Row (CSR) representation using:

* rowPtr
* colIndex

The CSR conversion is treated as preprocessing.

---

# Graph Input Format

The graph input is stored as an adjacency list.

Format:

```
Number_of_Vertices

Number_of_Neighbours Neighbour1 Neighbour2 ...

Number_of_Neighbours Neighbour1 ...

...
```

Example:

```
5
2 1 2
2 0 3
1 4
1 4
0
```

---

# Test Files

## GEMM

* gemm_test_01.txt
* gemm_test_02.txt
* gemm_test_03.txt
* gemm_test_04.txt
* gemm_test_05.txt

## CSR

* graph_10.txt
* graph_100.txt
* graph_10000.txt
* graph_50000.txt
* graph_100000.txt

---

# Compilation

Using Makefile:

```
mingw32-make
```

or

```
make
```

---

# Execution

Run:

```
./gemm
```

or on Windows:

```
gemm.exe
```

The wrapper displays a menu to select:

* GEMM
* CSR

After selecting an algorithm, the desired test case can be chosen.

---

# Notes

* Vertex numbering follows the convention 0 to V-1.
* CSR conversion time is not included in algorithm execution time.
* Large matrices and graphs are not printed to the console to avoid excessive output.
* Execution time is displayed for each algorithm.
