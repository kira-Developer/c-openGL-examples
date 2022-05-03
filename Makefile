OS = Unix
ifneq ($(shell uname -a | grep -i Darwin),)
	OS = MacOS
endif
ifneq ($(shell uname -a | grep -i Windows),)
	OS = Windows
endif
ifneq ($(shell uname -a | grep -i Linux),)
	OS = Linux
endif
all: bulid run 

install:
	git clone https://github.com/glfw/glfw.git
	  cd glfw && cmake . && make
	  

bulid: 
	file='$(file)';
	output='$(output)';
    ifeq ($(OS),Linux)
		-g -Wall -Wextra -std=c99 -Iglfw/include/ -Iinc/gald/ -Iinc/stb/ -Iinc src/$(file) inc/glad.c inc/stb.c -o bin/$(output) glfw/src/libglfw3.a -lm -ldl -lpthread
		

    endif
    ifeq ($(OS),Darwin)
	  	gcc -g -Wall -Wextra -std=c99 -Iglfw/include/ -Iinc/gald/ -Iinc/stb/ -Iinc src/$(file) inc/glad.c inc/stb.c -o bin/$(output) glfw/src/libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit

    endif

run: 
	./bin/$(output)


