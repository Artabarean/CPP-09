# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atabarea <atabarea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/13 14:15:58 by atabarea          #+#    #+#              #
#    Updated: 2026/10/13 14:16:20 by atabarea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= PmergeMe
CXX			= c++
CPPFLAGS	= -Wall -Wextra -Werror -std=c++98

SRC		= main.cpp PmergeMe.cpp
OBJS	= $(SRC:.cpp=.o)

INCLUDE = -I.
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CPPFLAGS) $(OBJS) -o $(NAME)  

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re