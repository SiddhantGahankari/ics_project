CC = gcc
SRC_DIR = src
OBJ_DIR = obj
BIN = main

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

$(BIN): $(OBJS)
	$(CC) -o $@ $^ -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run

clean:
	rm -rf $(OBJ_DIR) $(BIN)

run: $(BIN)
	./$(BIN)
