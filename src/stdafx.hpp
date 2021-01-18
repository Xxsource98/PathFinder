#pragma once

#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <cmath>
#include <iostream>
#include <future>

// Files
#include <SFML/Graphics.hpp>

// Libraries
#pragma comment(lib, "opengl32.lib")
#ifdef NDEBUG /* Release */
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#else /* Debug*/
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#endif