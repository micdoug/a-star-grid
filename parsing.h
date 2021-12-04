#pragma once

#include "grid.h"
#include <iostream>
#include <optional>

std::optional<Grid> parse_grid_from_file(const std::string& file_path);