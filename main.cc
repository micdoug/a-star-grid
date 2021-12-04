#include <iostream>
#include "parsing.h"
#include "grid.h"
#include "print.h"
#include "find_path.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: a-star-grid <grid-input-file>" << std::endl;
        return 1;
    }

    auto maybe_grid = parse_grid_from_file(argv[1]);
    if (!maybe_grid)
    {
        return 1;
    }

    const auto &grid = maybe_grid.value();

    std::cout << grid << std::endl;

    const auto result = find_path(0, 0, 2, 2, grid);

    print_grid_result(grid, 0, 0, 2, 2, result);

    return 0;
}