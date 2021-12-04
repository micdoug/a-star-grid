# A* Grid

This repository contains an implementation of a A* algorithm to find the path between two points in a 2d plane.

The program receives as input a file that represents a 2D grid. This file is composed of multiple lines with values `0` or `1` separated by a `,`.
The value `0` denotes an empty space in the grid, and the value `1` denotes a obstacle in the grid (i.e. a space that cannot be used to build a path).
The program should parse this file and represent the grid in memory. Then the program receives as an input from the user two `[x,y]` points for defining the start and end points respectively.
After receiving the input from the user, the program executes the A* algorithm to find a path from the two points. The program also shows a message when it is not possible to find a path between the two points in the current grid.

The program is implemented in pure C++. I will add instructions on how to execute it later.