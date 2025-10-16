NAME = btc
CXX = c++
SRCS = BitcoinExchange.cpp main.cpp
OBJS = ${SRCS:.cpp=.o}
CLEANER = rm

all: ${NAME}

${NAME} : ${OBJS}
	${CXX} ${OBJS} -o ${NAME}
%.o:%.cpp
	${CXX} -c $< -o $@
clean:
	${CLEANER} -rf ${OBJS}

fclean : clean 

	${CLEANER} ${NAME}

re : fclean all

.PHONY: all clean fclean re