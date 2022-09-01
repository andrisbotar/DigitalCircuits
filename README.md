# DIGITAL CIRCUITS

This is a program to represent, manipulate, simulate and display digital circuits

Written by Andras Botar

May 2022

## REQUIRES:
- C++ 14 at least
### for drawing circuit_diagrams:
blockdiag http://blockdiag.com/en/, to install use "sudo isntall dnf blockdiag"
this requires and will install the follwing: 
- Python 2.6, 2.7, 3.2, 3.3 or later
- Pillow 2.2.1 or later.
- funcparserlib 0.3.6 or later.
- setuptools or distribute.

## CONTAINED FILES:
- digital_circuits.cpp and digitalcircuits.h: Central file containing main function, demonstration cases, etc..
- circuit.cpp and circuit.h: Defines a class for storing a circuit with multiple inputs, outputs, update functionality..
- components.cpp and Components.h: Contains digital circuit components such as AND gates, OR gates, buffers...
- utility.cpp and utility.h: Contains various utility functions for creating truth tables, printing tables,printing vectors...
- draw.cpp and draw.h Uses the "blockdiag" program to output images of the circuits
- other_classes.cpp and other_classes.h: miscelaneous classes and variables
- common.h: a shared header for all files, defines global variables

## FURTHER DETAILS:
- See the tutorial: option 1 in the main menu
- See project report
