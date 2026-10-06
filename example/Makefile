CC = cc
CFLAGS = -std=c11 -Wall -Wextra

TESTS = test_basic.c test_failure.c main.c
TARGET = tests

$(TARGET): $(TESTS)
	$(CC) $(CFLAGS) $(TESTS) -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: test clean
