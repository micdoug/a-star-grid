#include "find_path.h"

#include <vector>
#include <unordered_set>
#include <list>
#include "hashing.h"

class PathSlot
{
public:
    explicit PathSlot(const GridSlot &slot, int distance, int weight, PathSlot *previous) : slot_(slot), distance_(distance), weight_(weight), previous_(previous)
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

    PathSlot *previous() const
    {
        return previous_;
    }

private:
    const GridSlot slot_;
    const int distance_;
    const int weight_;
    PathSlot *previous_;
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

std::vector<GridSlot> find_path(int begin_x, int begin_y, int end_x, int end_y, const Grid &grid)
{
    std::unordered_set<PathSlot> path;
    std::unordered_set<PathSlot> neighbors;

    // insert the start slot in the list of neighbors
    neighbors.insert(PathSlot{
        /*slot=*/grid.slot(begin_x, begin_y).value(),
        /*distance=*/0,
        /*weight=*/calculate_weight(begin_x, begin_y, end_x, end_y),
        /*previous=*/nullptr,
    });

    while (!neighbors.empty())
    {
        // Get the next node path with least weight.
        const PathSlot *min_slot = nullptr;
        for (const auto &next_slot : neighbors)
        {
            if (next_slot.slot().is_empty && (min_slot == nullptr || next_slot < *min_slot))
            {
                min_slot = &next_slot;
            }
        }
        // If we could not reach the goal and we don't have a next node path, there is no path to the destiny.
        if (min_slot == nullptr)
        {
            return {};
        }
        // Insert the next slot in the path.
        auto [node_iter, _] = path.insert(*min_slot);
        PathSlot *current_node = const_cast<PathSlot *>(&(*node_iter));
        neighbors.erase(*min_slot); // All references to min_slot are now invalidated.

        // Check if the added node is the goal, if it is, we can return the actual path.
        if (current_node->slot().row == end_x && current_node->slot().column == end_y)
        {
            std::vector<GridSlot> path_result;
            PathSlot *current_path_slot = current_node;
            while (current_path_slot != nullptr)
            {
                path_result.push_back(current_path_slot->slot());
                current_path_slot = current_path_slot->previous();
            }
            return std::vector<GridSlot>{path_result.rbegin(), path_result.rend()};
        }

        // calculate next neighbors
        const auto slot_neighbors = grid.neighbors(current_node->slot().row, current_node->slot().column);
        for (const auto &slot_neighbor : slot_neighbors)
        {
            PathSlot neighbor_path_slot{
                /*slot=*/slot_neighbor,
                /*distance=*/current_node->distance() + 1,
                /*weight=*/calculate_weight(slot_neighbor.row, slot_neighbor.column, end_x, end_y),
                /*previous=*/current_node,
            };

            // If the neighbor is not present in the current explored path, we add it.
            if (path.find(neighbor_path_slot) == path.end() && neighbors.find(neighbor_path_slot) == neighbors.end())
            {
                neighbors.insert(neighbor_path_slot);
            }
        }
    }
    return {};
}