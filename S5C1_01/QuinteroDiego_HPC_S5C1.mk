resultados.pdf: resultados.tex histogramas.pdf
	pdflatex resultados.tex

histogramas.pdf: QuinteroDiego_HPC_S5C1.py uniform_1000.dat normal_1000.dat
	python3 QuinteroDiego_HPC_S5C1.py

normal_1000.dat: normal_1000.exe
	./normal_1000.exe > normal_1000.dat

uniform_1000.dat: uniform_1000.exe
	./uniform_1000.exe > uniform_1000.dat

normal_1000.exe: normal_1000.cpp
	g++ normal_1000.cpp -o normal_1000.exe

uniform_1000.exe: uniform_1000.cpp
	g++ uniform_1000.cpp -o uniform_1000.exe

