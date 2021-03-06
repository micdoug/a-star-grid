#pragma once

#include <unordered_set>
#include "grid.h"
#include "hashing.h"

std::vector<GridSlot> find_path(int begin_x, int begin_y, int end_x, int end_y, const Grid &grid);