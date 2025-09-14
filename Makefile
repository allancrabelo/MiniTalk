CC = cc
CFLAGS = -Wall -Wextra -Werror

SERVER_NAME = server
CLIENT_NAME = client

BUILD_OBJ = .obj

VPATH = src src/client src/server src/utils

INCLUDE_DIR = includes
INCLUDE = -I$(INCLUDE_DIR)

UTILS_FILES = utils utils2
SERVER_FILES = server
CLIENT_FILES = client

SERVER_SRC = $(addsuffix .c, $(SERVER_FILES)) $(addsuffix .c, $(UTILS_FILES))
CLIENT_SRC = $(addsuffix .c, $(CLIENT_FILES)) $(addsuffix .c, $(UTILS_FILES))

SERVER_OBJ = $(addprefix $(BUILD_OBJ)/, $(SERVER_SRC:.c=.o))
CLIENT_OBJ = $(addprefix $(BUILD_OBJ)/, $(CLIENT_SRC:.c=.o))

all: $(BUILD_OBJ) $(SERVER_NAME) $(CLIENT_NAME)

$(BUILD_OBJ):
	@mkdir -p $@

$(SERVER_NAME): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT_NAME): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_OBJ)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(BUILD_OBJ)

fclean: clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)

re: fclean all
