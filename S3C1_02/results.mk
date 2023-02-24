resultados.pdf: resultados.tex plot.pdf plot1.pdf
    pdflatex resultados.tex

plot.pdf: plotdatos.py datos.dat
    python3 plotdatos.py

plot1.pdf: plotdatos1.py datos1.dat
    python3 plotdatos1.py

datos.dat: makedatos.py
    python3 makedatos.py > datos.dat

datos1.dat: makedatos1.out
   ./makedatos1.out > datos1.dat

makedatos1.out: makedatos1.cpp
   g++ makedatos1.cpp -o makedatos1.out
