#include "PathFinder.hpp"

inline void algorithmThreadFunc(Source::Window* win)
{
	using namespace Source::Algorithm;

	START:
	while (!Global::startAlgorithm) {}

	auto args = Global::globArgs;

	auto path = solvePath(args.nodes, args.gridSize, args.startPos, args.endPos, args.diagonalMove);

	for (auto e : path)
	{
		auto node = Source::Utils::findNodeByPosition(args.nodes, e);
		node->setColor(args.traceColor);
		Global::doAnimation ? sf::sleep(sf::milliseconds(Global::animationDelay / 2)) : void();
	}

	args.failedToFind = path.empty();

	win->updateArgs(args);

	Global::startAlgorithm = false;
	goto START;
}

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
	sf::Thread algorithmThread(algorithmThreadFunc, this);
	algorithmThread.launch();

	while (this->m_Window->isOpen())
	{
		this->pollEvent();
		this->drawLoop();
		this->refreshArgs();
	}

	algorithmThread.terminate();
	ImGui::SFML::Shutdown();
	this->deleteNodes();
}


void Source::Window::updateArgs(Utils::AlgorithmFuncArgs newArgs)
{
	this->m_DiagonalMove = newArgs.diagonalMove;
	this->m_PathFound = !newArgs.failedToFind;
	this->m_Nodes = newArgs.nodes;
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
		static auto visitedNodes	= Utils::getColorAsImVec4(Algorithm::Global::visitedNodeColor);

		if (ImGui::ColorEdit3("Background", (float*)&background))
		{
			this->m_AppColors.background			= Utils::getColorAsSFML(background);
		}
		if (ImGui::ColorEdit3("Border Lines", (float*)&borderLines))
		{
			this->m_AppColors.borderLines			= Utils::getColorAsSFML(borderLines);
		}
		if (ImGui::ColorEdit3("Start Node", (float*)&startNode))
		{
			this->m_AppColors.startNode				= Utils::getColorAsSFML(startNode);
		}
		if (ImGui::ColorEdit3("End Node", (float*)&endNode))
		{
			this->m_AppColors.endNode				= Utils::getColorAsSFML(endNode);
		}
		if (ImGui::ColorEdit3("Trace", (float*)&trace))
		{
			this->m_AppColors.trace					= Utils::getColorAsSFML(trace);
		}
		if (ImGui::ColorEdit3("Visited Nodes", (float*)&visitedNodes))
		{
			Algorithm::Global::visitedNodeColor		= Utils::getColorAsSFML(visitedNodes);
		}
		if (ImGui::ColorEdit3("Walls", (float*)&walls))
		{
			this->m_AppColors.wall					= Utils::getColorAsSFML(walls);	
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
			static int gridSize = this->m_Grid->getGridSize();

			this->drawColorsSection();
			ImGui::Checkbox("Diagonal Move", &this->m_DiagonalMove);
			ImGui::Checkbox("Animation", &Algorithm::Global::doAnimation);
			ImGui::Checkbox("Show Visited Nodes", &Algorithm::Global::showVisitedNodes);

			if (ImGui::SliderInt("Grid Size", &gridSize, 10, 100))
				this->m_Grid->updateSize(gridSize, this->m_Nodes);
			
			if (Algorithm::Global::doAnimation)
			{
				ImGui::SliderInt("Animation Delay (milliseconds)", (int*)&Algorithm::Global::animationDelay, 5, 1000);
			}

			if (ImGui::Button("Solve Algorithm"))
			{
				Source::Algorithm::Global::startAlgorithm = true;
			}

			if (ImGui::Button("Stop Solving"))
			{
				Source::Algorithm::Global::stopAnimation = true;
			}

			if (ImGui::Button("Clear Grid"))
			{
				Source::Algorithm::Global::stopAnimation = true;
				this->m_Grid->clearGrid(this->m_Nodes);
				this->refreshArgs();
				Source::Algorithm::Global::stopAnimation = false;
			}

			if (!this->m_PathFound)
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

const void Source::Window::refreshArgs()
{
	Utils::AlgorithmFuncArgs args;
	args.diagonalMove = this->m_DiagonalMove;
	args.startPos = this->m_Grid->getStartPosition();
	args.endPos = this->m_Grid->getEndPosition();
	args.failedToFind = !this->m_PathFound;
	args.traceColor = this->m_AppColors.trace;
	args.nodes = this->m_Nodes;

	Algorithm::Global::globArgs = args;
}
