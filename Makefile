CC = gcc
WARN = -Wall -Wextra -std=c11
CFLAGS = $(WARN) -O2
DEPFLAGS = -MMD -MP

ALG_SRCS = src/basicos/bubble.c src/basicos/selection.c src/basicos/insertion.c \
           src/avancados/merge.c src/avancados/quick.c src/avancados/heap.c
SRCS = src/main.c $(ALG_SRCS)
TEST_SRCS = tests/test_basic.c $(ALG_SRCS)

OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)
ALL_OBJS = $(sort $(OBJS) $(TEST_OBJS))

TARGET = sort_main
TEST_TARGET = test_basic

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) $(ALL_OBJS) $(ALL_OBJS:.o=.d)

.PHONY: all test clean

-include $(ALL_OBJS:.o=.d)
