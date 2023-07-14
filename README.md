# Flight Sorting System

## Tech Stack
- C++
- GUI: FLTK (Fast Light Toolkit)

## Description
This project focuses on implementing a flight sorting system that allows users to sort flights based on various criteria. The system provides a command-line interface as well as a graphical user interface (GUI) for input and visualization. It utilizes C++ programming, algorithm design, and GUI development.

The project has two main subsystems: the input subsystem and the output subsystem.

### Input Subsystem
The input subsystem handles user input and supports two modes:
1. Command-Line Interface (CLI): The `handleCommandLine` function processes the command-line arguments provided by the user.
2. Graphical User Interface (GUI): The `handleInputGUI` function creates a GUI window for users to enter all the necessary arguments.

### Output Subsystem
The output subsystem generates three types of output:
1. Visualization: The sorting process is visualized through a graphical interface using the FLTK library. The `VisualizerWindow` class displays the sorted flights with interactive animations.
2. Console Output: The `printAllData` function prints the gathered data and the sorted flights to the console.
3. File Output: The `printAllData` function also writes the gathered data and the sorted flights to an output file.

## How to Run
To run the Flight Sorting System, follow the steps below:

1. Clone the repository:
2. Set up the FLTK library
3. Compile the C++ source files:
```
g++ -std=c++11 -o flight_sorting main.cpp -lfltk
```
4. Run the program:
```
./flight_sorting
```

Please note that the FLTK library is required for running the graphical user interface (GUI).
