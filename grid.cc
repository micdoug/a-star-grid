#include "grid.h"
#include <algorithm>

Grid::Grid(const std::vector<std::vector<bool>> &slots)
{
    std::copy(slots.begin(), slots.end(), std::back_inserter(slot_states_));
}

std::optional<GridSlot> Grid::slot(int row, int column) const
{
    if (row < 0 || column < 0 || (row + 1) > slot_states_.size() || (column + 1) > slot_states_[row].size())
    {
        return {};
    }
    return GridSlot{
        .column = column,
        .row = row,
        .is_empty = !slot_states_[row][column],
    };
}

const std::vector<GridSlot> Grid::neighbors(int row, int column) const
{
    std::vector<GridSlot> slots;
    const auto up_neighbor = slot(row - 1, column);
    if (up_neighbor.has_value())
    {
        slots.push_back(up_neighbor.value());
    }
    const auto down_neighbor = slot(row + 1, column);
    if (down_neighbor.has_value())
    {
        slots.push_back(down_neighbor.value());
    }
    const auto left_neighbor = slot(row, column - 1);
    if (left_neighbor.has_value())
    {
        slots.push_back(left_neighbor.value());
    }
    const auto right_neighbor = slot(row, column + 1);
    if (right_neighbor.has_value())
    {
        slots.push_back(right_neighbor.value());
    }
    return slots;
}

size_t Grid::number_of_rows() const
{
    return slot_states_.size();
}

size_t Grid::number_of_columns(int row) const
{
    return slot_states_[row].size();
}

std::ostream &operator<<(std::ostream &out, const GridSlot &grid_slot)
{
    out << "GridSlot(row="
        << grid_slot.row
        << ", column="
        << grid_slot.column
        << ", is_empty="
        << (grid_slot.is_empty ? "yes" : "no")
        << ")";
    return out;
}