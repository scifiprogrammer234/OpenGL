#!/bin/sh
g++ main.cpp -o app -L/usr/local/lib/ -lGLEW -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -I/Users/mac/Desktop/opengl/GLEW/include