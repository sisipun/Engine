#ifndef A_SEARCH
#define A_SEARCH

#include <map>
#include <cmath>
#include <tuple>

struct Point
{
    int x, y;

    double getDistance(Point p) const
    {
        return abs(x - p.x) + abs(y - p.y);
    }

    bool operator<(const Point &p) const
    {
        return std::tie(x, y) < std::tie(p.x, p.y);
    }

    bool operator==(const Point &p) const
    {
        return x == p.x && y == p.y;
    }
};

class AStarSearch
{
public:
    std::map<Point, Point> search(int **map, int width, int height, Point start, Point end);
};

#endif