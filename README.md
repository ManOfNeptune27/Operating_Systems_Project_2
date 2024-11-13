# Operating Systems Banker's Algorithm

This program implements the Banker's Algorithm in C++ to check for a safe sequence in a system with multiple processes and resources. It uses an input file to load the initial resource allocation, maximum demand, and available resources for each process, then determines if the system is in a safe state.

## Compilation Instructions
The `bankers_algorithm.cpp` file can be compiled using the following command in a terminal:

```bash
g++ bankers_algorithm.cpp -o bankers_algorithm
```

## Execution Instructions
To run the program, make sure `inputFile.txt` is in the same directory as the executable, then execute the following command in a terminal:

```bash
./bankers_algorithm
```

### Input File Format
The program reads from an input file named `inputFile.txt`, which should be formatted as follows:
1. The **Allocation Matrix** (one row per process).
2. The **Maximum Demand Matrix** (one row per process).
3. The **Available Resources Array** (one row representing available units of each resource).

### Example of inputFile.txt
```plaintext
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
3 3 2
```

In this example:
- The first 5 rows represent the Allocation Matrix.
- The next 5 rows represent the Maximum Demand Matrix.
- The last row represents the Available Resources.

## Output
The program will indicate whether the system is in a safe state. If so, it will print the safe sequence; if not, it will state that the system is not safe.

### Example Output
If the system is safe:
```
System is in a safe state.
Safe sequence is: P1 -> P3 -> P4 -> P0 -> P2
```

If the system is not safe:
```
System is not in a safe state.
```

## Author
Conner Brunner