@ECHO OFF
cd Vendor/SFML
cmake -G "Visual Studio 16 2019" -A Win32 -S . -B "build"
cmake --build build --config Release
cmake --build build --config Debug
cd ../../
mkdir build
cd build
cmake -DCMAKE_GENERATOR_PLATFORM=x86 .. 
cmake .