# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -Isrc
LDFLAGS = -lX11 -lXft

# Paths and files
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)
BIN = wm

# Target
all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(SRC_DIR)/*.o $(BIN)

rebuild: clean all

.PHONY: all clean rebuild
