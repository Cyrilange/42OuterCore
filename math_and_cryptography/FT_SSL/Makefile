NAME        := ft_ssl

SRC_DIR     := source
OBJ_DIR     := objs

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -MMD -MP

SRCS        := main.c utils.c md5.c sha256.c print_algo.c
SRCS        := $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

TOTAL_FILES := $(words $(SRCS))
CURR_FILE   := 0

CLR_EASE    := \033[0m
CLR_RED     := \033[1;31m
CLR_GRN     := \033[1;32m
CLR_YLW     := \033[1;33m
CLR_CYN     := \033[1;36m

TOTAL_BAR   := 30

all: $(NAME)

$(NAME): $(OBJS)
	@printf "\n$(CLR_YLW) Linking $(NAME)...$(CLR_EASE)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\r$(CLR_GRN) Build successful: ./$(NAME)%-20s\n\n$(CLR_EASE)" ""
	@printf "$(CLR_CYN)usage: ft_ssl command [flag or not] [file/string]\n$(CLR_EASE)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@clear
	@mkdir -p $(dir $@)
	@$(eval CURR_FILE=$(shell echo $$(($(CURR_FILE)+1))))
	@$(eval PERCENT=$(shell echo $$(($(CURR_FILE)*100/$(TOTAL_FILES)))))
	@$(eval PROGRESS=$(shell echo $$(($(PERCENT)*$(TOTAL_BAR)/100))))
	@$(eval REMAIN=$(shell echo $$(($(TOTAL_BAR)-$(PROGRESS)))))
	@printf "\r$(CLR_CYN)[$(CLR_GRN)"
	@printf "%0.s#" $$(seq 1 $(PROGRESS))
	@printf "%0.s." $$(seq 1 $(REMAIN))
	@printf "$(CLR_CYN)] %3d%% Compiling %-20s$(CLR_EASE)" $(PERCENT) ""
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(CLR_RED) Removing object files...$(CLR_EASE)\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "$(CLR_RED) Removing executable...$(CLR_EASE)\n"
	@rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re