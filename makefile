CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=)

build: clean_nooutput $(OBJECTS)
	@echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	@echo "Done compiling, no errors or warnings. Created object files: $(OBJECTS)"
	@echo "----------------------------------------------------------------"

%: %.c
	@$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(OBJECTS)

clean_nooutput:
	@rm -f $(OBJECTS) > /dev/null

copyright:
	@echo "Copyright Grigore Mihnea-Andrei"

check_1: clean_nooutput $(OBJECTS)
	@./run_tests.sh 1

check_2: clean_nooutput $(OBJECTS)
	@./run_tests.sh 2

check_3: clean_nooutput $(OBJECTS)
	@./run_tests.sh 3

check_4: clean_nooutput $(OBJECTS)
	@./run_tests.sh 4

check_5: clean_nooutput $(OBJECTS)
	@./run_tests.sh 5

check_all: clean_nooutput $(OBJECTS)
	@./run_tests.sh