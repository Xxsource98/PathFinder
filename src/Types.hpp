#pragma once
#include "stdafx.hpp"

using Vector2 = sf::Vector2f;
using int32 = std::uint32_t;

struct PressedKeys
{
	bool leftKey = false;
	bool rightKey = false;
	bool lShift = false;
	bool lCtrl = false;
};

#define NULL_VECTOR2 Vector2(0.f, 0.f)
#define NEG_VECTOR2 Vector2(-1.f, -1.f)

struct Node
{
	sf::RectangleShape rectShape;
	Vector2 position = NULL_VECTOR2;
	float gCost = FLT_MAX / 2;
	float hCost = 0;
	float fCost = FLT_MAX / 2;
	bool isWall = false;
	Node* parentNode = nullptr;

	Node(Vector2 position)
	{
		this->position = position;
	}

	bool operator < (Node node)
	{
		return fCost < node.fCost;
	}

	void setColor(sf::Color color)
	{
		rectShape.setFillColor(color);
	}
};

struct Colors
{
	sf::Color background =	sf::Color(88, 88, 88);
	sf::Color borderLines = sf::Color(0, 0, 0);
	sf::Color startNode =	sf::Color(40, 240, 90);
	sf::Color endNode =		sf::Color(45, 145, 235);
	sf::Color trace =		sf::Color(245, 145, 30);
	sf::Color wall =		sf::Color(17, 17, 17);
};