#pragma once
#include "Types.hpp"
#include "utils.hpp"

namespace Source
{
	class Grid
	{
	public:
		Grid(int32 gridSize, Colors appColors);

		const void draw(sf::RenderWindow* window, std::vector<Node*>& nodes, PressedKeys& keys, bool isImGuiOpened);

		void clearGrid(std::vector<Node*>& nodes);
		void updateSize(int32 newSize, std::vector<Node*>& nodes);
		void updateColors(Colors appColors);
		int32 getGridSize() const;
		Vector2 getStartPosition() const;
		Vector2 getEndPosition() const;
	private:
		const bool isInMouseBounds(sf::Vector2i mousePosition, sf::Vector2f element, sf::Vector2f elementSize);
		const sf::RectangleShape drawRectangle(sf::Vector2f position, sf::Vector2f size);
		void gridAction(Node* selectedNode, PressedKeys& keys, bool isImGuiOpened);
		void drawGrid(sf::Vector2u windowSize, std::vector<Node*>& nodes);

	private:
		Colors m_AppColors;
		std::unique_ptr<sf::Mouse> m_Mouse;
		int32 m_GridSize = 10;
		float m_NodeWidth = 20.f;
		Vector2 m_StartPosition = NEG_VECTOR2;
		Vector2 m_EndPosition = NEG_VECTOR2;
	};
}