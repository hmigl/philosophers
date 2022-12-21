SHELL = /bin/sh

NAME := philo
OBJDIR := objdir

# -Werror
CFLAGS += -Wall -Wextra -pthread -g
# LDLIBS +=
# LDFLAGS +=

OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

SRC = main.c \
	  argument_validation.c utils_argument_validation.c \
	  pre_dinner.c utils_list.c after_dinner.c \
	  routine.c actions.c dinner_log.c

$(OBJDIR)/%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $@

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re
