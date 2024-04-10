# === Colors === #
RED = \033[0;31m
GREY = \033[0;90m
GREEN = \033[0;32m
BLUE = \033[0;34m
RESET = \033[0m

# === Prompt === #
PROMPT	=	${GREY}[${BLUE}${NAME}${GREY}]${RESET}:

# === Compilation === #
CC		=	c++
CFLAGS	=	-Wall -Wextra -Werror -std=c++98

ifdef STRICT
	CFLAGS	+=	-pedantic
endif

ifdef DEBUG
	CFLAGS	+=	-g3
endif

# === Sources & Objects === #

# Directories
SRCS_DIR	=	./srcs/
OBJS_DIR	=	./objs # Add objects to a separate directory?
HEADER		=	./inc/
DEPS		=	${addprefix ${HEADER},	Client.hpp \
										IrcIncludes.hpp \
										Server.hpp \
										Utils.hpp}

# Files
SRCS	=	${addprefix ${SRCS_DIR},	main.cpp \
										Client.cpp} \
			${addprefix ${SRCS_DIR}server/,	Server.cpp \
											socket.cpp}

OBJS	=	${SRCS:.cpp=.o}


${SRCS_DIR}%.o: ${SRCS_DIR}%.cpp ${DEPS}
	@printf "${PROMPT} ${GREEN}Compiling${RESET} $<\n"
	@${CC} ${CFLAGS} -I${HEADER} -c $< -o $@

# === Rules === #
NAME	=	ircserv

all:		 ${NAME}

${NAME}:	${OBJS}
	@printf "${PROMPT} ${GREEN}Linking${RESET} ${NAME}\n"
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}

strict:
	@${MAKE} STRICT=1

debug:
	@${MAKE} DEBUG=1

clean:
	@printf "${PROMPT} ${RED}Cleaning${RESET} objects\n"
	@rm -f ${OBJS}

fclean:		clean
	@printf "${PROMPT} ${RED}Cleaning${RESET} ${NAME}\n"
	@rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re strict
