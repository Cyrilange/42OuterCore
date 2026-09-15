NAME        := ft_ssl
TEST_SCRIPT := test.sh

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

all: $(NAME) $(TEST_SCRIPT)

$(NAME): $(OBJS)
	@printf "\n$(CLR_YLW) Linking $(NAME)...$(CLR_EASE)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\r$(CLR_GRN) Build successful: ./$(NAME)%-20s\n\n$(CLR_EASE)" ""
	@printf "$(CLR_CYN)usage: ft_ssl command [flag or not] [file/string]\n$(CLR_EASE)"

$(TEST_SCRIPT): $(NAME)
	@printf "$(CLR_CYN) Generating $(TEST_SCRIPT)...$(CLR_EASE)\n"
	@echo '#!/bin/bash' > $(TEST_SCRIPT)
	@echo '' >> $(TEST_SCRIPT)
	@echo 'GREEN="'"'"'\033[0;32m'"'"'"' >> $(TEST_SCRIPT)
	@echo 'BLUE="'"'"'\033[0;34m'"'"'"' >> $(TEST_SCRIPT)
	@echo 'NC="'"'"'\033[0m'"'"'"' >> $(TEST_SCRIPT)
	@echo '' >> $(TEST_SCRIPT)
	@echo 'run_test() {' >> $(TEST_SCRIPT)
	@echo '    echo -e "$${BLUE}> $$1$${NC}"' >> $(TEST_SCRIPT)
	@echo '    eval "$$1"' >> $(TEST_SCRIPT)
	@echo '    echo ""' >> $(TEST_SCRIPT)
	@echo '}' >> $(TEST_SCRIPT)
	@echo '' >> $(TEST_SCRIPT)
	@echo 'echo -e "$${GREEN}=== PREPARING TEST FILES ===$${NC}"' >> $(TEST_SCRIPT)
	@echo 'echo "And above all," > file' >> $(TEST_SCRIPT)
	@echo 'echo "https://www.42.fr/" > website' >> $(TEST_SCRIPT)
	@echo 'echo ""' >> $(TEST_SCRIPT)
	@echo '' >> $(TEST_SCRIPT)
	@echo 'echo -e "$${GREEN}=== MD5 & PARSING TESTS ===$${NC}"' >> $(TEST_SCRIPT)
	@echo '' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'echo "42 is nice" | openssl md5'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'echo "42 is nice" | md5sum'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'echo "42 is nice" | ./ft_ssl md5'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'echo "42 is nice" | ./ft_ssl md5 -p'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'echo "Pity the living." | ./ft_ssl md5 -q -r'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'./ft_ssl md5 file'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'./ft_ssl md5 -r file'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'./ft_ssl md5 -s "pity those that aren'\''t following baerista on spotify."'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'echo "some of this will not make sense at first" | ./ft_ssl md5 file'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'echo "but eventually you will understand" | ./ft_ssl md5 -p -r file'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'echo "GL HF let'\''s go" | ./ft_ssl md5 -p -s "foo" file'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar"'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file'"'"'' >> $(TEST_SCRIPT)
	@echo '' >> $(TEST_SCRIPT)
	@echo 'echo -e "$${GREEN}=== SHA256 TESTS ===$${NC}"' >> $(TEST_SCRIPT)
	@echo '' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'./ft_ssl sha256 -q website'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'sha256sum website'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'./ft_ssl sha256 -s "42 is nice"'"'"'' >> $(TEST_SCRIPT)
	@echo 'run_test '"'"'echo -n "42 is nice" | sha256sum'"'"'' >> $(TEST_SCRIPT)
	@echo '' >> $(TEST_SCRIPT)
	@echo 'rm -f file website' >> $(TEST_SCRIPT)
	@chmod +x $(TEST_SCRIPT)

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
	@printf "$(CLR_RED) Removing object files and test script...$(CLR_EASE)\n"
	@rm -rf $(OBJ_DIR)
	@rm -f $(TEST_SCRIPT)

fclean: clean
	@printf "$(CLR_RED) Removing executable...$(CLR_EASE)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re