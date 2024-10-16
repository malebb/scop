CXX = clang++
CC = gcc

SRC = ./source/main.cpp \
	  ./source/app/App.cpp \
	  ./source/window/Window.cpp \
	  ./source/parser/ObjParser.cpp \
	  ./source/shader/Shader.cpp \
	  ./source/buffers/VBO.cpp \
	  ./source/buffers/VAO.cpp \
	  ./source/buffers/EBO.cpp

INC = -I./source/app \
	  -I./source/window \
	  -I./source/parser \
	  -I./source/shader \
	  -I./source/math \
	  -I./source/buffers

OBJ = $(SRC:.cpp=.o)

TARGET = scop

INCLUDES = -I$(GLFW_INC) -I $(GLAD_INC) $(INC)
GLFW_LIBRARY = -L$(GLFW_LIB)
GLAD_LIBRARY = -L$(GLAD_LIB)

CXXFLAGS = -Wall -Werror -Wextra -std=c++17 $(INCLUDES) -g
LDFLAGS = $(GLFW_LIBRARY) -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl $(GLAD_LIBRARY) -lglad

GLFW = ./lib/glfw
GLFW_INC = $(GLFW)/include
GLFW_LIB = $(GLFW)/build/src

GLAD = ./lib/glad
GLAD_SRC = $(GLAD)/src
GLAD_LIB = $(GLAD)/lib
GLAD_INC = $(GLAD)/include

%.o:%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(LDFLAGS)

clean: 
	rm -f $(OBJ) $(TARGET)

init_blank_linux:

	sudo apt update -y
	# Dependencies for X11
	sudo apt install xorg-dev -y

	# Dependencies for Wayland
	sudo apt install libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules -y

	# Compile glfw library
	sudo apt install cmake
	cmake -S $(GLFW) -B $(GLFW)/build
	make -C $(GLFW_LIB)

	# Compile glad library
	$(CC) -c $(GLAD_SRC)/glad.c -I $(GLAD_INC) -o $(GLAD_SRC)/glad.o
	mkdir -p $(GLAD_LIB)
	ar rcs $(GLAD_LIB)/libglad.a $(GLAD_SRC)/glad.o

init_linux:

	# Compile glfw library
	cmake -S $(GLFW) -B $(GLFW)/build
	make -C $(GLFW_LIB)

	# Compile glad library
	$(CC) -c $(GLAD_SRC)/glad.c -I $(GLAD_INC) -o $(GLAD_SRC)/glad.o
	mkdir -p $(GLAD_LIB)
	ar rcs $(GLAD_LIB)/libglad.a $(GLAD_SRC)/glad.o

.PHONY: clean