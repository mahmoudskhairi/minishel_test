# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 14:50:47 by rmarzouk          #+#    #+#              #
#    Updated: 2024/07/21 17:18:12 by mskhairi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror 
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LIBS = -Llibft -lft -lreadline

LEXER_DIR=lexer/
S_LEXER= $(addprefix $(LEXER_DIR), 	\
									ft_lexer.c\
									ft_item.c\
									tokenization_utils.c \
									testing_print.c \
									ft_state.c \
									lexer_cleaner.c\
									lexer_errors.c\
									is_empty.c	\
									lexer_errors_utils.c	\
									reset_tokens.c\
									redirect_syntax.c)
O_LEXER=$(S_LEXER:.c=.o)

PARSER_DIR=parser/
S_PARSER= $(addprefix $(PARSER_DIR), 	\
										ft_cmd_limits.c\
										ft_command_utils.c\
										ft_command.c\
										set_token.c\
										organize.c\
										testing.c\
										expander.c\
										parser_cleaner.c\
									)
O_PARSER=$(S_PARSER:.c=.o)


NAME = minishell


all: $(NAME)

$(NAME): $(O_LEXER) $(O_PARSER) $(NAME).o
	make -C Libft
	$(CC) $(NAME).o $(CFLAGS) $(O_LEXER) $(O_PARSER) $(LIBS) -o $(NAME)

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	make fclean -C Libft
	rm -f $(O_LEXER) $(NAME).o
	rm -r $(O_PARSER)

fclean: clean
	rm -f $(NAME)

re: fclean all
