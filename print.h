#pragma once

#include <iostream>
#include "grid.h"
#include <unordered_set>
#include "hashing.h"

std::ostream &operator<<(std::ostream &out, const Grid &grid);

void print_grid_result(const Grid &grid, int start_x, int start_y, int end_x, int end_y, const std::unordered_set<GridSlot> &path);