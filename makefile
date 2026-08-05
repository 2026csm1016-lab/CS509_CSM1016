CXX = g++
CXXFLAGS = -std=c++17 -O2

TARGET = wrapper

SRC = \
assignment_01/wrapper/wrapper.cpp \
assignment_01/src/gemm.cpp \
assignment_01/src/csr.cpp

all:
	$(CXX) $(CXXFLAGS) -Iassignment_01/src $(SRC) -o $(TARGET)

clean:
	del /Q wrapper.exe