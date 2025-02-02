CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
LDFLAGS = -lm

SRCS = $(wildcard ./*.c)
OBJS = $(SRCS:.c=.o)

TARGET = graph

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

cp_cf:
	cp ../materials/linters/.clang-format .

all_checks:
	clang-format -n *.h *.c
	cppcheck .

all_fix:
	clang-format -i *.h *.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

rebuild: clean all