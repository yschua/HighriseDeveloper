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

#include "PathFinding.h"
#include "../Tower/Tower.h"
#include "../Tower/Level.h"
#include "../Routes/RouteBase.h"

using namespace Internal;

Node::Node(Level* level) : m_level(level), m_route(nullptr) {}
Node::Node(RouteBase* route) : m_level(nullptr), m_route(route) {}
Node::~Node() {}

void Node::AddNeighbor(Node* node)
{
    m_neighbors.insert(node);
    node->m_neighbors.insert(this);
}

PathFinding::PathFinding(Tower* tower) : m_tower(tower)
{
}

PathFinding::~PathFinding()
{
}

void PathFinding::ConstructGraph()
{
    m_nodes.clear();
    m_levelNodes.clear();

    for (auto level : m_tower->GetLevels()) {
        auto levelNode = std::make_unique<Node>(level);
        m_levelNodes.insert(std::make_pair(level->GetLevel(), levelNode.get()));
        m_nodes.push_back(std::move(levelNode));
    }

    for (auto route : m_tower->GetRouteList()) {
        auto routeNode = std::make_unique<Node>(route);
        for (auto levelNum : route->GetConnectedLevels()) {
            routeNode->AddNeighbor(m_levelNodes[levelNum]);
        }
        m_nodes.push_back(std::move(routeNode));
    }
}

static RouteBase* GetRoute(Node* a, Node* b)
{
    if (a->m_route != nullptr) return a->m_route;
    if (b->m_route != nullptr) return b->m_route;
    return nullptr;
}

static Level* GetLevel(Node* a, Node* b)
{
    if (a->m_level != nullptr) return a->m_level;
    if (b->m_level != nullptr) return b->m_level;
    return nullptr;
}

static int HeuristicCost(Node* start, Node* goal)
{
    if (start->m_route == nullptr && goal->m_route == nullptr)
        return 100;

    auto route = GetRoute(start, goal);
    auto level = GetLevel(start, goal);

    if (route->StopsOnLevel(level->GetLevel()))
        return 1;

    return 100;
}

static Node* GetNodeLowestFScore(const std::set<Node*>& openSet)
{
    int minFScore = std::numeric_limits<int>::max();
    Node* ret = nullptr;
    for (auto node : openSet) {
        if (node->fScore < minFScore) {
            ret = node;
            minFScore = node->fScore;
        }
    }
    return ret;
}

static int DistBetween(Node* a, Node* b)
{
    return 1;
}

static std::unique_ptr<Path> ConstructPath(
    const std::map<Node*, Node*>& cameFrom,
    Node* current)
{
    std::vector<Node*> nodePath = {current};
    while (cameFrom.find(current) != cameFrom.end()) {
        current = cameFrom.at(current);
        nodePath.push_back(current);
    }

    if (nodePath.size() % 3 != 0) {
        return nullptr;
    }

    auto path = std::make_unique<Path>();
    for (auto it = nodePath.rbegin(); it != nodePath.rend();) {
        Level* from      = (*it++)->m_level;
        RouteBase* route = (*it++)->m_route;
        Level* to        = (*it++)->m_level;

        if (from == nullptr || route == nullptr || to == nullptr) {
            return nullptr;
        }

        path->Add(RouteRequest{route, from->GetLevel(), to->GetLevel()});
    }
    return path;
}

std::unique_ptr<Path> PathFinding::AStar(int startLevel, int goalLevel)
{
    if (m_levelNodes.find(startLevel) == m_levelNodes.end() ||
        m_levelNodes.find(goalLevel) == m_levelNodes.end())
        return nullptr;

    Node* start = m_levelNodes[startLevel];
    Node* goal = m_levelNodes[goalLevel];

    std::set<Node*> closedSet;
    std::set<Node*> openSet = {start};

    for (auto& node : m_nodes) {
        node->gScore = node->fScore = std::numeric_limits<int>::max();
    }

    std::map<Node*, Node*> cameFrom;

    start->gScore = 0;
    start->fScore = HeuristicCost(start, goal);

    while (!openSet.empty()) {
        Node* current = GetNodeLowestFScore(openSet);

        if (current == goal) {
            return ConstructPath(cameFrom, current);
        }

        openSet.erase(current);
        closedSet.insert(current);

        for (auto neighbor : current->m_neighbors) {
            if (closedSet.find(neighbor) != closedSet.end()) continue;

            int gScoreTentative = current->gScore + DistBetween(current, neighbor);

            if (openSet.find(neighbor) == openSet.end()) {
                openSet.insert(neighbor);
            } else if (gScoreTentative >= neighbor->gScore) {
                continue;
            }

            cameFrom[neighbor] = current;
            neighbor->gScore = gScoreTentative;
            neighbor->fScore = neighbor->gScore + HeuristicCost(neighbor, goal);
        }
    }

    return nullptr;
}
