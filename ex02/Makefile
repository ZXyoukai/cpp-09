NAME = PmergeMe
CXX = c++
SRCS = main.cpp PmergeMe.cpp
OBJS = ${SRCS:.cpp=.o}
INCLUDES = PmergeMe.hpp
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CLEANER = rm

all: ${NAME}

${NAME} : ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME}
%.o:%.cpp ${INCLUDES}
	${CXX} ${CXXFLAGS} -c $< -o $@
clean:
	${CLEANER} -rf ${OBJS}

fclean : clean 

	${CLEANER} -rf ${NAME}

re : fclean all

.PHONY: all clean fclean re