# What is an A* algorithm?
A* (pronounced "A-star") is a graph traversal and path search algorithm, which is often used in many fields of computer science due to its completeness, optimality, and optimal efficiency. One major practical drawback is its space complexity, as it stores all generated nodes in memory. Thus, in practical travel-routing systems, it is generally outperformed by algorithms which can pre-process the graph to attain better performance, as well as memory-bounded approaches; however, A* is still the best solution in many cases. [Read More on Wikipedia](https://en.wikipedia.org/wiki/A*_search_algorithm)

# Pictures
![1](https://user-images.githubusercontent.com/36642285/104959050-97845080-59d1-11eb-802d-180d906a9156.PNG)
![2](https://user-images.githubusercontent.com/36642285/104959051-981ce700-59d1-11eb-999e-1aa0052846c9.PNG)
![3](https://user-images.githubusercontent.com/36642285/104959052-981ce700-59d1-11eb-82dd-94161430211f.PNG)
![4](https://user-images.githubusercontent.com/36642285/104959054-98b57d80-59d1-11eb-9b18-4c144e66d98e.PNG)

# Test Version
You can test the file downloading it from here: [Download Link](https://github.com/Xxsource98/PathFinder/releases/tag/1.0)

# Building a Project
Clone my repostiory and open build32.bat and wait until everything get build successfully (if you want to change compiler, press right on the "build32.bat" and "Visual Studio 16 2019" to your compiler). You can open a project and build with your compiler, if everything is fine, go to your Debug/Release build folder and put here files: 
```
FOR DEBUG BUILD:
sfml-graphics-d-2.dll
sfml-system-d-2.dll
sfml-window-d-2.dll
``` 
```
FOR RELEASE BUILD:
sfml-graphics-2.dll
sfml-system-2.dll
sfml-window-2.dll
```
<b>These files are located in: ```Vendor/SFML/build/lib/YOUR_BUILD_TYPE```. Without these files you can't run the program.</b>

# Functions
The application is using ImGui where are some useful features: 
```
- Solve Algorithm
- Clear Grid
- Change Grid Size
- Change Grid, Nodes colors
- Instruction how to use the application
```

# License
Project is under GNU General Public License v3.0. You can read more there: [www.gnu.org](https://www.gnu.org/licenses/gpl-3.0.html)
