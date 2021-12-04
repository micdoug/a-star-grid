#include "find_path.h"

#include <vector>
#include <unordered_set>
#include <list>
#include "hashing.h"

class PathSlot
{
public:
    explicit PathSlot(const GridSlot &slot, int distance, int weight) : slot_(slot), distance_(distance), weight_(weight)
    {
    }

    bool operator==(const PathSlot &other) const
    {
        return slot_ == other.slot_;
    }

    bool operator<(const PathSlot &other) const
    {
        return (weight() + distance()) < (other.weight() + other.distance());
    }

    const GridSlot &slot() const
    {
        return slot_;
    }

    int distance() const
    {
        return distance_;
    }

    int weight() const
    {
        return weight_;
    }

private:
    const GridSlot slot_;
    const int distance_;
    const int weight_;
};

namespace std
{
    template <>
    struct hash<PathSlot>
    {
        size_t operator()(const PathSlot &path_slot) const
        {
            return std::hash<GridSlot>()(path_slot.slot());
        }
    };
}

struct PathSlotWeightComparator
{
    bool operator()(const PathSlot &left, const PathSlot &right)
    {
        return (left.weight() + left.distance()) < (right.weight() + right.distance());
    }
};

int calculate_weight(int current_x, int current_y, int end_x, int end_y)
{
    // calculate the manhantan distance
    return std::abs(end_x - current_x) + std::abs(end_y - current_y);
}

std::unordered_set<GridSlot> find_path(int begin_x, int begin_y, int end_x, int end_y, const Grid &grid)
{
    std::unordered_set<PathSlot> path;
    std::unordered_set<PathSlot> neighbors;

    // insert the start slot in the list of neighbors

    neighbors.insert(PathSlot{
        /*slot=*/grid.slot(begin_x, begin_y).value(),
        /*distance=*/0,
        /*weight=*/calculate_weight(begin_x, begin_y, end_x, end_y),
    });

    int current_distance = 0;
    while (!neighbors.empty())
    {
        current_distance += 1;

        const PathSlot* min_slot = nullptr;
        for (const auto& next_slot: neighbors)
        {
            if (next_slot.slot().is_empty && (min_slot == nullptr || next_slot < *min_slot))
            {
                min_slot = &next_slot;
            }
        }
        if (min_slot == nullptr)
        {
            return {};
        }
        path.insert(*min_slot);

        if (min_slot->slot().row == end_x && min_slot->slot().column == end_y)
        {
            std::unordered_set<GridSlot> path_result;
            for (const auto &path_slot : path)
            {
                path_result.insert(path_slot.slot());
            }
            return path_result;
        }

        // calculate next neighbors
        const auto slot_neighbors = grid.neighbors(min_slot->slot().row, min_slot->slot().column);
        for (const auto &slot_neighbor : slot_neighbors)
        {
            PathSlot neighbor_path_slot{
                /*slot=*/slot_neighbor,
                /*distance=*/current_distance,
                /*weight=*/calculate_weight(slot_neighbor.row, slot_neighbor.column, end_x, end_y),
            };
            if (path.find(neighbor_path_slot) == path.end() && neighbors.find(neighbor_path_slot) == neighbors.end())
            {
                neighbors.insert(neighbor_path_slot);
            }
        }

        neighbors.erase(*min_slot);
    }
    return {};
}