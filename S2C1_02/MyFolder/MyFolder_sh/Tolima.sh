mkdir Tolima
cd Tolima
cp ../DatosTolima.dat .
cp ../PlotsTolima.py .
 
awk '{ if ($2 == "March" && NF > 6) { print $5, $7 } else if ($1 == "March" && NF == 6) { print $4, $6 } }' DatosTolima.dat > DatosMarzo.txt

awk '{ if (NF > 6) { print $5, $7 } else if (NF == 6) { print $4, $6 } }' DatosTolima.dat > GRF_vs_EQ.txt

python PlotsTolima.py

rm DatosTolima.dat
