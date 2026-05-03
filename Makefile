CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = lab1
TEST_TARGET = run_tests


COMMON_SRCS = DynamicArray.c Complex.c functions_double.c tests.c utilits.c
COMMON_OBJS = $(COMMON_SRCS:.c=.o)


MAIN_SRC = main.c
MAIN_OBJ = $(MAIN_SRC:.c=.o)


TEST_MAIN_SRC = test_main.c
TEST_MAIN_OBJ = $(TEST_MAIN_SRC:.c=.o)

.PHONY: all clean rebuild tests


all: $(TARGET)

$(TARGET): $(COMMON_OBJS) $(MAIN_OBJ)
	$(CC) $(COMMON_OBJS) $(MAIN_OBJ) -o $@ -lm


tests: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(COMMON_OBJS) $(TEST_MAIN_OBJ)
	$(CC) $(COMMON_OBJS) $(TEST_MAIN_OBJ) -o $@ -lm


$(COMMON_OBJS): %.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@


$(MAIN_OBJ): %.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@


$(TEST_MAIN_OBJ): %.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(COMMON_OBJS) $(MAIN_OBJ) $(TEST_MAIN_OBJ) $(TARGET) $(TEST_TARGET)


rebuild: clean all

.PHONY: all clean rebuild tests