SRCS := $(wildcard *.c)
OUTS := $(patsubst %.c, %.o, $(SRCS))
CC := gcc
COM_OP := -Wall -g
.PHONY: clean rebuild all
BIN := client

all: $(OUTS)
	$(CC) $^ -o $(BIN) $(COM_OP)


%.o: %.c
	$(CC) -c $^ -o $@ $(COM_OP)


clean:
	$(RM) $(OUTS)

rebuild: clean all
