UNAME_S = $(shell uname -s)
GCC = gcc 
CFLAG = -g -Wall -Wextra -std=c99 
CFLAG += -Iglfw/include/ -Iinc/gald/ -Iinc/stb/ -Iinc
CFLAG += src/$(file) inc/glad.c inc/stb.c -o bin/$(output)
LDFLAGS = glfw/src/libglfw3.a -lm

ifeq ($(UNAME_S), Darwin)
	LDFLAGS +=-framework OpenGL -framework IOKit -framework Cocoa
endif

ifeq ($(UNAME_S), Linux)
	LDFLAGS += -ldl -lpthread
endif
all: bulid run 

install:
	git clone https://github.com/glfw/glfw.git
	  cd glfw && cmake . && make
	  

bulid: 
	file='$(file)';
	output='$(output)';
    	
	$(GCC) $(CFLAG) $(LDFLAGS)



run: 
	./bin/$(output)


