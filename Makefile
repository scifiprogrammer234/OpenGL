CXX		  := clang++
CXX_FLAGS := -Wall -Wextra -std=c++17 -g
IMGUI_DIR = $(SRC)/vendor/imgui

BIN			:= bin
SRC1		:= src
SRC2		:= src/vendor/imgui
SRC3		:= src/tests
INCLUDE1	:= include
INCLUDE2	:= src/vendor
INCLUDE3	:= src
LIB			:= lib

LIBRARIES	:= -lglew -lglfw3
EXECUTABLE	:= app

all: $(BIN)/$(EXECUTABLE)

run: clean all
	@./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC1)/*.cpp $(SRC2)/*.cpp $(SRC3)/*.cpp
	@mkdir -p $(BIN)
	@$(CXX) $(CXX_FLAGS) -I$(INCLUDE1) -I$(INCLUDE2) -I$(INCLUDE3) -L$(LIB)  $^ -o $@ $(LIBRARIES) -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
	@echo "Compiled successfully!"

clean:
	@rm -rf $(BIN)/*