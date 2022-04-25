# -*- MakeFile -*-


LINK_DIRS = ../crypto ../blockchain/v0.3 ../blockchain/v0.3/transaction ../llist
LINKS = $(addprefix -l, hblk_blockchain llist ssl crypto hblk_crypto) -pthread
INCLUDE = $(addprefix -I, . $(LINK_DIRS)/)

NAME = cli
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g3 $(INCLUDE)

SRCDIR = src
OBJDIR = obj

INC_DIR = SRCDIR

OPERATIONSDIR = operations
UTILSDIR = utils

OBJ = $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/*.c))
OBJ += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(OPERATIONSDIR)/*.c))
OBJ += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(UTILSDIR)/*.c))

.PHONY : all clean oclean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(addprefix -L, $(LINK_DIRS)) -Wl,--start-group $(LINKS) -Wl,--end-group 

clean:
	$(RM) *~ $(NAME)

oclean:
	$(RM) $(OBJ)

fclean: clean oclean

re: oclean $(NAME)

print-%:
	@echo '$*=$($*)'
