#!/bin/bash
gcc="gcc"
arg="-g -Wall -Wextra -std=c99 -Iglfw/include/ -Iinc/gald/ -Iinc/stb/ -Iinc src/$1 inc/glad.c inc/stb.c -o bin/$2 glfw/src/libglfw3.a"
lib=""
if [[ ! -d "glfw" ]]
then
	git clone https://github.com/glfw/glfw.git
fi
if [[ ! -f "glfw/src/libglfw3.a" ]]
then
	cd glfw
	cmake .
	make
	cd ../
fi

if [[ "$OSTYPE" == "darwin"* ]]; then
	lib="-framework Cocoa -framework OpenGL -framework IOKit"
	set -xe
	$gcc $arg $lib


elif [[ "$OSTYPE" == "linux-gnu"* ]];  then
lib="-lm -ldl -lpthread"
set -xe
$gcc $arg $lib

fi

./bin/$2