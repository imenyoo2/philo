

NAME = philo_bonus
OFLAGS = -Wall -Werror -Wextra -pthread -O3
OBJS = philo_bonus.o parse_bonus.o helpers_bonus.o helpers2_bonus.o helpers3_bonus.o process2_bonus.o process_bonus.o forks_bonus.o philo_actions_bonus.o log_bonus.o monitor_bonus.o
CC = cc

all: $(NAME)

%.a: always
	$(call MAKE_LIB,all,$(word 1,$(subst /, ,$*)))

%_bonus.o: %_bonus.c philo_bonus.h
	$(CC) $(OFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OFLAGS) $(OBJS) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONEY: all clean fclean re
