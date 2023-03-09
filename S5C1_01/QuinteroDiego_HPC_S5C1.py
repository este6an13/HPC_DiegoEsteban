import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

# Read the data from the files
uniform_data = np.loadtxt('uniform_1000.dat', max_rows=1000,  delimiter='\n', dtype='int')
normal_data = np.loadtxt('normal_1000.dat', max_rows=1000, delimiter='\n', dtype='float')

# Create a PDF file to save the plots
pdf_pages = PdfPages('histogramas.pdf')

# Plot the histograms in separate plots
fig, ax = plt.subplots()
ax.hist(uniform_data, bins=50)
ax.set_xlabel('Value')
ax.set_ylabel('Frequency')
ax.set_title('Uniform Distribution')
pdf_pages.savefig(fig)

fig, ax = plt.subplots()
ax.hist(normal_data, bins=50)
ax.set_xlabel('Value')
ax.set_ylabel('Frequency')
ax.set_title('Normal Distribution')
pdf_pages.savefig(fig)

# Close the PDF file
pdf_pages.close()
