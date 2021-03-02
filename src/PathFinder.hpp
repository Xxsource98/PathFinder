#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include "stdafx.hpp"
#include "Grid.hpp"
#include "Algorithm.hpp"

namespace Source
{
	class Window : public sf::RenderWindow
	{
	public:
		explicit Window(sf::Vector2i windowSize, Colors appColors);
		const void draw();
		void updateArgs(Utils::AlgorithmFuncArgs newArgs);
	private:
		/* ImGui*/
		void drawColorsSection();
		void drawImGui();

		void deleteNodes();
		void pollEvent();
		void drawLoop();

		const void refreshArgs();
	private:
		Colors m_AppColors;
		Vector2 m_StartPosition = NEG_VECTOR2;
		Vector2 m_EndPosition = NEG_VECTOR2;
		std::vector<Node*> m_Nodes;
		std::string m_WindowName = "PathFinder | Created by: Xxsource98";
		std::unique_ptr<sf::RenderWindow> m_Window;
		std::unique_ptr<Grid> m_Grid;
		sf::Clock m_WindowClock;
		sf::Event m_WindowEvent;
		PressedKeys m_PressedKeys;
		bool m_ImGuiOpened = true;
		bool m_PathFound = false;
		bool m_DiagonalMove = false;
		bool m_StartAlgorithm = false;
	};
}