BUILD_DIR = build
INCLUDE_DIR = include
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(SRC))

MAIN_OBJ = $(filter-out $(BUILD_DIR)/test.o, $(OBJ))
TEST_OBJ = $(filter-out $(BUILD_DIR)/main.o, $(OBJ))

all: $(BUILD_DIR)/main $(BUILD_DIR)/test

$(BUILD_DIR)/main: $(MAIN_OBJ)
	gcc $(MAIN_OBJ) -I$(INCLUDE_DIR) -o $(BUILD_DIR)/main

$(BUILD_DIR)/test: $(TEST_OBJ)
	gcc $(TEST_OBJ) -I$(INCLUDE_DIR) -o $(BUILD_DIR)/test

$(BUILD_DIR)/%.o: src/%.c
	gcc -c $< -I$(INCLUDE_DIR) -o $@

cleanObj:
	rm -f $(OBJ)

cleanall:
	rm -f $(BUILD_DIR)/main $(BUILD_DIR)/test $(OBJ)

run: 
	./$(BUILD_DIR)/main $(FLAGS)

runtests: 
	./$(BUILD_DIR)/test $(FLAGS)

.PHONY: all cleanObj cleanall run runtests
