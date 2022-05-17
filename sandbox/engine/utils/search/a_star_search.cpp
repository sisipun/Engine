#include <queue>
#include <vector>

#include "a_star_search.h"

std::vector<Point> getNeighbors(int mapWidth, int mapHeight, Point point)
{
    std::vector<Point> neighbors;
    if (point.x - 1 >= 0)
    {
        neighbors.push_back({point.x - 1, point.y});
    }
    if (point.x + 1 < mapWidth)
    {
        neighbors.push_back({point.x + 1, point.y});
    }

    if (point.y - 1 >= 0)
    {
        neighbors.push_back({point.x, point.y - 1});
    }
    if (point.y + 1 < mapHeight)
    {
        neighbors.push_back({point.x, point.y + 1});
    }

    return neighbors;
}

std::map<Point, Point> AStarSearch::search(int **map, int width, int height, Point start, Point end)
{
    std::map<Point, Point> path;
    std::map<Point, int> costs;
    costs[start] = 0;
    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<std::pair<double, Point>>> pointsToExplore;
    pointsToExplore.push(std::make_pair(0, start));

    while (!pointsToExplore.empty())
    {
        std::pair<int, Point> current = pointsToExplore.top();
        pointsToExplore.pop();

        if (current.second == end) {
            break;
        }

        std::vector<Point> neighbors = getNeighbors(width, height, current.second);
        for (auto neighbor : neighbors)
        {
            int neighborCost = *(*(map + neighbor.x) + neighbor.y);
            int newCost = costs[current.second] + neighborCost;
            if (neighborCost >= 0 && (costs.find(neighbor) == costs.end() || newCost < costs[neighbor]))
            {
                costs[neighbor] = newCost;
                path[neighbor] = current.second;
                pointsToExplore.push(std::make_pair(newCost + neighbor.getDistance(end), neighbor));
            }
        }
    }

    return path;
}
