all: bulid run 

install:
	git clone https://github.com/glfw/glfw.git
	  cd glfw && cmake . && make
	  

bulid: 
	file='$(file)';
	output='$(output)';\
	gcc -g -Wall -Iglfw/include/GLFW/ -Iinc/gald/ -Iinc/stb/ -Iinc src/$(file) inc/glad.c inc/stb.c -o bin/$(output) glfw/src/libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit

run: 
	./bin/$(output)


