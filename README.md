MatterAndInteractionsIProject
=============================

Programming Project for CMU 33-131: Matter and Interactions I Fall 2014
This project attemps to simulate gas particles and measure the "speed of sound" by propigating a pressure wave through gas particles in a cylindrical container.


Description of files:

GasSim1D.py – particles constrained to 1 dimension.

GasSimF-ele.c – using the electric force between particles.

GasSimLJ.c - using a Lennard-Jones potential to calculate interatomic forces.

GasSimWCA.c – using a Weeks-Chandler-Andersen potential (essentially just a modified Lennard-Jones) to calculate interatomic forces.

GasSimVisualize.py – the program used to visualize all this data in neat animations using the vPython library.

SpeedTest.c and SpeedTest.py – used for testing the program's speed in C versus Python. From these it was ound that for 1000 particles and 200 iterations, the program written in C ran in about 12 seconds whereas same program written in Python ran in about 90 seconds. Clearly C is much more efficient. Note that if compiling with gcc, using the flag -O2 significantly improves the program's performance. 


Data is a folder for the Data outputted by the c programs for the python program to visualize. Note that the file paths to the Data files for all these programs are absoulte.
Execs is just a folder for the compiled c executables.
Screenshots is a folder for screenshots of the Visualization Program.
