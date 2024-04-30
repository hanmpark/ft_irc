# === Colors === #
RED		:= \033[0;31m
GREY	:= \033[0;90m
GREEN	:= \033[0;32m
BLUE	:= \033[0;34m
RESET	:= \033[0m
UP		:= \033[A

# === Prompt === #
PROMPT	=	${GREY}[${BLUE}${NAME}${GREY}]${RESET}:

# === Compilation === #
CC		:=	c++
CFLAGS	=	-Wall -Wextra -Werror -std=c++98

ifdef STRICT
	CFLAGS	+=	-pedantic
endif

ifdef DEBUG
	CFLAGS	+=	-fsanitize=address -g3 
endif

ifdef WLOGS
	CFLAGS	+=	-D WLOGS=1
endif

# === Sources & Objects === #

# Directories
SRCS_DIR	:=	./srcs/
HEADER		:=	./inc/

# Sources
SRCS	= main.cpp \
			srcs/IRCBot.cpp \
			utils/utils.cpp \

OBJS	=	${SRCS:.cpp=.o}

SRC_COUNT	= 0
SRC_TOT		:= ${shell find . -type f -name "*.cpp" | wc -l}
SRC_PRCT	= ${shell expr 100 \* ${SRC_COUNT} / ${SRC_TOT}}
BAR			= ${shell expr 23 \* ${SRC_COUNT} / ${SRC_TOT}}

%.o:	%.cpp
	@${eval SRC_COUNT = ${shell expr ${SRC_COUNT} + 1}}
	@${CC} ${CFLAGS} -I${HEADER} -c $< -o $@
	@printf "${PROMPT} ${GREEN}Compiling${RESET}\n"
	@printf " ${GREY}   [${GREEN}%-23.${BAR}s${GREY}] [${SRC_COUNT}/${SRC_TOT} (${SRC_PRCT}%%)]${RESET}" "***********************"
	@printf "${UP}${UP}\n"

# === Rules === #
NAME	=	IRCBot

all:		${NAME}

${NAME}:	${OBJS}
	@printf "${PROMPT} ${GREEN}Linking${RESET} ${NAME}                                                         \n"
	@printf " ${GREY}   [${GREEN}%-23.${BAR}s${GREY}] [${SRC_COUNT}/${SRC_TOT} (${SRC_PRCT}%%)]${RESET}\n" "***********************"
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}

strict:
	@${MAKE} STRICT=1

debug:
	@${MAKE} DEBUG=1

wlogs:
	@${MAKE} WLOGS=1

clean:
	@printf "${PROMPT} ${RED}Cleaning${RESET} objects\n"
	@rm -f ${OBJS}

fclean:		clean
	@printf "${PROMPT} ${RED}Cleaning${RESET} ${NAME}\n"
	@rm -f ${NAME}

re:			fclean all

.PHONY:		all strict debug wlogs clean fclean re
