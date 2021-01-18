#include "PathFinder.hpp"

Source::Window::Window(sf::Vector2i windowSize, Colors appColors)
{
	int32 windowStyle = sf::Style::Close | sf::Style::Titlebar;
	this->m_Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(windowSize.x, windowSize.y), this->m_WindowName, windowStyle);
	this->m_Grid = std::make_unique<Grid>(10, appColors);
	this->m_AppColors = std::move(appColors);
	ImGui::SFML::Init(*this->m_Window.get());
}

const void Source::Window::draw()
{
	while (this->m_Window->isOpen())
	{
		this->pollEvent();
		this->drawLoop();
	}

	ImGui::SFML::Shutdown();
	this->deleteNodes();
}

void Source::Window::deleteNodes()
{
	for (auto node : this->m_Nodes)
	{
		delete node;
	}

	this->m_Nodes.clear();
}

void Source::Window::pollEvent()
{
	while (this->m_Window->pollEvent(this->m_WindowEvent))
	{
		ImGui::SFML::ProcessEvent(this->m_WindowEvent);

		if (this->m_WindowEvent.type == sf::Event::Closed)
		{
			this->m_Window->close();
		}

		if (!this->m_ImGuiOpened && this->m_WindowEvent.type == sf::Event::MouseButtonPressed)
		{
			if (this->m_WindowEvent.key.code == sf::Mouse::Left)
			{
				m_PressedKeys.leftKey = true;
			}

			if (this->m_WindowEvent.key.code == sf::Mouse::Right)
			{
				m_PressedKeys.rightKey = true;
			}
		}


		if (this->m_WindowEvent.type == sf::Event::KeyPressed)
		{
			if (this->m_WindowEvent.key.code == sf::Keyboard::Insert)
			{
				this->m_ImGuiOpened = !this->m_ImGuiOpened;
				return;
			}

			if (this->m_WindowEvent.key.code == sf::Keyboard::LShift)
				m_PressedKeys.lShift = true;

			if (this->m_WindowEvent.key.code == sf::Keyboard::LControl)			
				m_PressedKeys.lCtrl = true;	
		}
	}
}

void Source::Window::drawColorsSection()
{
	if (ImGui::TreeNode("Colors"))
	{
		static auto background		= Utils::getColorAsImVec4(this->m_AppColors.background);
		static auto borderLines		= Utils::getColorAsImVec4(this->m_AppColors.borderLines);
		static auto startNode		= Utils::getColorAsImVec4(this->m_AppColors.startNode);
		static auto endNode			= Utils::getColorAsImVec4(this->m_AppColors.endNode);
		static auto trace			= Utils::getColorAsImVec4(this->m_AppColors.trace);
		static auto walls			= Utils::getColorAsImVec4(this->m_AppColors.wall);

		if (ImGui::ColorEdit3("Background", (float*)&background))
		{
			this->m_AppColors.background	= Utils::getColorAsSFML(background);
		}
		if (ImGui::ColorEdit3("Border Lines", (float*)&borderLines))
		{
			this->m_AppColors.borderLines	= Utils::getColorAsSFML(borderLines);
		}
		if (ImGui::ColorEdit3("Start Node", (float*)&startNode))
		{
			this->m_AppColors.startNode		= Utils::getColorAsSFML(startNode);
		}
		if (ImGui::ColorEdit3("End Node", (float*)&endNode))
		{
			this->m_AppColors.endNode		= Utils::getColorAsSFML(endNode);
		}
		if (ImGui::ColorEdit3("Trace", (float*)&trace))
		{
			this->m_AppColors.trace			= Utils::getColorAsSFML(trace);
		}
		if (ImGui::ColorEdit3("Walls", (float*)&walls))
		{
			this->m_AppColors.wall			= Utils::getColorAsSFML(walls);
			
		}
		if (ImGui::Button("Apply"))
		{
			this->m_Grid->updateColors(this->m_AppColors);
			this->m_Grid->clearGrid(this->m_Nodes);
		}


		ImGui::TreePop();
	}
}

void Source::Window::drawImGui()
{
	ImGui::SFML::Update(*this->m_Window.get(), this->m_WindowClock.restart());

	if (m_ImGuiOpened)
	{
		if (ImGui::Begin("Path Finder", &this->m_ImGuiOpened))
		{
			static bool diagonalPath = false;
			static bool failedToFind = false;
			static int gridSize = this->m_Grid->getGridSize();

			this->drawColorsSection();
			ImGui::Checkbox("Diagonal Move", &diagonalPath);

			if (ImGui::SliderInt("Grid Size", &gridSize, 10, 100))
				this->m_Grid->updateSize(gridSize, this->m_Nodes);
			
			if (ImGui::Button("Solve Algorithm"))
			{
				auto path = Algorithm::solvePath(this->m_Nodes, this->m_Grid->getGridSize(), 
							this->m_Grid->getStartPosition(), this->m_Grid->getEndPosition(), diagonalPath);

				for (auto e : path)
				{
					auto node = Utils::findNodeByPosition(this->m_Nodes, e);
					node->setColor(m_AppColors.trace);
				}

				failedToFind = !path.empty();
			}

			if (ImGui::Button("Clear Grid"))
				this->m_Grid->clearGrid(this->m_Nodes);
			

			if (failedToFind)
				ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "Failed to Find Path");

			ImGui::Separator();
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), "Press Insert to toggle Menu");
			ImGui::Text("* Close menu for create/destroy walls *");
			ImGui::Text("How to Use: ");
			ImGui::Text("Press LCtrl (Left Control) to select Start Node");
			ImGui::Text("Press LShift (Left Shift) to select End Node");
			ImGui::Text("Press/Hold Left Mouse Button to create Walls");
			ImGui::Text("Press/Hold Right Mouse Button to destroy Walls");
			ImGui::Text("For create a path, press 'Solve Algorithm' button");
			ImGui::Text("Have fun! Created By: Xxsource98"); 
		}
		ImGui::End();
	}
}

void Source::Window::drawLoop()
{
	this->m_Window->clear();

	this->m_Grid->draw(this->m_Window.get(), this->m_Nodes, this->m_PressedKeys, this->m_ImGuiOpened);
	this->drawImGui();
	/* draw things */
	for (auto node : this->m_Nodes)
	{
		this->m_Window->draw(node->rectShape);
	}

	ImGui::SFML::Render(*this->m_Window.get());
	this->m_Window->display();
}
