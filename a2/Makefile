# Make the three executables, one for each scheduler

CC = g++
CFLAGS = -Wall -Werror -std=c++20
FILES = driver.cpp loader.cpp simulator.cpp pcb.cpp

all: scheduler

scheduler:
	$(CC) $(CFLAGS) -o scheduler $(FILES)


clean:
	rm -f scheduler