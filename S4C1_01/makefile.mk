err_derF.pdf err_derC.pdf err_der_h.pdf: QuinteroDiego_HPC_S4C1Casa.py err_derF.dat
	python3 QuinteroDiego_HPC_S4C1Casa.py

err_derF.dat : err_derF.exe
	./err_derF.exe > err_derF.dat

err_derC.dat : err_derC.exe
	./err_derC.exe > err_derC.dat

err_der_h.dat : err_der_h.exe
	./err_der_h.exe > err_der_h.dat

err_derF.exe : err_derF.cpp
   	g++ err_derF.cpp -o err_derF.exe

err_derC.exe : err_derC.cpp
	g++ err_derC.cpp -o err_derC.exe

err_der_h.exe : err_der_h.cpp
	g++ err_der_h.cpp -o err_der_h.exe

