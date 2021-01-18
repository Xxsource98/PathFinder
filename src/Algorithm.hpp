#pragma once
#include "stdafx.hpp"
#include "utils.hpp"

namespace Source
{
    namespace Algorithm
    {
        inline std::vector<Vector2> reconstructPath(Node* currentNode, Node* startNode)
        {
            std::vector<Vector2> path;
            while (currentNode->parentNode != nullptr)
            {
                currentNode = currentNode->parentNode;
                path.push_back(currentNode->position);
            }
            path.pop_back();
            std::reverse(path.begin(), path.end());

            return path;
        }

        inline std::vector<Vector2> solvePath(std::vector<Node*> allNodes, int32 gridSize, Vector2 startPos, Vector2 endPos, bool diagonal = false)
        {
            if (startPos == NEG_VECTOR2 || endPos == NEG_VECTOR2)
                return std::vector<Vector2>();
            
            Node* startNode = new Node(startPos);
            Node* endNode = new Node(endPos);
            std::set<Node*> openSet;

            startNode->gCost = 0;
            startNode->fCost = diagonal ? Utils::diagonalDistance(startNode, endNode) : Utils::manhattanDistance(startNode, endNode);

            openSet.insert(startNode);

            while (!openSet.empty())
            {
                auto currentNode = *openSet.begin();

                if (currentNode->position == endNode->position)
                {
                    auto res = reconstructPath(currentNode, startNode);
                    delete startNode;
                    delete endNode;
                    return res;
                }

                openSet.erase(currentNode);

                auto neighbors = Utils::getNodeNeighbors(allNodes, gridSize, currentNode, diagonal);
                for (auto neighbor : neighbors)
                {
                    auto gCost = currentNode->gCost + (diagonal ? Utils::diagonalDistance(currentNode, neighbor) : Utils::manhattanDistance(currentNode, neighbor));
                    if (gCost < neighbor->gCost)
                    {
                        neighbor->parentNode = currentNode;
                        neighbor->gCost = gCost;
                        neighbor->hCost = diagonal ? Utils::diagonalDistance(neighbor, endNode) : Utils::manhattanDistance(neighbor, endNode);
                        neighbor->fCost = neighbor->gCost + neighbor->hCost;

                        if (!Utils::findInSet(openSet, neighbor))
                            openSet.insert(neighbor);
                    }
                }
            }

            return std::vector<Vector2>();
        }
    }
}