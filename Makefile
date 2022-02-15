# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/12 15:35:51 by shamizi           #+#    #+#              #
#    Updated: 2022/02/14 12:34:40 by shamizi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =philosopher

SRCS = main.c \
       utils.c \
       routine.c \
       init.c
	   
OBJS =$(SRCS:.c=.o)


CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread
clean: 
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all
