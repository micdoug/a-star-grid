#include <iostream>
#include "parsing.h"
#include "grid.h"
#include "print.h"
#include "find_path.h"
#include <unordered_set>
#include <string>

int main(int argc, char **argv)
{
    if (argc != 6)
    {
        std::cout << "Usage: a-star-grid <grid-input-file> <start_x> <start_y> <end_x> <end_y>" << std::endl;
        return 1;
    }

    auto maybe_grid = parse_grid_from_file(argv[1]);
    if (!maybe_grid)
    {
        return 1;
    }

    int begin_x = std::stoi(argv[2]);
    int begin_y = std::stoi(argv[3]);
    int end_x = std::stoi(argv[4]);
    int end_y = std::stoi(argv[5]);

    const auto &grid = maybe_grid.value();
    const auto result = find_path(begin_x, begin_y, end_x, end_y, grid);
    if (result.empty())
    {
        std::cout << "There is no path for the provided parameters." << std::endl;
        return 0;
    }
    const std::unordered_set<GridSlot> result_set{result.begin(), result.end()};
    print_grid_result(grid, begin_x, begin_y, end_x, end_y, result_set);
    return 0;
}