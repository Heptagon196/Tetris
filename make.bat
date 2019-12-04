@echo off
echo Building a release version
echo [1/4] Compiling ./Block.cpp
g++ -c --std=c++11 -Dwindows -O2 ./Block.cpp -o ./Block.o
echo [2/4] Compiling ./main.cpp
g++ -c --std=c++11 -Dwindows -O2 ./main.cpp -o ./main.o
echo [3/4] Compiling ./ConioPlus.cpp
g++ -c --std=c++11 -Dwindows -O2 ./ConioPlus.cpp -o ./ConioPlus.o
echo [4/4] Building tetris
g++ --std=c++11 -Dwindows -O2 ./Block.o ./main.o ./ConioPlus.o -o tetris
