if [ ! -f "glfw" ]
then
	git clone https://github.com/glfw/glfw.git
fi
if [ ! -f "glfw/src/libglfw3.a" ]
then
	cd glfw
	cmake .
	make
	cd ../
fi

if [[ "$OSTYPE" == "darwin"* ]]; then
set -xe
gcc -g -Wall -Wextra -std=c99 -Iglfw/include/GLFW/ -Iinc/gald/ -Iinc/stb/ -Iinc src/$1 inc/glad.c inc/stb.c -o bin/$2 glfw/src/libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit


elif [[ "$OSTYPE" == "linux-gnu"* ]];  then
gcc -g -Wall -Wextra -std=c99 -Iglfw/include/GLFW/ -Iinc/gald/ -Iinc/stb/ -Iinc $1 inc/glad.c inc/stb.c -o bin/$2 glfw/src/libglfw3.a -lm -ldl -lpthread
fi

./bin/$2