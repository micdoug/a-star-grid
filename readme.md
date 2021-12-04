# A* Grid

This repository contains an implementation of a A* algorithm to find the path between two points in a 2d plane.

The program receives as input a file that represents a 2D grid. This file is composed of multiple lines with values `0` or `1` separated by a `,`.
The value `0` denotes an empty space in the grid, and the value `1` denotes a obstacle in the grid (i.e. a space that cannot be used to build a path).
The program should parse this file and represent the grid in memory. Then the program receives as an input from the user two `[x,y]` points for defining the start and end points respectively.
After receiving the input from the user, the program executes the A* algorithm to find a path from the two points. The program also shows a message when it is not possible to find a path between the two points in the current grid.

The program is implemented in pure C++.

## How to build

This project is managed by cmake. You must have cmake 3.11 or newer versions and a c++ compiler compatible with `C++ 20` specification.

To build just run the following commands:

```sh
# create a directory to hold the build files
mkdir build
cd build

# generate build files
cmake ..

# build the project
make
```

After running those commands there should be a `a-star-grid` executable in the build directory.

## Example

Example of execution:

Assuming a `grid.txt` file with the following content:
```
0, 1, 0, 0,
0, 1, 0, 0,
0, 1, 0, 0,
0, 0, 0, 1,
```

If we execute the program with the command:
```
a-star-grid grid.txt 0 0 0 3
```

We are saying to the program that considering the grid represented in the file `grid.txt`, find a path from `row 0` and `column 0` to `row 0` and `column 3`. The result is the following:

```
🚦	⛰️	.	🏁	
🚗	⛰️	🚗	🚗	
🚗	⛰️	🚗	.	
🚗	🚗	🚗	⛰️
```

In the result `🚦` denotes the start of the path, `🏁` denotes the end of the path, `🚗` denotes intermediary steps in the path, `.` denotes empty slots in the grid and `⛰️` denotes an obstacle.

If we execute:
```
a-start-grid grid.txt 0 0 3 3
```

The result is:

```
There is no path for the provided parameters.
```