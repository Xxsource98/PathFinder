#pragma once
#include "stdafx.hpp"
#include <imgui.h>
#include "Types.hpp"

namespace Source
{
	namespace Utils
	{
		inline ImVec4 getColorAsImVec4(sf::Color sfColor)
		{
			ImVec4 color;
			color.x = sfColor.r / 255;
			color.y = sfColor.g / 255;
			color.z = sfColor.b / 255;
			color.w = sfColor.a / 255;
			return color;
		}

		inline sf::Color getColorAsSFML(ImVec4 fColor)
		{
			sf::Color color;
			color.r = fColor.x * 255;
			color.g = fColor.y * 255;
			color.b = fColor.z * 255;
			color.a = fColor.w * 255;
			return color;
		}

		inline Node* findNodeByPosition(std::vector<Node*> allNodes, Vector2 position)
		{
			for (auto e : allNodes)
			{
				if (e->position == position)
				{
					return e;
				}
			}

			return new Node(NULL_VECTOR2);
		}

		inline void clearSetPointers(std::set<Node*> allNodes)
		{
			for (auto node : allNodes)
			{
				delete node;
			}
		}

		/* http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html */
		inline float manhattanDistance(Node* startNode, Node* endNode)
		{
			float deltaX = std::abs(endNode->position.x - startNode->position.x); // weird calculation here but works better and more legit, than original one
			float deltaY = std::abs(endNode->position.y - startNode->position.y);

			return deltaX + deltaY;
		}

		inline float diagonalDistance(Node* startNode, Node* endNode)
		{
			float deltaX = std::abs(startNode->position.x - endNode->position.x);
			float deltaY = std::abs(startNode->position.y - endNode->position.y);

			return std::sqrt(std::pow(deltaX, 2) + std::pow(deltaY, 2));
		}

		inline bool findInSet(std::set<Node*> set, Node* element)
		{
			for (auto e : set)
			{
				if (e == element)
				{
					return true;
				}
			}

			return false;
		}

		inline std::vector<Node*> getNodeNeighbors(std::vector<Node*> allNodes, int32 gridSize, Node* currentNode, bool diagonal = false)
		{
			std::vector<Node*> neighbors;
			auto nodePos = currentNode->position;

			if ((nodePos.x - 1) >= 0)
			{
				auto node = findNodeByPosition(allNodes, Vector2(nodePos.x - 1, nodePos.y));
				if (!node->isWall)
					neighbors.push_back(node);
			}

			if ((nodePos.x + 1) <= gridSize)
			{
				auto node = findNodeByPosition(allNodes, Vector2(nodePos.x + 1, nodePos.y));
				if (!node->isWall)
					neighbors.push_back(node);
			}

			if ((nodePos.y - 1) >= 0)
			{
				auto node = findNodeByPosition(allNodes, Vector2(nodePos.x, nodePos.y - 1));
				if (!node->isWall)
					neighbors.push_back(node);
			}

			if ((nodePos.y + 1) <= gridSize)
			{
				auto node = findNodeByPosition(allNodes, Vector2(nodePos.x, nodePos.y + 1));
				if (!node->isWall)
					neighbors.push_back(node);
			}

			if (diagonal)
			{
				if ((nodePos.x - 1) >= 0 && (nodePos.y - 1) >= 0)
				{
					auto node = findNodeByPosition(allNodes, Vector2(nodePos.x - 1, nodePos.y - 1));
					if (!node->isWall)
						neighbors.push_back(node);
				}

				if ((nodePos.x + 1) <= gridSize && (nodePos.y - 1) >= 0)
				{
					auto node = findNodeByPosition(allNodes, Vector2(nodePos.x + 1, nodePos.y - 1));
					if (!node->isWall)
						neighbors.push_back(node);
				}

				if ((nodePos.x - 1) >= 0 && (nodePos.y + 1) <= gridSize)
				{
					auto node = findNodeByPosition(allNodes, Vector2(nodePos.x - 1, nodePos.y + 1));
					if (!node->isWall)
						neighbors.push_back(node);
				}

				if ((nodePos.x + 1) <= gridSize && (nodePos.y + 1) <= gridSize)
				{
					auto node = findNodeByPosition(allNodes, Vector2(nodePos.x + 1, nodePos.y + 1));
					if (!node->isWall)
						neighbors.push_back(node);
				}
			}

			return neighbors;
		}
	}
}