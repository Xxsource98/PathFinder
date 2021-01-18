@ECHO OFF
cd Vendor
git clone https://github.com/ocornut/imgui.git
git clone https://github.com/eliasdaler/imgui-sfml.git
git clone https://github.com/SFML/SFML.git
cd SFML
cmake -G "Visual Studio 16 2019" -A Win32 -S . -B "build"
cmake --build build --config Release
cmake --build build --config Debug
cd ../../
mkdir build
cd build
cmake -DCMAKE_GENERATOR_PLATFORM=x86 .. 
cmake .
