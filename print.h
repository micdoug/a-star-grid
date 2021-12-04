#pragma once

#include <iostream>
#include "grid.h"
#include <unordered_set>
#include "hashing.h"

// todo: implement a function to print the grid when parsed

std::ostream &operator<<(std::ostream &out, const Grid &grid);

// todo: implement a function to print the path in the grid

void print_grid_result(const Grid &grid, int start_x, int start_y, int end_x, int end_y, const std::unordered_set<GridSlot> &path);