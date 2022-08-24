# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabduvak <aabduvak@42istanbul.com.tr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/24 05:23:09 by aabduvak          #+#    #+#              #
#    Updated: 2022/08/24 05:28:12 by aabduvak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors

BLACK			=	"\033[0;30m"
RED				=	"\033[0;31m"
GREEN			=	"\033[0;32m"
YELLOW			=	"\033[0;33m"
CYAN			=	"\033[0;35m"
BLUE			=	"\033[0;36m"
WHITE			=	"\033[0;37m"
END				=	"\033[0;0m"

# Files

SRCS			= $(wildcard *.cpp)
OBJS			= $(SRCS:%.cpp=bin/%.o)
BIN				= ./bin
LOG				= output.file

# Command and Flags

NAME			= main
CC				= c++
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror

# Rules

all : $(NAME)

$(BIN):
	@mkdir $(BIN)

$(BIN)/%.o: %.cpp
	@echo $(YELLOW) "Compiling..." $< $(END)
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(BIN) $(OBJS)
	@echo $(YELLOW) "Building... $(NAME)" $(END)
	@$(CC) $(OBJS) -o $(NAME)
	@echo $(GREEN) "$(NAME) created successfully!\n" $(END)

# $< input files
# $@ output files
# in makefile used to create output files in their subfolder

clean :
	@echo $(YELLOW) "Removing object files..." $(END)
	@$(RM) $(OBJS)
	@$(RM) $(BIN)
	@echo $(RED) "All files deleted successfully!\n" $(END)

fclean : clean
	@echo $(YELLOW) "Removing $(NAME)..." $(END)
	@$(RM) $(LOG)
	@$(RM) $(NAME)
	@echo $(RED) "$(NAME) deleted successfully!\n" $(END)

re : fclean all

run : $(NAME)
	@./$(NAME)

leaks: $(NAME)
	@valgrind --log-file=$(LOG) --leak-check=yes --tool=memcheck ./$(NAME)  
	@cat $(LOG)

.PHONY: all clean fclean re run