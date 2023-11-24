SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib

LIB := juggfind
ALL := $(LIB)
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC := gcc
CPPFLAGS := -Iinc -MMD -MP -I/usr/include/python3.11
CFLAGS   := -Wall -pedantic -O3 
LDFLAGS  := 
LDLIBS   := -lm -lpthread -lssl -lcrypto

all: $(ALL)

$(LIB): $(OBJ) | $(LIB_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -shared -o $@.so
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -fPIC $< -o $@
$(LIB_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(OBJ_DIR)
clean_all:
	@$(RM) -rv $(LIB_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
.PHONY: all clean
