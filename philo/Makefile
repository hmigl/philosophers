SHELL = /bin/sh

NAME := philo
OBJDIR := objdir

CFLAGS += -Wall -Wextra -Werror -pthread -g
LDLIBS += -pthread

OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

SRC = main.c dinner_log.c \
	  argument_validation.c utils_argument_validation.c \
	  utils_list.c after_dinner.c \
	  routine.c routine_death.c \
	  actions_eating.c actions_sleeping.c

$(OBJDIR)/%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re
