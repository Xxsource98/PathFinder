#include "stdafx.hpp"
#include "PathFinder.hpp"
#include "imguiStyle.hpp"

/*
	Last Update: 02.03.2021

	Changelog:
		-> Fixed Invalid Default Colors Values
		-> Added "Animation" on finding path
		-> Added Visited Nodes (with changeable color)
		-> Fixed "Failed to Find Path" notification
*/

int main()
{
	Colors appColors;
	Source::Window win(sf::Vector2i(810, 810), appColors); /* If You want change resolution, make it as a square (for ex. 800x800, 1000x1000) for the best look */
	imguiStyle();

	win.draw();

	return EXIT_SUCCESS;
}