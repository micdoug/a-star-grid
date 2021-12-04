#pragma once

#include <vector>
#include <optional>
#include <iostream>

// Represents a slot in the 2d grid.
struct GridSlot
{
    const int column;
    const int row;
    const bool is_empty;

    bool operator==(const GridSlot &other) const
    {
        return column == other.column &&
               row == other.row &&
               is_empty == other.is_empty;
    }
};

std::ostream &operator<<(std::ostream &out, const GridSlot &grid_slot);

// Represents a 2d grid with spaces that can be either empty or with an obstacle.
// If we consider R the number of rows and C the number of columns in the grid, it
// is allowed for the grid to have R != C.
class Grid final
{
public:
    // Initializes the grid considering the slots occupancy.
    explicit Grid(const std::vector<std::vector<bool>> &slots);

    // Get the grid slot of the provided row and column.
    std::optional<GridSlot> slot(int row, int column) const;

    // Get all neighbors of the grid slot of the row and column provided.
    // Neighbors are the slots tha are in the left, right, up and down of a given slot.
    const std::vector<GridSlot> neighbors(int row, int column) const;

    // Get the number of rows in the grid.
    size_t number_of_rows() const;

    // Get the number of columns in the grid for a given row.
    size_t number_of_columns(int row) const;

private:
    // Represents a 2d grid in which slots with false value are empty.
    std::vector<std::vector<bool>> slot_states_;
};