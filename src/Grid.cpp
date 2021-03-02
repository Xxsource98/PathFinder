#include "Grid.hpp"

Source::Grid::Grid(int32 gridSize, Colors appColors) :
	m_GridSize(std::move(gridSize)), m_AppColors(std::move(appColors))
{
	this->m_Mouse = std::make_unique<sf::Mouse>();
}

const void Source::Grid::draw(sf::RenderWindow* window, std::vector<Node*>& nodes, PressedKeys& keys, bool isImGuiOpened)
{
	auto windowSize = window->getSize();
	this->drawGrid(windowSize, nodes);

	for (auto e : nodes)
	{
		if (this->isInMouseBounds(this->m_Mouse.get()->getPosition(*window), 
			e->rectShape.getPosition(), 
			e->rectShape.getSize()))
		{
			this->gridAction(e, keys, isImGuiOpened);
		}
	}
}

void Source::Grid::clearGrid(std::vector<Node*>& nodes)
{
	this->m_StartPosition = NEG_VECTOR2;
	this->m_EndPosition = NEG_VECTOR2;
	nodes.clear();
}

void Source::Grid::updateSize(int32 newSize, std::vector<Node*>& nodes)
{
	this->clearGrid(nodes);
	this->m_GridSize = newSize;
}

void Source::Grid::updateColors(Colors appColors)
{
	this->m_AppColors = appColors;
}

int32 Source::Grid::getGridSize() const
{
	return this->m_GridSize;
}

Vector2 Source::Grid::getStartPosition() const
{
	return this->m_StartPosition;
}

Vector2 Source::Grid::getEndPosition() const
{
	return this->m_EndPosition;
}

void Source::Grid::setStartPosition(Vector2 newPos)
{
	this->m_StartPosition = newPos;
}

void Source::Grid::setEndPosition(Vector2 newPos)
{
	this->m_EndPosition = newPos;
}

const bool Source::Grid::isInMouseBounds(sf::Vector2i mousePosition, sf::Vector2f element, sf::Vector2f elementSize)
{
	return  (mousePosition.x >= element.x) && 
			(mousePosition.x <= element.x + elementSize.x) && 
			(mousePosition.y >= element.y) && 
			(mousePosition.y <= element.y + elementSize.y);
}

const sf::RectangleShape Source::Grid::drawRectangle(sf::Vector2f position, sf::Vector2f size)
{
	sf::RectangleShape rect;

	rect.setPosition(sf::Vector2f(position));
	rect.setSize(sf::Vector2f(size));
	rect.setFillColor(m_AppColors.background);
	rect.setOutlineColor(m_AppColors.borderLines);
	rect.setOutlineThickness(1.f);

	return rect;
}

void Source::Grid::gridAction(Node* selectedNode, PressedKeys& keys, bool isImGuiOpened)
{
	if (keys.lShift)
	{
		if (this->m_StartPosition == NEG_VECTOR2 && selectedNode->position != this->m_EndPosition && !selectedNode->isWall)
		{
			selectedNode->setColor(m_AppColors.startNode);
			this->m_StartPosition = selectedNode->position;
		}
		else
		{
			if (selectedNode->position == this->m_StartPosition)
			{
				selectedNode->setColor(m_AppColors.background);
				this->m_StartPosition = NEG_VECTOR2;
			}
		}
		keys.lShift = false;
		return;
	}

	if (keys.lCtrl)
	{
		if (this->m_EndPosition == NEG_VECTOR2 && selectedNode->position != this->m_StartPosition && !selectedNode->isWall)
		{
			selectedNode->setColor(m_AppColors.endNode);
			this->m_EndPosition = selectedNode->position;
		}
		else
		{
			if (selectedNode->position == this->m_EndPosition)
			{
				selectedNode->setColor(m_AppColors.background);
				this->m_EndPosition = NEG_VECTOR2;
			}
		}
		keys.lCtrl = false;
		return;
	}

	if (!keys.lShift && !keys.lCtrl && !isImGuiOpened && this->m_Mouse->isButtonPressed(sf::Mouse::Left))
	{
		if (!selectedNode->isWall && selectedNode->position != this->m_StartPosition && selectedNode->position != this->m_EndPosition)
		{
			selectedNode->setColor(m_AppColors.wall);
			selectedNode->isWall = true;
		}
	}

	if (!keys.lShift && !keys.lCtrl && !isImGuiOpened && this->m_Mouse->isButtonPressed(sf::Mouse::Right))
	{
		if (selectedNode->isWall && selectedNode->position != this->m_StartPosition && selectedNode->position != this->m_EndPosition)
		{
			selectedNode->setColor(m_AppColors.background);
			selectedNode->isWall = false;
		}
	}
}

void Source::Grid::drawGrid(sf::Vector2u windowSize, std::vector<Node*>& nodes)
{
	for (float y = 0; y < this->m_GridSize; y++)
	{
		for (float x = 0; x < this->m_GridSize; x++)
		{
			if (nodes.size() != (std::pow(this->m_GridSize, 2)))
			{
				auto node = new Node(Vector2(x, y));
				auto nodeWidthX = windowSize.x * 1.0f / this->m_GridSize;
				auto nodeWidthY = windowSize.y * 1.0f / this->m_GridSize;
				node->rectShape = drawRectangle(sf::Vector2f(x * nodeWidthX, y * nodeWidthY),
					sf::Vector2f(nodeWidthX, nodeWidthY));

				nodes.push_back(node);
			}
		}
	}
}
