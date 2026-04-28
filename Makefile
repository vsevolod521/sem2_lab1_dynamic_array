CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = lab1
SRCS = DynamicArray.c Complex.c functions_double.c tests.c utilits.c main.c
HDRS = DynamicArray.h Complex.h FieldInfo.h functions_double.h tests.h utilits.h
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ -lm

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild