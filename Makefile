CXX		  := clang++
CXX_FLAGS := -Wall -Wextra -std=c++17 -g

BIN		:= bin
SRC		:= src
INCLUDE1	:= include
INCLUDE2	:= src/vender
LIB		:= lib

LIBRARIES	:= -lglew -lglfw3
EXECUTABLE	:= app


all: $(BIN)/$(EXECUTABLE)

run: clean all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE1) -I$(INCLUDE2) -L$(LIB) $^ -o $@ $(LIBRARIES) -framework Cocoa -framework OpenGL -framework IOKit
	@echo "Compiled "$<" successfully!"

clean:
	-rm -rf $(BIN)/*