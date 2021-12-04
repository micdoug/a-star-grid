#include "print.h"

const std::string kPathSpaceImage = "🚗\t";
const std::string kObstacleSpaceImage = "⛰️\t";
const std::string kEmptySpaceImage = ".\t";
const std::string kFinalSpaceImage = "🏁\t";
const std::string kStartSpaceImage = "🚦\t";

std::ostream &operator<<(std::ostream &out, const Grid &grid)
{
    for (int i = 0; i < grid.number_of_rows(); i++)
    {
        for (int j = 0; j < grid.number_of_columns(i); j++)
        {
            const auto maybe_slot = grid.slot(i, j);
            if (maybe_slot.has_value())
            {
                const auto &slot = maybe_slot.value();
                if (slot.is_empty)
                {
                    out << kEmptySpaceImage;
                }
                else
                {
                    out << kObstacleSpaceImage;
                }
            }
        }
        out << std::endl;
    }
    return out;
}

void print_grid_result(const Grid &grid, int start_x, int start_y, int end_x, int end_y, const std::unordered_set<GridSlot> &path)
{
    for (int i = 0; i < grid.number_of_rows(); i++)
    {
        for (int j = 0; j < grid.number_of_columns(i); j++)
        {
            const auto maybe_slot = grid.slot(i, j);
            if (maybe_slot.has_value())
            {
                const auto &slot = maybe_slot.value();
                if (slot.row == start_x && slot.column == start_y)
                {
                    std::cout << kStartSpaceImage;
                }
                else if (slot.row == end_x && slot.column == end_y)
                {
                    std::cout << kFinalSpaceImage;
                }
                else if (path.find(slot) != path.end())
                {
                    std::cout << kPathSpaceImage;
                }
                else if (slot.is_empty)
                {
                    std::cout << kEmptySpaceImage;
                }
                else
                {
                    std::cout << kObstacleSpaceImage;
                }
            }
        }
        std::cout << std::endl;
    }
}