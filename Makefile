CXX		  := clang++
CXX_FLAGS := -Wall -Wextra -std=c++17 -g
IMGUI_DIR = $(SRC)/vendor/imgui

BIN			:= bin
SRC1		:= src
SRC2		:= src/vendor/imgui
INCLUDE1	:= include
INCLUDE2	:= src/vendor
LIB			:= lib

LIBRARIES	:= -lglew -lglfw3
EXECUTABLE	:= app

all: $(BIN)/$(EXECUTABLE)

run: clean all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC1)/*.cpp $(SRC2)/*.cpp
	@mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE1) -I$(INCLUDE2) -L$(LIB)  $^ -o $@ $(LIBRARIES) -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
	@echo "Compiled "$<" successfully!"

clean:
	-rm -rf $(BIN)/*