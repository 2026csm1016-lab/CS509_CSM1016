CXX = g++
CXXFLAGS = -O2 -std=c++11

all: gemm

gemm: main.cpp gemm.cpp csr.cpp
	$(CXX) $(CXXFLAGS) main.cpp gemm.cpp csr.cpp -o gemm

clean:
	del /Q gemm.exe