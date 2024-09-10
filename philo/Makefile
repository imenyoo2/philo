
NAME = philo
OFLAGS = -Wall -Werror -Wextra -pthread -O3 -g
OBJS = philo.o parse.o helpers.o helpers2.o helpers3.o thread2.o thread.o mutex.o philo_actions.o log.o monitor.o
CC = cc

all: $(NAME)

%.a: always
	$(call MAKE_LIB,all,$(word 1,$(subst /, ,$*)))

%.o: %.c philo.h
	$(CC) $(OFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OFLAGS) $(OBJS) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONEY: all clean fclean re
