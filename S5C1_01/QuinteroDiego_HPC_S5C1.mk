CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17
LDFLAGS=

.PHONY: all clean

all: uniform_1000.exe normal_1000.exe
    ./uniform_1000.exe > uniform_1000.dat
    ./normal_1000.exe > normal_1000.dat
    python QuinteroDiego_HPC_S5C1.py
    pdflatex resultados.tex

uniform_1000.exe: uniform_1000.cpp
    $(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

normal_1000.exe: normal_1000.cpp
    $(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
    rm -f *.o *.exe *.dat *.pdf
