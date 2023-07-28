NAME = PmergeMe

SRC = main.cpp PmergeMe.cpp

OBJ = $(SRC:.cpp=.o)

CC = g++

CFLAGS = -Wall -Wextra -Werror

CPPFLAGS = -std=c++98

all: $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re