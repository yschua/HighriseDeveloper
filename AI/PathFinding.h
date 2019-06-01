/*   This file is part of Highrise Developer.
*
*   Highrise Developer is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.

*   Highrise Developer is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with Highrise Developer.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _PATHFINDING_H
#define _PATHFINDING_H

#include <vector>
#include <map>
#include <set>
#include <memory>

class Level;
class Tower;
class RouteBase;

namespace Internal
{
class Node
{
public:
    Node(Level* level);
    Node(RouteBase* route);
    virtual ~Node();
    void AddNeighbor(Node* node);

    Level* m_level;
    RouteBase* m_route;
    std::set<Node*> m_neighbors;
    int gScore;
    int fScore;
};
}

struct RouteRequest
{
    RouteBase* m_route;
    int m_from;
    int m_to;
};

class Path
{
public:
    Path() {}
    virtual ~Path() {}
    inline void Add(RouteRequest req) { m_path.push_back(req); }
    inline void Reset() { m_it = m_path.begin(); }
    inline RouteRequest GetRouteRequest() const { return *m_it; }
    inline void Advance() { m_it++; }
    inline bool IsEnd() const { return m_it == m_path.end(); }

private:
    std::vector<RouteRequest> m_path;
    std::vector<RouteRequest>::iterator m_it;
};

class PathFinding
{
public:
    PathFinding(Tower* tower);
    virtual ~PathFinding();
    void ConstructGraph();
    std::unique_ptr<Path> AStar(int start, int goal);

private:
    Tower* m_tower;
    std::vector<std::unique_ptr<Internal::Node>> m_nodes;
    std::map<int, Internal::Node*> m_levelNodes;
};

#endif