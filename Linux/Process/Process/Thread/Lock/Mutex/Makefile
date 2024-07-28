SRCS := $(wildcard *.c)
OUTS := $(patsubst %.c,%,$(SRCS))
CC := gcc
COM_OP := -Wall -g
.PHONY: clean rebuild all

all: $(OUTS)
% : %.c
	$(CC) $^ -o $@ $(COM_OP) -pthread


clean:
	$(RM) $(OUTS)

rebuild: clean all
