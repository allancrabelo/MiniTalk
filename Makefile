CC = cc
CFLAGS = -Wall -Wextra -Werror

SERVER_NAME = server
CLIENT_NAME = client

BUILD_OBJ = .obj

VPATH = src src/client src/server src/utils src_bonus

INCLUDE_DIR = includes
INCLUDE = -I$(INCLUDE_DIR)

UTILS_FILES = utils utils2
SERVER_FILES = server
CLIENT_FILES = client

UTILS_BONUS_FILES = utils utils2
SERVER_BONUS_FILES = server
CLIENT_BONUS_FILES = client

SERVER_SRC = $(addsuffix .c, $(SERVER_FILES)) $(addsuffix .c, $(UTILS_FILES))
CLIENT_SRC = $(addsuffix .c, $(CLIENT_FILES)) $(addsuffix .c, $(UTILS_FILES))

SERVER_BONUS_SRC = $(addsuffix .c, $(SERVER_BONUS_FILES)) $(addsuffix .c, $(UTILS_BONUS_FILES))
CLIENT_BONUS_SRC = $(addsuffix .c, $(CLIENT_BONUS_FILES)) $(addsuffix .c, $(UTILS_BONUS_FILES))

SERVER_OBJ = $(addprefix $(BUILD_OBJ)/, $(SERVER_SRC:.c=.o))
CLIENT_OBJ = $(addprefix $(BUILD_OBJ)/, $(CLIENT_SRC:.c=.o))

SERVER_BONUS_OBJ = $(addprefix $(BUILD_OBJ)/, $(SERVER_BONUS_SRC:.c=.o))
CLIENT_BONUS_OBJ = $(addprefix $(BUILD_OBJ)/, $(CLIENT_BONUS_SRC:.c=.o))

intro:
	@echo "\033[0;31m███╗   ███╗██╗███╗   ██╗██╗████████╗ █████╗ ██╗     ██╗  ██╗\033[0m"
	@echo "\033[0;31m████╗ ████║██║████╗  ██║██║╚══██╔══╝██╔══██╗██║     ██║ ██╔╝\033[0m"
	@echo "\033[0;31m██╔████╔██║██║██╔██╗ ██║██║   ██║   ███████║██║     █████╔╝ \033[0m"
	@echo "\033[0;31m██║╚██╔╝██║██║██║╚██╗██║██║   ██║   ██╔══██║██║     ██╔═██╗ \033[0m"
	@echo "\033[0;31m██║ ╚═╝ ██║██║██║ ╚████║██║   ██║   ██║  ██║███████╗██║  ██╗\033[0m"
	@echo "\033[0;31m╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝\033[0m"
	@echo "\033[0;31m                                         by: Allan Rabelo   \033[0m"

all: intro $(BUILD_OBJ) $(SERVER_NAME) $(CLIENT_NAME)

$(BUILD_OBJ):
	@mkdir -p $@

$(SERVER_NAME): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT_NAME): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_OBJ)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

bonus: intro $(BUILD_OBJ) $(SERVER_NAME)_bonus $(CLIENT_NAME)_bonus

$(SERVER_NAME)_bonus: $(SERVER_BONUS_OBJ)
	$(CC) $(CFLAGS) $^ -o $(SERVER_NAME)

$(CLIENT_NAME)_bonus: $(CLIENT_BONUS_OBJ)
	$(CC) $(CFLAGS) $^ -o $(CLIENT_NAME)

clean:
	rm -rf $(BUILD_OBJ)

fclean: clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)

re: fclean all

