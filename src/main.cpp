#include "stdafx.hpp"
#include "PathFinder.hpp"
#include "imguiStyle.hpp"

int main()
{
	Colors appColors;
	Source::Window win(sf::Vector2i(800, 800), appColors); /* Don't change resolution, 800x800 looks the best here */
	imguiStyle();

	win.draw();

	return EXIT_SUCCESS;
}