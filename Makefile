# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/18 20:52:10 by rfrey             #+#    #+#              #
#    Updated: 2014/05/22 17:37:26 by rfrey            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME_SERVER = serveur
NAME_CLIENT = client
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
PATH_OBJ = obj
PATH_SRC = src
PATH_INC = inc
PATH_LIBFT = libft
LIBFT = libft.a
PATH_LIBFT_INC = $(PATH_LIBFT)/includes

SRC_SERVER = main.c init_env.c clean_fd.c get_opt.c main_loop.c \
				init_fd.c do_select.c check_fd.c \
				srv_create.c srv_accept.c \
				client_read.c client_write.c \
				interpret_cmd.c cmd_msg.c
SRC_CLIENT = clt_main.c clt_cmd.c clt_connect.c clt_main.c clt_send_text.c \
				clt_read.c

OBJ_SERVER = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC_SERVER))
OBJ_CLIENT = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC_CLIENT))

all : $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_SERVER) : $(OBJ_SERVER) $(PATH_LIBFT)/$(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo " done !"

$(NAME_CLIENT) : $(OBJ_CLIENT) $(PATH_LIBFT)/$(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo " done !"

$(PATH_OBJ)/%.o : $(addprefix $(PATH_SRC)/, %.c)
	@echo -n .
	@mkdir -p $(PATH_OBJ)
	@$(CC) $(CFLAGS) -o $@ -c $< -I $(PATH_INC)/ -I $(PATH_LIBFT_INC)/

$(PATH_LIBFT)/$(LIBFT) : $(PATH_LIBFT)/Makefile
	@cd $(PATH_LIBFT)/ && $(MAKE)

clean :
	@rm -f $(OBJ_SERVER)
	@rm -f $(OBJ_CLIENT)
	@cd $(PATH_LIBFT) && $(MAKE) $@

fclean : clean
	@rm -f $(NAME_SERVER)
	@rm -f $(NAME_CLIENT)
	@rm -f $(PATH_LIBFT)/$(LIBFT)

re : fclean all

.PHONY: clean fclean
