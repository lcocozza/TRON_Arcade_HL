.SILENT:

NAME= TRON_Arcade_HL

SRC_FILE=	main.c \
		ft_general.c \
		libft.c

NETWORK_FILE=	ft_general_network.c \
		ft_server_core.c

SRC_PATH= srcs/
NETWORK_PATH= $(SRC_PATH)network/

INCL_PATH= -I incls/

SRC= $(addprefix $(SRC_PATH), $(SRC_FILE))
NETWORK= $(addprefix $(NETWORK_PATH), $(NETWORK_FILE))

ALL_SRC= $(SRC) $(NETWORK)

FLAGS= -Wall -Wextra -Werror

$(NAME): all

all:
	gcc -g -o $(NAME) $(FLAGS) $(ALL_SRC) $(INCL_PATH)

clean:
	rm $(NAME)

fclean: clean

re: fclean all

