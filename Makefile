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
OBJS_DIR	:=	./objs/
HEADER		:=	./inc/
DEPS		:=	${addprefix ${HEADER},	Server.hpp \
										Replies.hpp} \
				${addprefix ${HEADER}channel/,	Channel.hpp \
												ChannelList.hpp} \
				${addprefix ${HEADER}client/,	Client.hpp \
												ClientList.hpp} \
				${addprefix ${HEADER}commands/,	ACommand.hpp \
												CommandList.hpp \
												CAP.hpp \
												INVITE.hpp \
												JOIN.hpp \
												KICK.hpp \
												PART.hpp \
												MODE.hpp \
												NICK.hpp \
												PASS.hpp \
												PING.hpp \
												PRIVMSG.hpp \
												QUIT.hpp \
												TOPIC.hpp \
												USER.hpp}

# Files
SRCS	=	${addprefix ${SRCS_DIR},	main.cpp \
										Replies.cpp} \
			${addprefix ${SRCS_DIR}server/,	Server.cpp \
											socket.cpp \
											runner.cpp \
											handleClient.cpp} \
			${addprefix ${SRCS_DIR}client/,	Client.cpp \
											ClientList.cpp} \
			${addprefix ${SRCS_DIR}channel/,	Channel.cpp \
												ChannelList.cpp} \
			${addprefix ${SRCS_DIR}commands/,	CommandList.cpp \
												CAP.cpp \
												INVITE.cpp \
												JOIN.cpp \
												KICK.cpp \
												MODE.cpp \
												NICK.cpp \
												PART.cpp \
												PASS.cpp \
												PING.cpp \
												PRIVMSG.cpp \
												QUIT.cpp \
												TOPIC.cpp \
												USER.cpp}

OBJS	=	${SRCS:.cpp=.o}

SRC_COUNT	= 0
SRC_TOT		:= ${shell find ${SRCS_DIR} -type f -name "*.cpp" | wc -l}
SRC_PRCT	= ${shell expr 100 \* ${SRC_COUNT} / ${SRC_TOT}}
BAR			= ${shell expr 23 \* ${SRC_COUNT} / ${SRC_TOT}}

${SRCS_DIR}%.o:	${SRCS_DIR}%.cpp ${DEPS}
	@${eval SRC_COUNT = ${shell expr ${SRC_COUNT} + 1}}
	@${CC} ${CFLAGS} -I${HEADER} -c $< -o $@
	@printf "${PROMPT} ${GREEN}Compiling${RESET}\n"
	@printf " ${GREY}   [${GREEN}%-23.${BAR}s${GREY}] [${SRC_COUNT}/${SRC_TOT} (${SRC_PRCT}%%)]${RESET}" "***********************"
	@printf "${UP}${UP}\n"

# === Rules === #
NAME	=	ircserv

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
