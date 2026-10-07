CC = cc
CFLAGS = -std=c11 -Wall -Wextra

TESTS = main.c \
		test_basic.c \
		test_failure.c \
		test_skip.c
TARGET = tests

$(TARGET): $(TESTS)
	$(CC) $(CFLAGS) $(TESTS) -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: test clean
